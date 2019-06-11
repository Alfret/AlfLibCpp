// MIT License
//
// Copyright (c) 2019 Filip Björklund
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "alflib/string.hpp"

// ========================================================================== //
// Headers
// ========================================================================== //

#include "alflib/assert.hpp"
#include <vector>

// ========================================================================== //
// String Implementation
// ========================================================================== //

namespace alflib {

String::String(const char8* string)
  : mString(string ? string : "")
  , mLength(static_cast<u32>(alfUTF8StringLength(string)))
{}

// -------------------------------------------------------------------------- //

String::String(const char16* string)
{
  u32 numBytes;
  AlfBool success = alfUTF16ToUTF8(
    reinterpret_cast<const AlfChar16*>(string), &numBytes, nullptr);
  AlfAssert(success, "Failed to convert UTF-16 to UTF-8");
  char* buffer = new char[numBytes + 1ull];
  buffer[numBytes] = 0;
  success = alfUTF16ToUTF8(
    reinterpret_cast<const AlfChar16*>(string), &numBytes, buffer);
  AlfAssert(success, "Failed to convert UTF-16 to UTF-8");
  mString = buffer;
  mLength = static_cast<u32>(alfUTF8StringLength(buffer));
  delete[] buffer;
}

// -------------------------------------------------------------------------- //

String::String(const std::string& string)
  : mString(string)
  , mLength(static_cast<u32>(alfUTF8StringLength(string.c_str())))
{}

// -------------------------------------------------------------------------- //

String::String(u32 codepoint)
{
  char8 encoded[5];
  u32 numBytes;
  const AlfBool success = alfUTF8Encode(encoded, 0, codepoint, &numBytes);
  AlfAssert(success, "Failed to construct string from codepoint");
  encoded[numBytes] = 0;
  mString = std::string(encoded);
  mLength = 1;
}

// -------------------------------------------------------------------------- //

String::String(const String& string)
  : mString(string.mString)
  , mLength(string.mLength)
{}

// -------------------------------------------------------------------------- //

String::String(String&& string) noexcept
  : mString(std::move(string.mString))
  , mLength(string.mLength)
{}

// -------------------------------------------------------------------------- //

String::~String()
{
  mLength = 0;
}

// -------------------------------------------------------------------------- //

String&
String::operator=(const String& other)
{
  if (this != &other) {
    mString = other.mString;
    mLength = other.mLength;
  }
  return *this;
}

// -------------------------------------------------------------------------- //

String&
String::operator=(String&& other) noexcept
{
  if (this != &other) {
    mString = std::move(other.mString);
    mLength = other.mLength;
  }
  return *this;
}

// -------------------------------------------------------------------------- //

s64
String::AtByteOffset(u32 offset, u32& width) const
{
  // Decode at offset
  u32 codepoint, numBytes;
  const AlfBool success =
    alfUTF8Decode(GetUTF8(), offset, &codepoint, &numBytes);
  if (!success) {
    return -1;
  }

  // Set width and return codepoint
  width = numBytes;
  return codepoint;
}

// -------------------------------------------------------------------------- //

s64
String::Find(const String& substring) const
{
  const std::string::size_type pos = mString.find(substring.mString);
  if (pos == std::string::npos) {
    return -1;
  }
  return pos;
}

// -------------------------------------------------------------------------- //

s64
String::IndexOf(u32 codepoint) const
{
  return alfUTF8IndexOf(GetUTF8(), codepoint);
}

// -------------------------------------------------------------------------- //

s64
String::LastIndexOf(u32 codepoint) const
{
  return alfUTF8LastIndexOf(GetUTF8(), codepoint);
}

// -------------------------------------------------------------------------- //

bool
String::StartsWith(u32 codepoint) const
{
  return mLength > 0 && At(0) == codepoint;
}

// -------------------------------------------------------------------------- //

bool
String::EndsWith(u32 codepoint) const
{
  // Check that the codepoint is even possible to be at the end
  const char8* str = GetUTF8();
  const u32 width = CodepointWidth(codepoint);
  if (width > GetSize()) {
    return false;
  }
  
  // Decode at expected location from end
  u32 _codepoint, numBytes;
  if (alfUTF8Decode(str, GetSize() - width, &_codepoint, &numBytes)) {
    return _codepoint == codepoint;
  }
  return false;
}

// -------------------------------------------------------------------------- //

u32
String::Replace(const String& from, const String& to)
{
  s64 index;
  u32 count = 0;
  while ((index = Find(from)) >= 0) {
    String str0 = mString.substr(0, index);
    String str1 = mString.substr(index + from.GetSize());
    operator=(str0 + to + str1);
    count++;
  }
  return count;
}

// -------------------------------------------------------------------------- //

u32
String::Remove(u32 codepoint)
{
  // Encode the codepoint into a string
  char8 encoded[5];
  u32 numBytes;
  const AlfBool success = alfUTF8Encode(encoded, 0, codepoint, &numBytes);
  if (!success) {
    return 0;
  }
  encoded[numBytes] = 0;

  // Use replace
  return Replace(encoded, "");
}

// -------------------------------------------------------------------------- //

String
String::Substring(u64 from, u64 count) const
{
  // TODO(Filip Björklund): Fix alf_unicode to allow no allocation to be done.
  // TODO(Filip Björklund): Or use simpler functions to build substring.

  // Retrieve substring
  char8* substring;
  if (count == -1) {
    substring = alfUTF8SubstringFrom(GetUTF8(), from);
  } else {
    substring = alfUTF8Substring(GetUTF8(), from, count);  
  }

  String output(substring);
  free(substring);
  return output;
}

// -------------------------------------------------------------------------- //

void
String::operator+=(const String& string)
{
  mString += string.mString;
  mLength += string.mLength;
}

// -------------------------------------------------------------------------- //

void
String::operator+=(const char8* string)
{
  mString += string;
  mLength += static_cast<u32>(alfUTF8StringLength(string));
}

// -------------------------------------------------------------------------- //

u32
String::At(u32 index) const
{
  return alfUTF8AtIndex(GetUTF8(), static_cast<u64>(index));
}

// -------------------------------------------------------------------------- //

u32 String::operator[](u32 index) const
{
  return At(index);
}

// -------------------------------------------------------------------------- //

UniquePointer<char16[]>
String::GetUTF16() const
{
  const char8* _string = GetUTF8();
  u32 numCodeUnits;
  AlfBool success = alfUTF8ToUTF16(_string, &numCodeUnits, nullptr);
  AlfAssert(success, "Failed to convert UTF-16 to UTF-8");

  char16* buffer =
    DefaultAllocator::Instance().NewArray<char16>(numCodeUnits + 1ull);

  buffer[numCodeUnits] = 0;
  success = alfUTF8ToUTF16(
    _string, &numCodeUnits, reinterpret_cast<AlfChar16*>(buffer));
  AlfAssert(success, "Failed to convert UTF-16 to UTF-8");
  return UniquePointer<char16[]>(buffer, DefaultAllocator::Instance());
}

// -------------------------------------------------------------------------- //

std::ostream&
operator<<(std::ostream& stream, const String& string)
{
  return stream << string.GetUTF8();
}

// -------------------------------------------------------------------------- //

String
operator+(const String& str0, const String& str1)
{
  return str0.mString + str1.mString;
}

// -------------------------------------------------------------------------- //

String
operator+(const String& str0, const char8* str1)
{
  return str0 + String(str1);
}

// -------------------------------------------------------------------------- //

String
operator+(const char8* str0, const String& str1)
{
  return String(str0) + str1;
}

// -------------------------------------------------------------------------- //

bool
operator==(const String& str0, const String& str1)
{
  return str0.mString == str1.mString;
}

// -------------------------------------------------------------------------- //

bool
operator==(const String& str0, const char8* str1)
{
  return str0 == String(str1);
}

// -------------------------------------------------------------------------- //

bool
operator==(const char8* str0, const String& str1)
{
  return String(str0) == str1;
}

// -------------------------------------------------------------------------- //

bool
operator!=(const String& str0, const String& str1)
{
  return str0.mString != str1.mString;
}

// -------------------------------------------------------------------------- //

bool
operator!=(const String& str0, const char8* str1)
{
  return str0 != String(str1);
}

// -------------------------------------------------------------------------- //

bool
operator!=(const char8* str0, const String& str1)
{
  return String(str0) != str1;
}

// -------------------------------------------------------------------------- //

u32
String::CodepointWidth(u32 codepoint)
{
  return alfUTF8CodepointWidth(codepoint);
}

}
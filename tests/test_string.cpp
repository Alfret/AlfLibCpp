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

// ========================================================================== //
// Headers
// ========================================================================== //

#include "alflib/string.hpp"
#include <doctest/doctest.h>

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[String] - Construct()")
{
  // Normal (ASCII)
  auto string = String("my string");
  CHECK(string.GetLength() == 9);
  CHECK(string.GetSize() == 9);

  // Borderline (ASCII)
  string = String("");
  CHECK(string.GetLength() == 0);
  CHECK(string.GetSize() == 0);
  string = String(
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  CHECK(string.GetLength() == 200);
  CHECK(string.GetSize() == 200);

  // Normal (UTF-8)
  string = String("hellö!");
  CHECK(string.GetLength() == 6);
  CHECK(string.GetSize() == 7);
  string = "Smile 😃";
  CHECK(string.GetLength() == 7);
  CHECK(string.GetSize() == 10);

  // Borderline (UTF-8)
  string = "😃";
  CHECK(string.GetLength() == 1);
  CHECK(string.GetSize() == 4);
  string = "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃"
           "😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃😃";
  CHECK(string.GetLength() == 200);
  CHECK(string.GetSize() == 800);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - AtByteOffset()") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - Find()") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - IndexOf()/LastIndexOf()") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - StartsWith()")
{
  // Normal
  CHECK(String{ "A string" }.StartsWith("A str"));

  CHECK(!String{ "string" }.StartsWith("name"));

  // Borderline
  CHECK(String{ "" }.StartsWith(""));
  CHECK(String{ "string" }.StartsWith(""));
  CHECK(String{ "string" }.StartsWith("string"));
  CHECK(!String{ "" }.StartsWith("string"));
  CHECK(!String{ "str" }.StartsWith("string"));
}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - EndsWith()")
{
  // Normal
  CHECK(String{ "A string" }.EndsWith("string"));
  CHECK(!String{ "string" }.EndsWith("name"));

  // Borderline
  CHECK(String{ "" }.EndsWith(""));
  CHECK(String{ "string" }.EndsWith(""));
  CHECK(String{ "string" }.EndsWith("string"));
  CHECK(!String{ "" }.EndsWith("string"));
  CHECK(!String{ "string" }.EndsWith("super string"));
}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - Replace()") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - Remove()") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - Substring()")
{
  // Normal cases
  CHECK(String{ "This is a string" }.Substring(10) == "string");
  CHECK(String{ "This is a string" }.Substring(10, 3) == "str");
  CHECK(String{ "This is a string" }.Substring(5, 2) == "is");

  CHECK(String{ "This is a 😃 smile" }.Substring(12) == "smile");
  CHECK(String{ "This is a 😃 smile" }.Substring(12, 3) == "smi");
  CHECK(String{ "This is a 😃 smile" }.Substring(5, 2) == "is");
  CHECK(String{ "This is a 😃 smile" }.Substring(10, 1) == "😃");

  // Borderline cases
  CHECK(String("").Substring(0) == "");
  CHECK(String("").Substring(0, 0) == "");
  CHECK(String("").Substring(0, 100) == "");
  CHECK(String("").Substring(100) == "");
  CHECK(String("").Substring(100, 0) == "");
  CHECK(String("").Substring(100, 100) == "");

  CHECK(String("😃").Substring(0) == "😃");
  CHECK(String("😃").Substring(0, 0) == "");
  CHECK(String("😃").Substring(0, 100) == "😃");
  CHECK(String("😃").Substring(100) == "");
  CHECK(String("😃").Substring(100, 0) == "");
  CHECK(String("😃").Substring(100, 100) == "");

  CHECK(String("😃,😃").Substring(0, 1) == "😃");
  CHECK(String("😃,😃").Substring(1, 1) == ",");
  CHECK(String("😃,😃").Substring(2, 1) == "😃");
  CHECK(String("😃,😃").Substring(0, 4) == "😃,😃");
}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - ForEach()") {}

}

// -------------------------------------------------------------------------- //

TEST_CASE("[String] - Iterate")
{
  String str("Smile åäö 😃");
  u32 refCodepoints[] = { 'S', 'm', 'i', 'l', 'e',   ' ',
                          229, 228, 246, ' ', 128515 };
  s32 index = 0;
  for (const auto& codepoint : str) {
    CHECK(codepoint == refCodepoints[index]);
    index++;
  }
}

}
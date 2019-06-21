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

#pragma once

// ========================================================================== //
// Headers
// ========================================================================== //

// Standard headers
#include <unordered_map>
#include <vector>

// Project headers
#include "alflib/core/buffer.hpp"

// ========================================================================== //
// MemoryWriter Declaration
// ========================================================================== //

namespace alflib {

/** \class MemoryWriter.
 * \author Filip Björklund
 * \date 01 januari 2019 - 00:00
 * \brief Memory writer.
 * \details
 * Class for writing binary data to a memory buffer.
 *
 * It should be noted that the contents of the buffer is stored in little-endian
 * byte order. This means that little-endian machines can write without
 * conversion.
 */

class MemoryWriter
{
public:
  /** Buffer resize factor **/
  static constexpr f32 BUFFER_RESIZE_FACTOR = 2.0f;
  /** Default buffer size **/
  static constexpr u64 DEFAULT_BUFFER_SIZE = 16;

private:
  /** Buffer that data is written to **/
  Buffer mBuffer;
  /** Write offset **/
  u64 mWriteOffset = 0;

public:
  /** Construct a memory with a buffer of a specified size.
   * \pre Buffer size must exceed zero (0).
   * \brief Construct memory writer.
   * \param bufferSize Size of the buffer.
   * \param allocator Allocator for allocating memory for the buffer.
   */
  explicit MemoryWriter(u64 bufferSize = DEFAULT_BUFFER_SIZE,
                        Allocator& allocator = DefaultAllocator::Instance());

  /** Write raw bytes to the memory buffer.
   * \brief Write bytes.
   * \param data Bytes to write.
   * \param size Size of data to write.
   */
  void WriteBytes(const u8* data, u64 size);

  /** Write an object of the type T to buffer.
   * \note This function requires the object to have a function
   * 'ToBytes(MemoryWriter& writer)' defined for its class.
   * \brief Write object.
   * \tparam T Type of object to write.
   * \param object Object to write.
   */
  template<typename T>
  void Write(const T& object);

  /** Write an object of the type T to buffer.
   * \note This function requires the object to have a function
   * 'ToBytes(MemoryWriter& writer)' defined for its class.
   * \brief Write object.
   * \tparam T Type of object to write.
   * \param object Object to write.
   */
  template<typename T>
  void Write(const T* object);

  /** Write a list of objects to the buffer.
   * \brief Write list.
   * \tparam T Type of objects in list.
   * \param list List to write.
   */
  template<typename T>
  void Write(const ArrayList<T>& list);

  /** Write a std::vector to the buffer.
   * \brief Write vector.
   * \tparam T Object type.
   * \param vector Vector to write.
   */
  template<typename T>
  void Write(const std::vector<T>& vector);

  /** Write a std::unordered_map to the buffer.
   * \brief Write map.
   * \tparam K Key type.
   * \tparam V Value type.
   * \param map Map to write.
   */
  template<typename K, typename V>
  void Write(const std::unordered_map<K, V>& map);

  /** Returns the buffer of the memory writer.
   * \brief Returns buffer.
   * \return Buffer.
   */
  Buffer& GetBuffer() { return mBuffer; }

  /** Returns the buffer of the memory writer.
   * \brief Returns buffer.
   * \return Buffer.
   */
  const Buffer& GetBuffer() const { return mBuffer; }

  /** Returns the current write offset in the underlying buffer.
   * \brief Returns write offset.
   * \return Write offset.
   */
  u64 GetOffset() const { return mWriteOffset; }
};

// -------------------------------------------------------------------------- //

template<typename T>
void
MemoryWriter::Write(const T& object)
{
  object.ToBytes(*this);
}

// -------------------------------------------------------------------------- //

template<typename T>
void
MemoryWriter::Write(const T* object)
{
  object->ToBytes(*this);
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const s8& object)
{
  WriteBytes(reinterpret_cast<const u8*>(&object), 1);
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const u8& object)
{
  WriteBytes(&object, 1);
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const s16& object)
{
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  WriteBytes(reinterpret_cast<const u8*>(&object), sizeof(s16));
#else
  s16 _object = SwapEndian(object);
  WriteBytes(reinterpret_cast<const u8*>(&_object), sizeof(s16));
#endif
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const u16& object)
{
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  WriteBytes(reinterpret_cast<const u8*>(&object), sizeof(u16));
#else
  u16 _object = SwapEndian(object);
  WriteBytes(reinterpret_cast<const u8*>(&_object), sizeof(u16));
#endif
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const s32& object)
{
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  WriteBytes(reinterpret_cast<const u8*>(&object), sizeof(s32));
#else
  s32 _object = SwapEndian(object);
  WriteBytes(reinterpret_cast<const u8*>(&_object), sizeof(s32));
#endif
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const u32& object)
{
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  WriteBytes(reinterpret_cast<const u8*>(&object), sizeof(u32));
#else
  u32 _object = SwapEndian(object);
  WriteBytes(reinterpret_cast<const u8*>(&_object), sizeof(u32));
#endif
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const s64& object)
{
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  WriteBytes(reinterpret_cast<const u8*>(&object), sizeof(s64));
#else
  s64 _object = SwapEndian(object);
  WriteBytes(reinterpret_cast<const u8*>(&_object), sizeof(s64));
#endif
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const u64& object)
{
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  WriteBytes(reinterpret_cast<const u8*>(&object), sizeof(u64));
#else
  u64 _object = SwapEndian(object);
  WriteBytes(reinterpret_cast<const u8*>(&_object), sizeof(u64));
#endif
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const f32& object)
{
  Write(reinterpret_cast<const u32&>(object));
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const f64& object)
{
  Write(reinterpret_cast<const u64&>(object));
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const String& object)
{
  u32 size = object.GetSize();
  Write(size);
  WriteBytes(reinterpret_cast<const u8*>(object.GetUTF8()), size);
}

// -------------------------------------------------------------------------- //

template<>
void inline MemoryWriter::Write(const char8* object)
{
  u32 size = strlen(object);
  Write(size);
  WriteBytes(reinterpret_cast<const u8*>(object), size);
}

// -------------------------------------------------------------------------- //

template<typename T>
void
MemoryWriter::Write(const ArrayList<T>& list)
{
  Write(static_cast<u64>(list.GetSize()));
  for (const T& object : list) {
    Write(object);
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
void
MemoryWriter::Write(const std::vector<T>& vector)
{
  Write(static_cast<u64>(vector.size()));
  for (const T& object : vector) {
    Write(object);
  }
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
void
MemoryWriter::Write(const std::unordered_map<K, V>& map)
{
  Write(static_cast<u64>(map.size()));
  for (const auto& entry : map) {
    Write<K>(entry.first);
    Write<V>(entry.second);
  }
}

}
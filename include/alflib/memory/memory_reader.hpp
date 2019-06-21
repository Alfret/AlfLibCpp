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
#include "alflib/core/common.hpp"
#include "alflib/core/buffer.hpp"

// ========================================================================== //
// MemoryReader Implementation
// ========================================================================== //

namespace alflib {

/** \class MemoryReader
 * \author Filip Björklund
 * \date 20 june 2019 - 23:41
 * \brief Memory reader.
 * \details
 * Class for reading data from a byte buffer.
 */
class MemoryReader
{
private:
  /** Buffer that is being read **/
  const Buffer& mBuffer;
  /** Read offset **/
  u64 mReadOffset = 0;

public:
  /** Construct a memory reader from a buffer.
   * \brief Construct memory reader.
   * \param buffer Buffer for the reader to work on.
   */
  explicit MemoryReader(const Buffer& buffer);

  /** Read the specified number of bytes from the reader.
   * \brief Read bytes.
   * \param size Number or bytes to read.
   * \return Read bytes.
   */
  const u8* ReadBytes(u64 size);

  /** Read an object of the type T from the buffer.
   * \note This function requires the object to have a static function
   * 'FromBytes(MemoryReader&)' defined for it. This function will receive  the
   * reader and is responsible for reading all data that is required to
   * reconstruct the object.
   * \brief Read object.
   * \tparam T Type of object.
   * \return Read object.
   */
  template<typename T>
  T Read();

  /** Read an array-list from the buffer.
   * \brief Read array list.
   * \tparam T Type of objects in list.
   * \return Read list.
   */
  template<typename T>
  ArrayList<T> ReadArrayList();

  /** Read a std::vector from the buffer.
   * \brief Read vector.
   * \tparam T Type of objects in vector.
   * \return Read vector.
   */
  template<typename T>
  std::vector<T> ReadStdVector();

  /** Read a std::unordered_map from the buffer.
   * \brief Read map.
   * \tparam K Key type.
   * \tparam V Value type.
   * \return Read map.
   */
  template<typename K, typename V>
  std::unordered_map<K, V> ReadStdUnorderedMap();

  /** Returns the current read offset in the underlying buffer.
   * \brief Returns read offset.
   * \return Read offset.
   */
  u64 GetOffset() const { return mReadOffset; }
};

// -------------------------------------------------------------------------- //

template<typename T>
T
MemoryReader::Read()
{
  return T::FromBytes(*this);
}

// -------------------------------------------------------------------------- //

template<>
s8 inline MemoryReader::Read()
{
  const s8* bytes = reinterpret_cast<const s8*>(ReadBytes(sizeof(s8)));
  return *bytes;
}

// -------------------------------------------------------------------------- //

template<>
u8 inline MemoryReader::Read()
{
  const u8* bytes = ReadBytes(sizeof(s8));
  return *bytes;
}

// -------------------------------------------------------------------------- //

template<>
s16 inline MemoryReader::Read()
{
  const s16* data = reinterpret_cast<const s16*>(ReadBytes(sizeof(s16)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
u16 inline MemoryReader::Read()
{
  const u16* data = reinterpret_cast<const u16*>(ReadBytes(sizeof(u16)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
s32 inline MemoryReader::Read()
{
  const s32* data = reinterpret_cast<const s32*>(ReadBytes(sizeof(s32)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
u32 inline MemoryReader::Read()
{
  const u32* data = reinterpret_cast<const u32*>(ReadBytes(sizeof(u32)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
s64 inline MemoryReader::Read()
{
  const s64* data = reinterpret_cast<const s64*>(ReadBytes(sizeof(s64)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
u64 inline MemoryReader::Read()
{
  const u64* data = reinterpret_cast<const u64*>(ReadBytes(sizeof(u64)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
f32 inline MemoryReader::Read()
{
  const f32* data = reinterpret_cast<const f32*>(ReadBytes(sizeof(f32)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
f64 inline MemoryReader::Read()
{
  const f64* data = reinterpret_cast<const f64*>(ReadBytes(sizeof(f64)));
#if ALFLIB_HOST_ENDIAN == ALFLIB_LITTLE_ENDIAN
  return *data;
#else
  return SwapEndian(*data);
#endif
}

// -------------------------------------------------------------------------- //

template<>
String inline MemoryReader::Read()
{
  u32 size = Read<u32>();
  const char8* data = reinterpret_cast<const char8*>(ReadBytes(size));
  return String(data, size);
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>
MemoryReader::ReadArrayList()
{
  const u64 size = Read<u64>();
  ArrayList<T> list;
  list.Resize(size);
  for (u64 i = 0; i < size; i++) {
    list[i] = Read<T>();
  }
  return list;
}

// -------------------------------------------------------------------------- //

template<typename T>
std::vector<T>
MemoryReader::ReadStdVector()
{
  const u64 size = Read<u64>();
  std::vector<T> list;
  list.resize(size);
  for (u64 i = 0; i < size; i++) {
    list[i] = Read<T>();
  }
  return list;
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
std::unordered_map<K, V>
MemoryReader::ReadStdUnorderedMap()
{
  std::unordered_map<K, V> map;
  u64 size = Read<u64>();
  for (u64 i = 0; i < size; i++) {
    K key = Read<K>();
    map[key] = Read<V>();
  }
  return map;
}

}
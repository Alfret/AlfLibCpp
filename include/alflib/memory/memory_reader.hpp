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

  /** Read a value of the type s8.
   * \brief Read s8.
   * \return Read value.
   */
  template<>
  s8 Read();

  /** Read a value of the type u8.
   * \brief Read u8.
   * \return Read value.
   */
  template<>
  u8 Read();

  /** Read a value of the type s16.
   * \brief Read s16.
   * \return Read value.
   */
  template<>
  s16 Read();

  /** Read a value of the type u16.
   * \brief Read u16.
   * \return Read value.
   */
  template<>
  u16 Read();

  /** Read a value of the type s32.
   * \brief Read s32.
   * \return Read value.
   */
  template<>
  s32 Read();

  /** Read a value of the type u32.
   * \brief Read u32.
   * \return Read value.
   */
  template<>
  u32 Read();

  /** Read a value of the type s64.
   * \brief Read s64.
   * \return Read value.
   */
  template<>
  s64 Read();

  /** Read a value of the type u64.
   * \brief Read u64.
   * \return Read value.
   */
  template<>
  u64 Read();

  /** Read a value of the type f32.
   * \brief Read f32.
   * \return Read value.
   */
  template<>
  f32 Read();

  /** Read a value of the type f64.
   * \brief Read f64.
   * \return Read value.
   */
  template<>
  f64 Read();

  /** Read a string from the buffer.
   * \note This function is compatible with the 'const char8*' version of the
   * corresponding function on the writer. This means that this function can be
   * used to read strings that were written as 'const char8*'.
   * \brief Read string.
   * \return Read string.
   */
  template<>
  String Read();

  /** Read an array-list from the buffer.
   * \brief Read array list.
   * \tparam T Type of objects in list.
   * \return Read list.
   */
  template<typename T>
  ArrayList<T> ReadArrayList();

  template<typename K, typename V>
  std::unordered_map<K, V> ReadStdUnorderedMap();
};

// -------------------------------------------------------------------------- //

template<typename T>
T
MemoryReader::Read()
{
  return T::FromBytes(*this);
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
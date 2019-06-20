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

  template<typename T>
  T Read();

  template<>
  s8 Read();

  template<>
  u8 Read();

  template<>
  s16 Read();

  template<>
  u16 Read();

  template<>
  s32 Read();

  template<>
  u32 Read();

  template<>
  s64 Read();

  template<>
  u64 Read();

  template<>
  f32 Read();

  template<>
  f64 Read();

  template<>
  String Read();

  template<typename T>
  ArrayList<T> ReadArrayList();
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

}
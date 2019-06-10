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

// Library headers
#include <doctest/doctest.h>

// Project headers
#include "alflib/common.hpp"
#include "alflib/unique_pointer.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

/** Datastructure for UniquePointer tests **/
struct Data
{
  s32 i0;
  s32 i1;
  Data(s32 i0, s32 i1)
    : i0(i0)
    , i1(i1)
  {}
};

// -------------------------------------------------------------------------- //

TEST_CASE("[UniquePointer] - Make")
{
  using namespace alflib;

  auto p = UniquePointer<Data>::Make(32, 240);
  CHECK(p->i0 == 32);
  CHECK(p->i1 == 240);
}

}
}
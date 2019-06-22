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

// Library headers
#include <doctest/doctest.h>

// Project headers
#include "alflib/collection/robin_hood_map.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[RobinHoodMap] - Construct()")
{
  CHECK(true);

  RobinHoodMap<s32, s32> map;
  map[2] = 1;
  map[34] = 2;
  map[66] = 3;
  map[35] = 4;
  map[36] = 5;
  map[65] = 6;
  map[67] = 7;

  CHECK(map[2] == 1);
  CHECK(map[34] == 2);
  CHECK(map[66] == 3);
  CHECK(map[35] == 4);
  CHECK(map[36] == 5);
  CHECK(map[65] == 6);
  CHECK(map[67] == 7);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[RobinHoodMap] - Insert()")
{
  CHECK(true);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[RobinHoodMap] - Get()")
{
  CHECK(true);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[RobinHoodMap] - HasKey()")
{
  CHECK(true);
}

}
}
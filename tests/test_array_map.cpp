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
#include "alflib/collection/array_map.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[ArrayMap] - Construct")
{
  ArrayMap<String, s32> map;
  CHECK(map.GetSize() == 0);
  map["first"] = 22;
  map["second"] = 37;
  CHECK(map.GetSize() == 2);

  CHECK(map.HasKey("first"));
  CHECK(map.HasKey("second"));
  CHECK(!map.HasKey("third"));

  CHECK(map["first"] == 22);
  CHECK(map["second"] == 37);

  map.Remove("first");
  CHECK(map.GetSize() == 1);
  CHECK(!map.HasKey("first"));

  CHECK(map["second"] == 37);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[ArrayMap] - Entry creation")
{
  ArrayMap<String, u32> map;

  String key0 = "first";
  u32 val0 = 1;
  map[key0] = val0;

  map[String{ "second" }] = 2;
}

}
}
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
#include "alflib/collection/array_list.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

struct Element
{
  static u32 liveCount;
  s32 i;
  Element()
    : i(0)
  {
    liveCount++;
  }
  Element(s32 i)
    : i(i)
  {
    liveCount++;
  }
  Element(const Element&) = delete;
  Element(Element&& other)
  {
    i = other.i;
    liveCount++;
  }
  Element& operator=(const Element&) = delete;
  Element& operator=(Element&& other) = delete;
  ~Element() { liveCount--; }
};

// -------------------------------------------------------------------------- //

u32 Element::liveCount = 0;

// -------------------------------------------------------------------------- //

TEST_CASE("[ArrayList] - Create")
{
  const ArrayList<Element> l0;
  CHECK(l0.GetSize() == 0);

  const ArrayList<Element> l1(10);
  CHECK(l1.GetSize() == 0);
  CHECK(l1.GetCapacity() == 10);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[ArrayList] - Append")
{
  u32 liveCount = Element::liveCount;
  {
    constexpr u32 count = 16;

    ArrayList<Element> list;
    CHECK(list.GetSize() == 0);

    for (u32 i = 0; i < count; ++i) {
      list.Append(Element(i));
    }

    CHECK(list.GetSize() == count);
    CHECK(list.GetCapacity() >= count);
  }
  CHECK(liveCount == Element::liveCount);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[ArrayList] - Prepend") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[ArrayList] - Remove")
{
  u32 liveCount = Element::liveCount;
  {
    constexpr u32 count = 16;

    ArrayList<Element> list;
    CHECK(list.GetSize() == 0);

    for (u32 i = 0; i < count; ++i) {
      list.Append(Element(i));
    }

    CHECK(list.GetSize() == count);
    CHECK(list.GetCapacity() >= count);

    while (list.GetSize() > 0) {
      list.Remove(0);
    }

    CHECK(list.GetSize() == 0);
  }
  CHECK(liveCount == Element::liveCount);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[ArrayList] - Iterator")
{
  ArrayList<Element> list;
  list.AppendEmplace(Element{ 1 });
  list.AppendEmplace(Element{ 3 });
  list.AppendEmplace(Element{ 5 });
  list.AppendEmplace(Element{ 7 });
  CHECK(list.GetSize() == 4);
  CHECK(list.GetCapacity() >= 4);
  s32 index = 0;
  for (auto& e : list) {
    if (index == 0) {
      CHECK(e.i == 1);
    } else if (index == 1) {
      CHECK(e.i == 3);
    } else if (index == 2) {
      CHECK(e.i == 5);
    } else if (index == 3) {
      CHECK(e.i == 7);
    }
    index++;
  }
}

}
}

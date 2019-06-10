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

#include "alflib/file/path.hpp"
#include <doctest/doctest.h>

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[Path] - Create")
{
  // Normal cases
  Path p0(".");
  CHECK(p0.GetPath() == ".");
  Path p1("..");
  CHECK(p1.GetPath() == "..");

  // Trailing separator
  Path p2("./");
  CHECK(p2.GetPath() == ".");
  Path p3("../");
  CHECK(p3.GetPath() == "..");

  // Wrong separator
  Path p4("this/is/a/path");
#if defined(_WIN32)
  CHECK(p4.GetPath() == "this\\is\\a\\path");
#else
  CHECK(p4.GetPath() == "this/is/a/path");
#endif

  // Mixed separators
  Path p5("this/is/a\\path");
  CHECK(p5 == Path("this\\is\\a\\path"));
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Path] - Join")
{
  Path p0("this/is");
  p0.Join(Path("a/path"));
  CHECK(p0.GetPath() == "this\\is\\a\\path");

  Path p1("this/is");
  p1.Join(Path("/a/path"));
  CHECK(p1.GetPath() == "this\\is\\a\\path");
}

// -------------------------------------------------------------------------- //



}
}
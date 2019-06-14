// MIT License
//
// Copyright (c) 2019 Filip Bj�rklund
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
  CHECK(p0 == Path{ "this\\is\\a\\path" });

  Path p1("this/is");
  p1.Join(Path("/a/path"));
  CHECK(p1 == Path{ "this\\is\\a\\path" });
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Path] - Components")
{
  Path p0("Path/to\\some/file.txt");
  ArrayList<String> c0 = p0.GetComponents();
  CHECK(c0.Contains("Path"));
  CHECK(c0.Contains("to"));
  CHECK(c0.Contains("some"));
  CHECK(c0.Contains("file.txt"));

  Path p1("Path/to\\some/file/");
  ArrayList<String> c1 = p1.GetComponents();
  CHECK(c1.Contains("Path"));
  CHECK(c1.Contains("to"));
  CHECK(c1.Contains("some"));
  CHECK(c1.Contains("file"));
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Path] - GetName")
{
  CHECK(Path{ "file.txt" }.GetName() == "file.txt");
  CHECK(Path{ "file" }.GetName() == "file");
  CHECK(Path{ "path/to/file.txt" }.GetName() == "file.txt");
  CHECK(Path{ "path/to/.hidden/file.txt" }.GetName() == "file.txt");
  CHECK(Path{ "path/to/.hidden/file" }.GetName() == "file");
  CHECK(Path{ "path/to/my.dir/file.txt" }.GetName() == "file.txt");
  CHECK(Path{ "path/to/my.dir/file" }.GetName() == "file");
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Path] - GetBaseName")
{
  CHECK(Path{ "file.txt" }.GetBaseName() == "file");
  CHECK(Path{ "file" }.GetBaseName() == "file");
  CHECK(Path{ "path/to/file.txt" }.GetBaseName() == "file");
  CHECK(Path{ "path/to/.hidden/file.txt" }.GetBaseName() == "file");
  CHECK(Path{ "path/to/.hidden/file" }.GetBaseName() == "file");
  CHECK(Path{ "path/to/my.dir/file.txt" }.GetBaseName() == "file");
  CHECK(Path{ "path/to/my.dir/file" }.GetBaseName() == "file");
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Path] - GetExtensionString")
{
  // Normal cases
  CHECK(Path{ "file.txt" }.GetExtensionString() == ".txt");
  CHECK(Path{ "image.png" }.GetExtensionString() == ".png");
  CHECK(Path{ "file." }.GetExtensionString() == "");
  CHECK(Path{ "path/to/file.txt" }.GetExtensionString() == ".txt");
  CHECK(Path{ "path/to/archive.tar" }.GetExtensionString() == ".tar");
  CHECK(Path{ "path/to/.hidden/file.txt" }.GetExtensionString() == ".txt");
  CHECK(Path{ "path/to/.hidden/file" }.GetExtensionString() == "");

  // Normal cases type
  CHECK(Path{ "file.txt" }.GetExtensionString() == ".txt");
  CHECK(Path{ "image.png" }.GetExtensionString() == ".png");
  CHECK(Path{ "file." }.GetExtensionString() == "");
  CHECK(Path{ "path/to/file.txt" }.GetExtensionString() == ".txt");
  CHECK(Path{ "path/to/archive.tar" }.GetExtensionString() == ".tar");
  CHECK(Path{ "path/to/.hidden/file.txt" }.GetExtensionString() == ".txt");
  CHECK(Path{ "path/to/.hidden/file" }.GetExtensionString() == "");
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Path] - GetExtension")
{

  const Path p3("file.txt");
  CHECK(p3.GetExtension() == Path::Extension::kTxt);
  const Path p4("path/to/some.txt");
  CHECK(p4.GetExtension() == Path::Extension::kTxt);
  const Path p5("path/to/file");
  CHECK(p5.GetExtension() == Path::Extension::kNone);
}

}
}
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
#include "alflib/file/file.hpp"
#include "alflib/file/file_io.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[File] - Enumerate")
{
  // Directory
  File f0("../../tests/res");
  CHECK(f0.Exists());
  CHECK(f0.GetType() == File::Type::kDirectory);
  if (f0.GetType() == File::Type::kDirectory) {
    ArrayList<File> files = f0.Enumerate();
    CHECK(files.Contains(File{ "some_dir" }));
    CHECK(files.Contains(File{ "some.txt" }));
    CHECK(files.Contains(File{ "an_archive.zip" }));
  }

  // Archive
  File f1("../../tests/res/an_archive.zip");
  CHECK(f1.Exists());
  CHECK(f1.GetType() == File::Type::kArchive);
  if (f1.GetType() == File::Type::kArchive) {
    ArrayList<File> files = f1.Enumerate();
    CHECK(files.Contains(File{ "file_inside.txt" }));
    CHECK(files.Contains(File{ "some_other.txt" }));
  }
}

// -------------------------------------------------------------------------- //

TEST_CASE("[File] - Create")
{
  // File f0("../../a_file.txt");
  // FileResult r0 = f0.Create(File::Type::kFile);

  // File f1("../../a_dir");
  // FileResult r1 = f1.Create(File::Type::kDirectory);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[FileIO] - Open") {}

// -------------------------------------------------------------------------- //

TEST_CASE("[FileIO] - Read")
{
  FileIO f0("../../tests/res/smile.txt");
  FileResult result = f0.Open(FileIO::Flag::kRead);
  CHECK(result == FileResult::kSuccess);

  String c0;
  result = f0.Read(c0);
  CHECK(result == FileResult::kSuccess);
  CHECK(c0.GetLength() == 8);
}

}
}
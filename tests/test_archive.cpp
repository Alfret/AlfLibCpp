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
#include "alflib/file/archive.hpp"
#include "alflib/file/file.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[Archive] - Open")
{
  // Tar Archive
  Archive a1(Path{ "tests/res/taping.tar" });
  FileResult result = a1.Open();
  CHECK(result == FileResult::kSuccess);
  if (result == FileResult::kSuccess) {
    ArrayList<File> files = a1.Enumerate();
    CHECK(files.Contains(File{ "inside_tar.txt" }));
    CHECK(files.Contains(File{ "also_in_tar.txt" }));
    CHECK(files.Contains(File{ "tar_img.png" }));
  }

  // Zip Archive
  Archive a2(Path{ "tests/res/an_archive.zip" });
  result = a2.Open();
  CHECK(result == FileResult::kSuccess);
  if (result == FileResult::kSuccess) {
    ArrayList<File> files = a2.Enumerate();
    CHECK(files.Contains(File{ "file_inside.txt" }));
    CHECK(files.Contains(File{ "some_other.txt" }));
  }
}

}
}
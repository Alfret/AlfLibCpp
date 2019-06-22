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
#include "alflib/graphics/image.hpp"
#include "alflib/file/file.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[Image] - Load")
{
  // Load image
  Image image;
  Image::Result result = image.Load(Path{ "res/test_image.png" });
  CHECK(result == Image::Result::kSuccess);
  CHECK(image.GetWidth() == 32);
  CHECK(image.GetHeight() == 40);
  CHECK(image.GetFormat() == Image::Format::kRGB);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Image] - Save")
{
  // Save image
  Image image;
  Image::Result result = image.Load(Path{ "res/test_image.png" });
  CHECK(result == Image::Result::kSuccess);
  CHECK(image.Save(Path{ "res/test_image_other.tga" }) ==
        Image::Result::kSuccess);

  // Cleanup
  File file(Path{ "res/test_image_other.tga" });
  CHECK(file.Delete() == FileResult::kSuccess);
}

// -------------------------------------------------------------------------- //

TEST_CASE("[Image] - Blit")
{
  // Create src images
  Image im0;
  im0.Create(8, 8);
  im0.Fill(Color::RED);
  Image im1;
  im1.Create(8, 8);
  im1.Fill(Color::MAGENTA);
  Image im2;
  im2.Create(8, 8);
  im2.Fill(Color::CORNFLOWER_BLUE);
  CHECK(im2.GetPixel(0, 0) == Color::CORNFLOWER_BLUE);

  // Create destination image
  Image dst;
  dst.Create(32, 32);
  dst.Fill(Color::WHITE);

  // Blit images
  dst.Blit(im0, 0, 0);
  dst.Blit(im1, 8, 0);
  dst.Blit(im2, 24, 0);

  CHECK(dst.GetPixel(2, 7) == Color::RED);
  CHECK(dst.GetPixel(9, 4) == Color::MAGENTA);
  CHECK(dst.GetPixel(13, 0) == Color::MAGENTA);
  CHECK(dst.GetPixel(27, 6) == Color::CORNFLOWER_BLUE);

  // Save image
  dst.Save(Path{ "res/atlas.tga" }, true);
  CHECK(File(Path{ "res/atlas.tga" }).Exists());
}

}
}
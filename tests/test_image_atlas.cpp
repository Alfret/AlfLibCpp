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
#include "alflib/graphics/image_atlas.hpp"

// ========================================================================== //
// Tests
// ========================================================================== //

namespace alflib {
namespace tests {

TEST_CASE("[ImageAtlas] - Construct")
{
  // Create some images
  Image imageRed;
  imageRed.Create(8, 8);
  imageRed.Fill(Color::RED);
  Image imageGreen;
  imageGreen.Create(8, 8);
  imageGreen.Fill(Color::GREEN);
  Image imageMagenta;
  imageMagenta.Create(8, 8);
  imageMagenta.Fill(Color::MAGENTA);
  Image imageBlue;
  imageBlue.Create(8, 8);
  imageBlue.Fill(Color::BLUE);
  Image imageYellow;
  imageYellow.Create(8, 8);
  imageYellow.Fill(Color::YELLOW);

  // Create atlas
  ImageAtlas atlas;
  ImageAtlas<>::Result result = atlas.Build(
    { &imageRed, &imageGreen, &imageMagenta, &imageBlue, &imageYellow },
    { "red", "green", "magenta", "blue", "yellow" },
    32,
    32);
  CHECK(result == ImageAtlas<>::Result::kSuccess);
  atlas.GetImage().Save(Path{ "res/out/image_atlas.tga" }, true);
}

}
}
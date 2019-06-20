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

#include "alflib/graphics/image.hpp"

// ========================================================================== //
// Headers
// ========================================================================== //

// stb_image header
#define STBI_ASSERT(x) AlfAssert(x, "Assertion failed in library stb_image")
#define STBI_NO_STDIO
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// stb_image_write header
#define STBIW_ASSERT(x) AlfAssert(x, "Assertion failed in library stb_image")
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb/stb_image_write.h>

// stb_image_resize header
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STBIR_ASSERT(x)                                                        \
  AlfAssert(x, "Assertion failed in library stb_image_resize")
#include <stb/stb_image_resize.h>

// ========================================================================== //
// Functions
// ========================================================================== //

namespace alflib {}

// ========================================================================== //
// Image Implementation
// ========================================================================== //

namespace alflib {

Image::Image(const Path& path, Image::Format format, Allocator& allocator)
  : mAllocator(allocator)
{}

// -------------------------------------------------------------------------- //

Image::Image(u32 width,
             u32 height,
             Format format,
             const u8* data,
             Format dataFormat,
             Allocator& allocator)
  : mAllocator(allocator)
{}

// -------------------------------------------------------------------------- //

Image::Image(const Image& other)
  : mWidth(other.mWidth)
  , mHeight(other.mHeight)
  , mFormat(other.mFormat)
  , mAllocator(other.mAllocator)
{
  mData = static_cast<u8*>(mAllocator.Alloc(mDataSize));
  memcpy(mData, other.mData, mDataSize);
  mDataSize = other.mDataSize;
}

// --------------------------------------------------------------------------
// //

Image::Image(Image&& other)
  : mWidth(other.mWidth)
  , mHeight(other.mHeight)
  , mFormat(other.mFormat)
  , mAllocator(other.mAllocator)
  , mData(other.mData)
  , mDataSize(other.mDataSize)
{
  other.mData = nullptr;
  other.mDataSize = 0;
}

// -------------------------------------------------------------------------- //

Image::~Image()
{
  mAllocator.Free(mData);
}

// -------------------------------------------------------------------------- //

Image&
Image::operator=(const Image& other)
{
  if (this != &other) {
  }
  return *this;
}

// -------------------------------------------------------------------------- //

Image&
Image::operator=(Image&& other)
{
  if (this != &other) {
  }
  return *this;
}

}
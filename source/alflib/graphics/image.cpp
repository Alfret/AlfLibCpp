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

// Project headers
#include "alflib/file/file_io.hpp"

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

namespace alflib {

Image::Result
LoadImageData(const Path& path,
              u32* widthOut,
              u32* heightOut,
              Image::Format* formatOut,
              u8** dataOut,
              u64* dataSizeOut,
              Allocator& allocator)
{
  // Open image file
  File imageFile(path);
  FileIO io(imageFile);
  FileResult fresult = io.Open(FileIO::Flag::kRead | FileIO::Flag::kShareRead);
  if (fresult != FileResult::kSuccess) {
    return Image::Result::kFileNotFound;
  }

  // Read file
  u64 size = imageFile.GetSize();
  u64 read;
  u8* buffer = allocator.NewArray<u8>(size);
  fresult = io.Read(buffer, size, read);
  if (fresult != FileResult::kSuccess) {
    allocator.Delete(buffer);
    return Image::Result::kFileNotFound;
  }

  // Parse file
  s32 x, y, c;
  stbi_uc* imageData =
    stbi_load_from_memory(buffer, size, &x, &y, &c, STBI_default);
  *widthOut = x;
  *heightOut = y;

  // Determine format and data size
  *formatOut = Image::Format::kUnknown;
  if (c == 1) {
    *formatOut = Image::Format::kGrayscale;
  }
  if (c == 3) {
    *formatOut = Image::Format::kRGB;
  }
  if (c == 4) {
    *formatOut = Image::Format::kRGBA;
  }
  *dataSizeOut = x * y * Image::BytesPerPixel(*formatOut);

  // Copy data to use correct allocator
  // TODO(Filip Björklund): Don't do this copy!
  *dataOut = allocator.NewArray<u8>(*dataSizeOut);
  memcpy(*dataOut, imageData, *dataSizeOut);

  return Image::Result::kSuccess;
}

}

// ========================================================================== //
// Image Implementation
// ========================================================================== //

namespace alflib {

Image::Image(Allocator& allocator)
  : mAllocator(allocator)
{}

// -------------------------------------------------------------------------- //

Image::Result
Image::Load(const Path& path, Image::Format format)
{
  // Load image data
  Result result = LoadImageData(
    path, &mWidth, &mHeight, &mFormat, &mData, &mDataSize, mAllocator);
  if (result != Result::kSuccess) {
    return result;
  }

  // Convert if neccessary
  if (mFormat != format) {
    // TODO(Filip Björklund): Convert
  }

  return Result::kSuccess;
}

// -------------------------------------------------------------------------- //

Image::Result
Image::Create(u32 width,
              u32 height,
              Image::Format format,
              const u8* data,
              Image::Format dataFormat)
{
  mWidth = width;
  mHeight = height;
  mFormat = format;

  if (format == dataFormat) {
    mDataSize = mWidth * mHeight * BytesPerPixel(mFormat);
    mData = mAllocator.NewArray<u8>(mDataSize);
    memcpy(mData, data, mDataSize);
  } else {
    // TODO(Filip Björklund): Do conversion and then assign converted image
  }

  return Result::kSuccess;
}
// -------------------------------------------------------------------------- //

Image::Image(const Image& other)
  : mWidth(other.mWidth)
  , mHeight(other.mHeight)
  , mFormat(other.mFormat)
  , mAllocator(other.mAllocator)
{
  if (other.mData) {
    mData = static_cast<u8*>(mAllocator.Alloc(mDataSize));
    memcpy(mData, other.mData, mDataSize);
    mDataSize = other.mDataSize;
  }
}

// -------------------------------------------------------------------------- //

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
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mFormat = other.mFormat;
    mAllocator = other.mAllocator;
    mData = other.mData;
    mDataSize = other.mDataSize;
    if (other.mData) {
      mData = static_cast<u8*>(mAllocator.Alloc(mDataSize));
      memcpy(mData, other.mData, mDataSize);
      mDataSize = other.mDataSize;
    }
  }
  return *this;
}

// -------------------------------------------------------------------------- //

Image&
Image::operator=(Image&& other)
{
  if (this != &other) {
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mFormat = other.mFormat;
    mAllocator = other.mAllocator;
    mData = other.mData;
    mDataSize = other.mDataSize;
    other.mData = nullptr;
    other.mDataSize = 0;
  }
  return *this;
}

// -------------------------------------------------------------------------- //

u32
Image::BytesPerPixel(Image::Format format)
{
  switch (format) {
    case Format::kUnknown:
      return 0;
    case Format::kGrayscale:
      return 1;
    case Format::kRGBA:
      return 4;
    case Format::kRGB:
      return 3;
    case Format::kBGRA:
      return 4;
    case Format::kBGR:
      return 3;
  }
}

}
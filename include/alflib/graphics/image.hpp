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

// Project headers
#include "alflib/file/path.hpp"

// ========================================================================== //
// Image Declaration
// ========================================================================== //

namespace alflib {

/** \class Image
 * \author Filip Björklund
 * \date 01 januari 2019 - 00:00
 * \brief Image.
 * \details
 * Class that represents an image.
 */
class Image
{
public:
  /** Enumeration of image formats  **/
  enum class Format
  {
    /** Unknown format. It's only used as an argument to functions, images
       cannot exist in this format **/
    kUnknown,
    /** Grayscale format **/
    kGrayscale,
    /** RGBA format **/
    kRGBA,
    /** RGB format **/
    kRGB,
    /** BGRA format **/
    kBGRA,
    /** BGR format **/
    kBGR
  };

private:
  /** Width of the image in pixels **/
  u32 mWidth;
  /** Height of the image in pixels **/
  u32 mHeight;
  /** Format of the image **/
  Format mFormat;

  /** Allocator **/
  Allocator& mAllocator;
  /** Image data **/
  u8* mData;
  /** Size of image data in bytes **/
  u64 mDataSize;

public:
  /** Construct an image by loading the data from a file at the specified path.
   * \brief Construct image by loading from file.
   * \param path Path to image file.
   * \param format Format of the image.
   * \param allocator Allocator to allocate the data with.
   */
  explicit Image(const Path& path,
                 Format format = Format::kUnknown,
                 Allocator& allocator = DefaultAllocator::Instance());

  /** Construct an empty image from the specified dimensions and format. Data
   * for the image can also be specified, along with a format for the data.
   * \note The data is copied by the image if it's not null, therefore the data
   * is still owned by the caller.
   * \note If the data format is Format::kUnknown, then the data is assumed to
   * have the same format as the constructed image.
   * \pre Width must be greater than zero.
   * \pre Height must be greater than zero.
   * \pre Format cannot be unknown.
   * \brief Construct empty image.
   * \param width Width of the image.
   * \param height Height of the image.
   * \param format Format of the image.
   * \param data Data to initialize image from. If the data format is not
   * Format::kUnknown and the format does no match the image format then the
   * data is converted to the correct format before being used to initialize the
   * image.
   * \param dataFormat Format of the data.
   * \param allocator Allocator to allocate the data with.
   */
  Image(u32 width,
        u32 height,
        Format format,
        const u8* data = nullptr,
        Format dataFormat = Format::kUnknown,
        Allocator& allocator = DefaultAllocator::Instance());

  Image(const Image& other);

  Image(Image&& other);

  ~Image();

  Image& operator=(const Image& other);

  Image& operator=(Image&& other);
};

}
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
  /** Results enumeration **/
  enum class Result
  {
    /** Success **/
    kSuccess,
    /** Failed allocation **/
    kOutOfMemory,
    /** Image file could not be found **/
    kFileNotFound,
  };

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
  u32 mWidth = 0;
  /** Height of the image in pixels **/
  u32 mHeight = 0;
  /** Format of the image **/
  Format mFormat = Format::kUnknown;

  /** Allocator **/
  Allocator& mAllocator;
  /** Image data **/
  u8* mData = nullptr;
  /** Size of image data in bytes **/
  u64 mDataSize = 0;

public:
  /** Construct an empty image without dimensions and data. The image data must
   * either be setup by a call to Image::Load(...), to load from a file, or by a
   * call to Image::Create(...), to create the image from data.
   * \param allocator Allocator to allocate data with.
   */
  explicit Image(Allocator& allocator = DefaultAllocator::Instance());

  /** Load the image data from a file at the specified path. An optional format
   * can be specified that the data should be converted to after loading it from
   * the file. If the format is Format::kUnknown (default) then the format is
   * determined from the file.
   * \param path Path to the image file.
   * \param format Format to store the image in. If the format Format::kUnknown
   * is specified then the image is stored in the format determined by the file.
   * \return Result.
   * Result::kSuccess: Successfully loaded image data from file.
   * Result::kFileNotFound: Failed to find the image file.
   * Result::kOutOfMemory: Failed to allocate memory for the image data.
   */
  Result Load(const Path& path, Format format = Format::kUnknown);

  /** Create the image data from the specified dimensions and format. Data for
   * the image can also be specified, along with a format for the data.
   * \note The data is copied by the image if it's not null, therefore the data
   * is still owned by the caller.
   * \note If the data format is Format::kUnknown, then the data is assumed to
   * have the same format as the constructed image.
   * \note The data is expected to be at least the size that is required by the
   * image (width * height * format-bytes-per-pixel). Any size less than that
   * gives undefined behaviour.
   * \pre Width must be greater than zero.
   * \pre Height must be greater than zero.
   * \pre Format cannot be unknown.
   * \brief Create image data.
   * \param width Width of the image.
   * \param height Height of the image.
   * \param format Format of the image.
   * \param data Data to initialize image from. If the data format is not
   * Format::kUnknown and the format does no match the image format then the
   * data is converted to the correct format before being used to initialize the
   * image.
   * \param dataFormat Format of the data.
   * \return Result.
   * Result::kSuccess: Successfully loaded image data from file.
   * Result::kOutOfMemory: Failed to allocate memory for the image data.
   */
  Result Create(u32 width,
                u32 height,
                Format format,
                const u8* data = nullptr,
                Format dataFormat = Format::kUnknown);

  /** Copy-constructor **/
  Image(const Image& other);

  /** Move-constructor **/
  Image(Image&& other);

  /** Destruct image and free data **/
  ~Image();

  /** Copy-assignment **/
  Image& operator=(const Image& other);

  /** Move-assignment **/
  Image& operator=(Image&& other);

public:
  /** Returns the number of bytes that are required to store a single pixel in
   * the specified format
   * \brief Returns bytes per pixel for format.
   * \param format Format to get bytes per pixel for.
   * \return Bytes per pixel.
   */
  static u32 BytesPerPixel(Format format);
};

}
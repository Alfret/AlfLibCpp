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

// Project headers
#include "alflib/common.hpp"
#include "alflib/macros.hpp"
#include "alflib/file/result.hpp"
#include "alflib/file/file.hpp"

// ========================================================================== //
// FileIO Declaration
// ========================================================================== //

namespace alflib {

/** \class FileIO
 * \author Filip Bj�rklund
 * \date 09 juni 2019 - 19:53
 * \brief
 * \details
 */
class FileIO
{
private:
  /** File that IO handle is operating on **/
  File mFile;

#if defined(ALFLIB_TARGET_WINDOWS)
  /** Handle **/
  HANDLE mFileHandle = INVALID_HANDLE_VALUE;
#else
  /** Handle **/
  File* mHandle = nullptr;
#endif

  /** Whether the file is open **/
  bool mIsOpen = false;

public:
  /** Flags that can be specified when opening the file handle **/
  enum class Flag : u32
  {
    /** Open file with read access **/
    kRead,
    /** Open file with write access **/
    kWrite,
    /** Open file with read and write access **/
    kReadWrite = kRead | kWrite,
    /** Open file with shared read access **/
    kShareRead,
    /** Open file with shared write access **/
    kShareWrite,
    /** Open file with shared read and write access **/
    kShareReadWrite = kShareRead | kShareWrite,
    /** Create the file if it does not already exists **/
    kCreate,
    /** Overwrite file if it already exists **/
    kOverwrite,
    /** Open file with cursor at the end for appending **/
    kAppend
  };
  ALFLIBCPP_ENUM_CLASS_OPERATORS(friend, Flag, u32);

public:
  /** Create a file IO handle for performing operations on a file in the 
   * filesystem. This function does not open the file, instead it only sets up 
   * the handle. Call FileIO::Open(FileIO::Flag) to open the file.
   * \brief Create file IO handle.
   * \param[in] file File to create handle for.
   */
  FileIO(File file);

  /** Create a file IO handle for performing operations on a file in the
   * filesystem. This function does not open the file, instead it only sets up
   * the handle. Call FileIO::Open(FileIO::Flag) to open the file.
   * \brief Create file IO handle.
   * \param[in] path Path to file to create handle for.
   */
  FileIO(const Path& path);

  /** Create a file IO handle for performing operations on a file in the
   * filesystem. This function does not open the file, instead it only sets up
   * the handle. Call FileIO::Open(FileIO::Flag) to open the file.
   * \brief Create file IO handle.
   * \param[in] path Path to file to create handle for.
   */
  FileIO(const String& path);

  /** Destruct file IO handle. This also closes the file if it's still open.
   * \brief Destruct file IO handle.
   */
  ~FileIO();

  /** Open the file IO handle to start performing operations on the file.
   * \brief Open handle.
   * \param[in] flags Flags specifying how the file should be opened.
   * \return Restult.
   */
  FileResult Open(Flag flags);

  /** Close a file IO handle. No more operations may be performed on the handle
   * after this function has been called.
   * \brief Close handle.
   */
  void Close();

  /** Read data from the file into a buffer. The buffer and number of bytes must
   * be specified by the user. The number of read bytes are also returned as an 
   * output parameter.
   * \brief Read from file.
   * \param[in] buffer Buffer to read into.
   * \param[in] toRead Number of bytes to read.
   * \param[out] read Number of bytes read.
   * \return Result.
   */
  FileResult Read(u8* buffer, u64 toRead, u64& read);

  /** Write data from a buffer into the file. The buffer and number of bytes to
   * write must be specified by the user. The number of bytes that was 
   * successfully written is returned to the user in an output parameter.
   * \brief Write to file.
   * \param[in] buffer Buffer to write data from.
   * \param[in] toWrite Number of bytes to write.
   * \param[out] written Number of bytes written.
   * \return Result.
   */
  FileResult Write(const u8* buffer, u64 toWrite, u64& written);

  /** Returns whether or not the handle is currently open.
   * \brief Returns whether handle is open.
   * \return True if the handle is open otherwise false.
   */
  bool IsOpen() const { return mIsOpen; }

};

}
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
#include "alflib/common.hpp"
#include "alflib/macros.hpp"
#include "alflib/file/file_io.hpp"
#include "alflib/file/path.hpp"
#include "alflib/collection/array_list.hpp"
#include "alflib/platform.hpp"

// ========================================================================== //
// File Declaration
// ========================================================================== //

namespace alflib {

/** \class File
 * \author Filip Björklund
 * \date 07 juni 2019 - 20:31
 * \brief File handle.
 * \details
 *
 */
class File
{
  friend FileIO;

private:
  /** File path **/
  Path mPath;

#if defined(ALFLIB_TARGET_WINDOWS)
  /** Win32 file attributes **/
  WIN32_FILE_ATTRIBUTE_DATA mFileAttributes;
#endif

public:
  /** File results **/
  enum class Result
  {
    /** Success **/
    kSuccess,
    /** File was not found at the specified path **/
    kNotFound,
    /** File already exists at the specified path **/
    kAlreadyExists,
    /** Access was denied trying to access file at the specified path **/
    kAccessDenied,
  };

  /** Enumeration of file system object types **/
  enum class Type
  {
    /** File **/
    kFile,
    /** Directory **/
    kDirectory,
    /** Archive **/
    kArchive
  };

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
  /** Construct a file handle that represents the object at the specified path 
   * in the filesystem.
   * \note This operation does not actually open the file for reading. Instead 
   * File::OpenFile() function should be used to perform operations on files.
   * \brief Create file.
   * \param path Path to file.
   */
  File(const Path& path);

  /** Create a file handle that represents the object at the specified path in
   * the filesystem.
   * \note This operation does not actually open the file for reading. Instead
   * File::OpenFile() function should be used to perform operations on files.
   * \brief Create file.
   * \param path Path to file.
   */
  File(const String& path);

  /** Destruct file handle **/
  ~File() = default;

  /** Open a file relative to the current file.
   * \brief Open relative file.
   * \return File.
   */
  File Open(const Path& path);
 
  /** Open a file relative to the current file.
   * \brief Open relative file.
   * \return File.
   */
  File Open(const String& path);

  /** Open file to perform read/write operations on it.
   * \brief Open file.
   * \return File IO interface.
   */
  FileIO OpenFile(Flag flags);

  /** Enumerate all the files in a directory or archive.
   * \pre Type of file must be a directory.
   * \brief Enumerate files in directory or archive.
   * \return List of files.
   */
  ArrayList<File> Enumerate();

  /** Returns the path to the file.
   * \brief Returns path.
   * \return Path to file.
   */
  const Path& GetPath() const { return mPath; }

  /** Returns the type of the file.
   * \brief Returns file type.
   * \return Type of the file.
   */
  Type GetType() const;

private:
  /** Retrieve current file attributes **/
  void UpdateAttributes();

};

}
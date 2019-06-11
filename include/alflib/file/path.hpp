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
#include "alflib/collection/array_list.hpp"
#include "alflib/platform/platform.hpp"
#include "alflib/string.hpp"

// ========================================================================== //
// Path Declaration
// ========================================================================== //

namespace alflib {

/** \class Path
 * \author Filip Bj�rklund
 * \date 09 juni 2019 - 20:15
 * \brief Path.
 * \details
 * Represents a path in the filesystem.
 */
class Path
{
public:
  /** Enumeration of known directories **/
  enum class KnownDirectory
  {
    /** User home directory **/
    kHome,
    /** Desktop directory **/
    kDesktop,
    /** Documents directory **/
    kDocuments,
    /** Downloads directory **/
    kDownloads
  };

  /** List of known file extensions **/
  enum class Extension
  {
    /** No extension **/
    kNone,
    /** Unknown extension **/
    kUnknown,
    /** Text file **/
    kTxt,
    /** PNG image file **/
    kPng,
    /** Zip archive **/
    kZip,
  };

public:
  /** Path (relative) to current directory **/
  static const String CURRENT;
  /** Path (relative) to parent directory **/
  static const String PARENT;

  /** Path separator **/
  static const String SEPARATOR;

#if defined(ALFLIB_TARGET_WINDOWS)
  /** Path separator character (Windows) **/
  static constexpr u32 SEPARATOR_CHAR = '\\';
#else
  /** Path separator character **/
  static constexpr u32 SEPARATOR_CHAR = '/';
#endif

private:
  /** Path string **/
  String mPath;

public:
  /** Construct a path from a string.
   * \brief Construct path.
   * \param path
   */
  Path(const String& path = CURRENT);

  /** Join another path at the end of this path. This correctly insert a
   * separator between the path components.
   * \brief Join with another path.
   * \param other Path to join.
   * \return Reference to this.
   */
  Path& Join(const Path& other);

  /** Join another path at the end of this path. This correctly insert a
   * separator between the path components.
   * \brief Join with another path.
   * \param other Path to join.
   * \return Reference to this.
   */
  Path& operator+=(const Path& other);

  /** Returns the join of this path with another path. This correctly insert a
   * separator between the path components.
   * \brief Returns joined path.
   * \param other Path to join with.
   * \return Joined paths.
   */
  Path Joined(const Path& other) const;

  /** Returns the string that represents the path.
   * \brief Returns path string.
   * \return Path string.
   */
  const String& GetPath() const { return mPath; }

  /** Returns the path as an absolute path. This function also resolves any '.'
   * (current directory) and '..' (parent directory) components that may be part
   * of the path. For this reason this function may be costly and should not be
   * called when the absolute path is not actually needed.
   * \brief Returns absolute resolved path.
   * \return Absolute and resolved path.
   */
  Path GetAbsolutePath() const;

  /** Returns each of the path components that make up the path.
   * \brief Returns path components.
   * \return Path components.
   */
  ArrayList<String> GetComponents();

  /** Returns the name of the object at the path. This is the last component
   * and is returned without any extension.
   * \brief Returns name.
   * \return Name.
   */
  String GetName() const;

  /** Returns the extension of the path.
   * \brief Returns extension.
   * \return Extension.
   */
  Extension GetExtension() const;

  /** Returns the extension of the path as a string.
   * \brief Returns extension string.
   * \return Extension string.
   */
  String GetExtensionString() const;

  /** Returns whether or not two paths are equal.
   * \brief Returns whether paths are equal.
   * \param path0 First path.
   * \param path1 Second path.
   * \return True if the paths are equal otherwise false.
   */
  friend bool operator==(const Path& path0, const Path& path1);

  /** Returns whether or not two paths are not equal.
   * \brief Returns whether paths are unequal.
   * \param path0 First path.
   * \param path1 Second path.
   * \return True if the paths are not equal otherwise false.
   */
  friend bool operator!=(const Path& path0, const Path& path1);

  /** Returns two paths joined together.
   * \brief Returns joined paths.
   * \param path0 First path.
   * \param path1 Second path.
   * \return Joined paths.
   */
  friend Path operator+(const Path& path0, const Path& path1);

  /** Returns two paths joined together, the second created from a string.
   * \brief Returns joined paths.
   * \param path0 First path.
   * \param path1 Second path.
   * \return Joined paths.
   */
  friend Path operator+(const Path& path0, const String& path1);

private:
  /** This function sets up the separators in the path to be the correct for
   * the OS **/
  void FixSeparators();

public:
  /** Returns the path to a known directory of the specified type.
   * \brief Returns known directory path.
   */
  static Path GetKnownDirectory(KnownDirectory directory);
};

}
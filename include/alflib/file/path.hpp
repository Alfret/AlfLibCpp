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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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
#include "alflib/string.hpp"
#include "alflib/platform.hpp"

// ========================================================================== //
// Path Declaration
// ========================================================================== //

namespace alflib {

/** \class Path
 * \author Filip Björklund
 * \date 09 juni 2019 - 20:15
 * \brief Path.
 * \details
 * Represents a path in the filesystem.
 */
class Path
{
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

  /** Join another path at the end of this path.
   * \brief Join with another path.
   * \param other Path to join.
   * \return Reference to this.
   */
  Path& Join(const Path& other);

  /** Returns the join of this path with another path.
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

private:
  /** This function sets up the separators in the path to be the correct for 
   * the OS **/
  void FixSeparators();

};

}
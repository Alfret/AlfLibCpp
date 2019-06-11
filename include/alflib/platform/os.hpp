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
#include "alflib/platform/platform.hpp"

// ========================================================================== //
// Windows
// ========================================================================== //

#if defined(ALFLIB_TARGET_WINDOWS)

namespace alflib {

/** \class SharedLibraries
 * \author Filip Björklund
 * \date 10 juni 2019 - 23:31
 * \brief Windows shared libraries.
 * \details
 * Represents a collection of windows shared libraries that are loaded
 * dynamically the first time they are accessed instead of linking to them at
 * compile-time.
 */
class SharedLibraries
{
public:
  /** Functions from KernelBase.dll **/
  struct KernelBase
  {
    /** PathCchCanonicalizeEx type **/
    using PFN_PathCchCanonicalizeEx = HRESULT (*)(PWSTR, size_t, PCWSTR, ULONG);
    /** PathCchCanonicalizeEx function **/
    PFN_PathCchCanonicalizeEx pPathCchCanonicalizeEx;
  } mKernelBase;

public:

  /** Returns the collection of dynamically loaded functions from the KernelBase
   * library.
   * \brief Returns KernelBase functions.
   * \return Functions in KernelBase.
   */
  static const KernelBase& GetKernelBase() { return Instance().mKernelBase; }

private:
  /** Construct shared library object by loading all the modules **/
  SharedLibraries();

  /** Returns singleton instance to shared library object **/
  static SharedLibraries& Instance();

};

// -------------------------------------------------------------------------- //



}

#endif

// ========================================================================== //
// Linux
// ========================================================================== //

namespace alflib {
}
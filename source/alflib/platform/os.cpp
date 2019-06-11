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

#include "alflib/platform/os.hpp"

// ========================================================================== //
// Windows Functions
// ========================================================================== //

#if defined(ALFLIB_TARGET_WINDOWS)

namespace alflib {

SharedLibraries::SharedLibraries()
  : mKernelBase({})
{
  // Load KernelBase.dll
  const HMODULE module = LoadLibraryW(L"KernelBase.dll");
  if (module) {
    mKernelBase.pPathCchCanonicalizeEx =
      (KernelBase::PFN_PathCchCanonicalizeEx)GetProcAddress(
        module, "PathCchCanonicalizeEx");
    FreeLibrary(module);
  }
}

// -------------------------------------------------------------------------- //

SharedLibraries&
SharedLibraries::Instance()
{
  static SharedLibraries instance;
  return instance;
}
}

#endif
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

#include "alflib/memory/allocator.hpp"

// ========================================================================== //
// Headers
// ========================================================================== //

// Project headers
#include "alflib/math/math.hpp"

// ========================================================================== //
// DefaultAllocator Implementation
// ========================================================================== //

namespace alflib {

void*
DefaultAllocator::Alloc(u64 size, u32 alignment)
{
  if (size == 0) {
    return nullptr;
  }

#if defined(_WIN32)
  return _aligned_malloc(size, alignment);
#elif defined(__linux__) || defined(__APPLE__)
  alignment = Max(DEFAULT_ALIGNMENT, alignment);
  void* memory;
  if (posix_memalign(&memory, alignment, size) != 0) {
    return nullptr;
  }
  return memory;
#endif
}

// -------------------------------------------------------------------------- //

void
DefaultAllocator::Free(void* memory)
{
#if defined(_WIN32)
  _aligned_free(memory);
#elif defined(__linux__) || defined(__APPLE__)
  free(memory);
#endif
}

// -------------------------------------------------------------------------- //

DefaultAllocator&
DefaultAllocator::Instance()
{
  static DefaultAllocator allocator;
  return allocator;
}

}

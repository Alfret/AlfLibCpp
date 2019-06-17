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

#include "alflib/assert.hpp"
#include "alflib/common.hpp"

// ========================================================================== //
// Functions
// ========================================================================== //

namespace alflib {

/** Returns the minimum of two values.
 * \brief Returns min of two values.
 * \tparam T Type of values.
 * \param a First value.
 * \param b Second value.
 * \return Minimum value.
 */
template<typename T>
constexpr T
Min(T a, T b)
{
  return a < b ? a : b;
}

// -------------------------------------------------------------------------- //

/** Returns the maximum of two values.
 * \brief Returns max of two values.
 * \tparam T Type of values.
 * \param a First value.
 * \param b Second value.
 * \return Maximum value.
 */
template<typename T>
constexpr T
Max(T a, T b)
{
  return a > b ? a : b;
}

// -------------------------------------------------------------------------- //

/** Returns whether or not a value is a power of two.
 * \brief Returns whether value is power of two.
 * \param value Value to check if power of two.
 * \return True if the value is a power of two, otherwise false.
 */
constexpr bool
IsPowerOfTwo(u64 value)
{
  return value && !(value & value - 1);
}

// -------------------------------------------------------------------------- //

/** Align a value 'base' to a power of two 'alignment'.
 * \brief Align value.
 * \param base Base value to align to the specified alignment.
 * \param alignment Value to align to.
 * \return Aligned value.
 */
inline u64
AlignPowerOfTwo(u64 base, u32 alignment)
{
#if defined(_WIN32)
#pragma warning(push)
#pragma warning(disable : 4146)
  AlfAssert(alignment > 0 && IsPowerOfTwo(alignment),
            "Alignment must be a power of two");
  return (base + alignment - 1) & -alignment;
#pragma warning(pop)
#else
  AlfAssert(alignment > 0 && IsPowerOfTwo(alignment),
            "Alignment must be a power of two");
  return (base + alignment - 1) & -alignment;
#endif
}

}
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
#include "alflib/core/common.hpp"

// ========================================================================== //
// Platform Detection
// ========================================================================== //

#if defined(_WIN32)
/** Microsoft Windows target platform **/
#define ALFLIB_TARGET_WINDOWS
#elif defined(__linux__) && !defined(__ANDROID__)
/** Linux target platform **/
#define ALFLIB_TARGET_LINUX
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
/** Apple iOS simulator target platform **/
#define ALFLIB_TARGET_IOS_SIMULATOR
#elif TARGET_OS_IPHONE
/** Apple iOS target platform **/
#define ALFLIB_TARGET_IOS
#elif TARGET_OS_MAC
/** Apple MacOS target platform **/
#define ALFLIB_TARGET_MACOS
#else
#error "Unknown Apple OS"
#endif
#elif defined(__ANDROID__)
#define ALFLIB_TARGET_ANDROID
#endif

// ========================================================================== //
// Endianness
// ========================================================================== //

/** Macro for little endian **/
#define ALFLIB_LITTLE_ENDIAN 0x03020100ul
/** Macro for big endian **/
#define ALFLIB_BIG_ENDIAN 0x00010203ul
/** Macro for PDP endian **/
#define ALFLIB_PDP_ENDIAN 0x01000302ul

namespace alflib {

/** Union used to determine host endianness **/
static const union
{
  u8 bytes[4];
  u32 value;
} sHostOrder = { { 0, 1, 2, 3 } };

}

/** Macro for the endianness of the host **/
#define ALFLIB_HOST_ENDIAN (alflib::sHostOrder.value)

// ========================================================================== //
// Windows Headers
// ========================================================================== //

#if defined(ALFLIB_TARGET_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <pathcch.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <windows.h>

#endif // defined(ALFLIB_TARGET_WINDOWS)

// ========================================================================== //
// Linux Headers
// ========================================================================== //

#if defined(ALFLIB_TARGET_LINUX)

#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#endif

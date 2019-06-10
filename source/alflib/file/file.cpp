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

#include "alflib/file/file.hpp"

// ========================================================================== //
// File Implementation
// ========================================================================== //

namespace alflib {

File::File(const Path& path)
  : mPath(path)
{
  UpdateAttributes();
}

// -------------------------------------------------------------------------- //

File::File(const String& path)
  : File(Path(path))
{}

// -------------------------------------------------------------------------- //

File
File::Open(const Path& path)
{
  return File{ "" };
}

// -------------------------------------------------------------------------- //

File
File::Open(const String& path)
{
  return File{ "" };
}

// -------------------------------------------------------------------------- //

bool
File::Exists() const
{
#if defined(ALFLIB_TARGET_WINDOWS)
  return mFileAttributes.dwFileAttributes != INVALID_FILE_ATTRIBUTES;
#else
  return false;
#endif
}

// -------------------------------------------------------------------------- //

ArrayList<File>
File::Enumerate() const
{
  ArrayList<File> files;

#if defined(ALFLIB_TARGET_WINDOWS)
  const auto path = (mPath.GetPath() + "/*").GetUTF16();
  WIN32_FIND_DATAW findData;
  const HANDLE findHandle = FindFirstFileExW(
    path.Get(), FindExInfoBasic, &findData, FindExSearchNameMatch, nullptr, 0);
  if (findHandle != INVALID_HANDLE_VALUE) {
    do {
      files.AppendEmplace(findData.cFileName);
    } while (FindNextFileW(findHandle, &findData));
  }
  FindClose(findHandle);
#else

#endif

  return files;
}

// -------------------------------------------------------------------------- //

File::Type
File::GetType() const
{
  if (!Exists()) {
    return Type::kInvalid;
  }

#if defined(ALFLIB_TARGET_WINDOWS)
  if (mFileAttributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
    return Type::kDirectory;
  }
  return Type::kFile;
#else
  return Type::kInvalid;
#endif
}

// -------------------------------------------------------------------------- //

u64
File::GetSize() const
{
  if (!Exists()) {
    return 0;
  }

#if defined(ALFLIB_TARGET_WINDOWS)
  const u64 sizeHigh = (uint64_t)mFileAttributes.nFileSizeHigh << sizeof(DWORD);
  const u64 sizeLow = mFileAttributes.nFileSizeLow;
  return sizeLow | sizeHigh;
#else
  struct stat fileStats;
  s32 result = stat(mPath.GetPath().GetUTF8(), &fileStats);
  if (result != 0) {
    return 0;
  }
  return static_cast<u64>(fileStats.st_size);
#endif
}

// -------------------------------------------------------------------------- //

void
File::UpdateAttributes()
{
  const UniquePointer<char16[]> path = mPath.GetPath().GetUTF16();
  GetFileAttributesExW(path.Get(), GetFileExInfoStandard, &mFileAttributes);
}

// -------------------------------------------------------------------------- //

bool
operator==(const File& file0, const File& file1)
{
  return file0.mPath == file1.mPath;
}

// -------------------------------------------------------------------------- //

bool
operator!=(const File& file0, const File& file1)
{
  return file0.mPath != file1.mPath;
}

}

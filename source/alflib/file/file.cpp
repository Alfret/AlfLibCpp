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

FileIO
File::OpenFile(Flag flags)
{
  return FileIO{  };
}

// -------------------------------------------------------------------------- //

ArrayList<File>
File::Enumerate()
{
  return ArrayList<File>{};
}

// -------------------------------------------------------------------------- //

File::Type
File::GetType() const
{
  return Type::kFile;
}

// -------------------------------------------------------------------------- //

void
File::UpdateAttributes()
{
  char16* path = mPath.GetPath().GetUTF16();
  GetFileAttributesExW(path, GetFileExInfoStandard, &mFileAttributes);
  

}

}

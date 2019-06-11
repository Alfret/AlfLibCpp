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

#include "alflib/file/path.hpp"

// ========================================================================== //
// Headers
// ========================================================================== //

// Standard headers
#include <cstdlib>
#include "alflib/platform/os.hpp"

// ========================================================================== //
// Path Implementation
// ========================================================================== //

namespace alflib {

const String Path::CURRENT = ".";

// -------------------------------------------------------------------------- //

const String Path::PARENT = "..";

// -------------------------------------------------------------------------- //

#if defined(ALFLIB_TARGET_WINDOWS)
const String Path::SEPARATOR = "\\";
#else
const String Path::SEPARATOR = "/";
#endif

// -------------------------------------------------------------------------- //

Path::Path(const String& path)
  : mPath(path)
{
  FixSeparators();

  // Remove trailing separator
  if (mPath.EndsWith('\\') || mPath.EndsWith('/')) {
    mPath = mPath.Substring(0, mPath.GetLength() - 1);
  }
}

// -------------------------------------------------------------------------- //

Path&
Path::Join(const Path& other)
{
  if (!other.mPath.StartsWith('\\') && !other.mPath.StartsWith('/')) {
    mPath += SEPARATOR_CHAR;
  }
  mPath += other.mPath;
  return *this;
}

// -------------------------------------------------------------------------- //

Path&
Path::operator+=(const Path& other)
{
  return Join(other);
}

// -------------------------------------------------------------------------- //

Path
Path::Joined(const Path& other) const
{
  Path path = *this;
  path.Join(other);
  return path;
}

// -------------------------------------------------------------------------- //

Path
Path::GetAbsolutePath() const
{
#if defined(ALFLIB_TARGET_WINDOWS)
  // Retrieve absolute path
  char16 buffer[MAX_PATH];
  const DWORD length =
    GetFullPathNameW(mPath.GetUTF16().Get(), MAX_PATH, buffer, nullptr);
  if (length != 0) {
    // Canonicalize path
    char16 _buffer[MAX_PATH];
    // TODO(Filip Björklund): Handle case where function is not available
    const HRESULT result =
      SharedLibraries::GetKernelBase().pPathCchCanonicalizeEx(
        _buffer, MAX_PATH, buffer, PATHCCH_NONE);
    if (SUCCEEDED(result)) {
      return String(_buffer);
    }
  }
  return Path{ "" };
#else
  char buffer[PATH_MAX];
  realpath(mPath.GetUTF8(), buffer);
  return String(buffer);
#endif
}

// -------------------------------------------------------------------------- //

ArrayList<String>
Path::GetComponents()
{
  ArrayList<String> components;

  // Find components
  u32 prevIndex = 0;
  mPath.ForEach([&](u32 codepoint, u32 index) {
    if (codepoint == '/' || codepoint == '\\') {
      components.Append(mPath.Substring(prevIndex, index - prevIndex));
      prevIndex = index + 1;
    }
  });
  components.Append(mPath.Substring(prevIndex));
  return components;
}

// -------------------------------------------------------------------------- //

String
Path::GetName() const
{
  const s64 sepIndex = Max(mPath.LastIndexOf('/'), mPath.LastIndexOf('\\'));
  const s64 dotIndex = mPath.LastIndexOf('.');
  if (sepIndex == -1) {
    return "";
  }
  if (dotIndex == -1) {
    return mPath.Substring(sepIndex);
  }
  return mPath.Substring(sepIndex, dotIndex - sepIndex);
}

// -------------------------------------------------------------------------- //

Path::Extension
Path::GetExtension() const
{
  const String extensionString = GetExtensionString();
  if (extensionString.GetLength() == 0) {
    return Extension::kNone;
  }
  if (extensionString == ".txt") {
    return Extension::kTxt;
  }
  if (extensionString == ".png") {
    return Extension::kPng;
  }
  if (extensionString == ".tar") {
    return Extension::kTar;
  }
  if (extensionString == ".zip") {
    return Extension::kZip;
  }
  return Extension::kUnknown;
}

// -------------------------------------------------------------------------- //

String
Path::GetExtensionString() const
{
  const s64 index = mPath.LastIndexOf('.');
  if (index == -1) {
    return "";
  }
  return mPath.Substring(index);
}

// -------------------------------------------------------------------------- //

bool
operator==(const Path& path0, const Path& path1)
{
  return path0.mPath == path1.mPath;
}

// -------------------------------------------------------------------------- //

bool
operator!=(const Path& path0, const Path& path1)
{
  return path0.mPath != path1.mPath;
}

// -------------------------------------------------------------------------- //

Path
operator+(const Path& path0, const Path& path1)
{
  return path0.Joined(path1);
}

// -------------------------------------------------------------------------- //

Path
operator+(const Path& path0, const String& path1)
{
  return path0.Joined(Path{ path1 });
}

// -------------------------------------------------------------------------- //

void
Path::FixSeparators()
{
#if defined(ALFLIB_TARGET_WINDOWS)
  mPath.Replace("/", "\\");
#else
  mPath.Replace("\\", "/");
#endif
}

// -------------------------------------------------------------------------- //

Path
Path::GetKnownDirectory(KnownDirectory directory)
{
#if defined(ALFLIB_TARGET_WINDOWS)
  if (directory == KnownDirectory::kHome) {
    char16* buffer;
    HRESULT hresult =
      SHGetKnownFolderPath(FOLDERID_Profile, KF_FLAG_DEFAULT, nullptr, &buffer);
    String output(buffer);
    CoTaskMemFree(buffer);
    return output;
  }
  if (directory == KnownDirectory::kDesktop) {
    char16* buffer;
    HRESULT hresult =
      SHGetKnownFolderPath(FOLDERID_Desktop, KF_FLAG_DEFAULT, nullptr, &buffer);
    String output(buffer);
    CoTaskMemFree(buffer);
    return output;
  }
  if (directory == KnownDirectory::kDocuments) {
    char16* buffer;
    HRESULT hresult = SHGetKnownFolderPath(
      FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, &buffer);
    String output(buffer);
    CoTaskMemFree(buffer);
    return output;
  }
  if (directory == KnownDirectory::kDownloads) {
    char16* buffer;
    HRESULT hresult = SHGetKnownFolderPath(
      FOLDERID_Downloads, KF_FLAG_DEFAULT, nullptr, &buffer);
    String output(buffer);
    CoTaskMemFree(buffer);
    return output;
  }
#else
  if (directory == KnownDirectory::kHome) {
    struct passwd* pw = getpwuid(getuid());
    return String{ pw->pw_dir };
  }
  if (directory == KnownDirectory::kDesktop) {
    char* path = std::getenv("XDG_DESKTOP_DIR");
  }
  if (directory == KnownDirectory::kDocuments) {
    char* path = std::getenv("XDG_DOCUMENTS_DIR");

  }
  if (directory == KnownDirectory::kDownloads) {
    char* path = std::getenv("XDG_DOWNLOAD_DIR");

  }
#endif
  return Path{ "" };
}


}

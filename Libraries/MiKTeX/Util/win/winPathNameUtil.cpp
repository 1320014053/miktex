/**
 * @file winPathNameUtil.cpp
 * @author Christian Schenk
 * @brief PathNameUtil class (Windows)
 *
 * @copyright Copyright © 2020-2024 Christian Schenk
 *
 * This file is part of the MiKTeX Util Library.
 *
 * The MiKTeX Util Library is licensed under GNU General Public License version
 * 2 or any later version.
 */

#include <Windows.h>

#define A7C88F5FBE5C45EB970B3796F331CD89
#include "miktex/Util/config.h"

#if defined(MIKTEX_UTIL_SHARED)
#define MIKTEXUTILEXPORT MIKTEXDLLEXPORT
#else
#define MIKTEXUTILEXPORT
#endif

#include "miktex/Util/CharBuffer.h"
#include "miktex/Util/PathNameUtil.h"
#include "miktex/Util/StringUtil.h"

#include "internal.h"

using namespace std;

using namespace MiKTeX::Util;

// inspired CMake's SystemTools::ConvertToWindowsExtendedPath (Source/kwsys/SystemTools.cxx)
wstring PathNameUtil::ToLengthExtendedPathName(const string& path)
{
    if (path.empty())
    {
        return L"\\\\?\\"s;
    }
    wstring wpath = StringUtil::UTF8ToWideChar(path);
    DWORD len = GetFullPathNameW(wpath.c_str(), 0, nullptr, nullptr);
    if (len == 0)
    {
        throw Exception("GetFullPathNameW failed");
    }
    CharBuffer<wchar_t> absPath;
    absPath.Reserve(len);
    len = GetFullPathNameW(wpath.c_str(), len, &absPath[0], nullptr);
    if (len == 0 || len >= absPath.GetCapacity())
    {
        throw Exception("GetFullPathNameW failed");
    }
    if (IsDosDriveLetter(absPath[0])
        && IsDosVolumeDelimiter(absPath[1])
        && IsDirectoryDelimiter(absPath[2]))
    {
        // C:\Foo\bar\FooBar.txt
        return L"\\\\?\\"s + absPath.ToString();
    }
    else if (PathNameUtil::IsDirectoryDelimiter(absPath[0]) && PathNameUtil::IsDirectoryDelimiter(absPath[1]))
    {
        if (absPath[2] == L'?' && PathNameUtil::IsDirectoryDelimiter(absPath[3]))
        {
            if (absPath[4] == L'U' && absPath[5] == L'N' && absPath[6] == L'C' && PathNameUtil::IsDirectoryDelimiter(absPath[7]))
            {
                // \\?\UNC\Foo\bar\FooBar.txt
                return absPath.ToString();
            }
            else if (PathNameUtil::IsDosDriveLetter(absPath[4]) && PathNameUtil::IsDirectoryDelimiter(absPath[5]))
            {
                // \\?\C:\Foo\bar\FooBar.txt
                return absPath.ToString();
            }
            else if (absPath.GetLength() > 4)
            {
                // \\?\Foo\bar\FooBar.txt
                return absPath.ToString();
            }
        }
        else if (absPath[2] == '.' && PathNameUtil::IsDirectoryDelimiter(absPath[3]))
        {
            if (PathNameUtil::IsDosDriveLetter(absPath[4]) && PathNameUtil::IsDosVolumeDelimiter(absPath[5]))
            {
                // \\.\C:\Foo\bar\FooBar.txt
                return L"\\\\?\\"s + wstring(&absPath[4]);
            }
            else if (absPath.GetLength() > 4)
            {
                // \\.\Foo\bar\ (device name is left unchanged)
                return absPath.ToString();
            }
        }
        else if (absPath.GetLength() > 2)
        {
            // \\Foo\bar\FooBar.txt
            return L"\\\\?\\UNC\\"s + wstring(&absPath[2]);
        }
    }
    return wpath;
}

/* miktex/Extractor/Extractor.h:                        -*- C++ -*-

   Copyright (C) 2001-2019 Christian Schenk

   This file is part of MiKTeX Extractor.

   MiKTeX Extractor is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   MiKTeX Extractor is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with MiKTeX Extractor; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */

#pragma once

#if !defined(CE2192A940434CEB82EFF92FA64AC9D4)
#define CE2192A940434CEB82EFF92FA64AC9D4

#include <miktex/First>
#include <miktex/Definitions>

#include "config.h"

#include <cstddef>

#include <memory>
#include <string>

#include <miktex/Util/PathName>
#include <miktex/Core/Paths>
#include <miktex/Core/Session>
#include <miktex/Core/Stream>

/// @namespace MiKTeX::Extractor
/// @brief Extracting files from compressed archives.
MIKTEX_EXTRACTOR_BEGIN_NAMESPACE;

enum class ArchiveFileType
{
  None, MSCab, TarBzip2, Zip, Tar, TarLzma, TarXz
};

class MIKTEXNOVTABLE IExtractCallback
{
public:
  virtual void MIKTEXTHISCALL OnBeginFileExtraction(const std::string& fileName, std::size_t uncompressedSize) = 0;

public:
  virtual void MIKTEXTHISCALL OnEndFileExtraction(const std::string& fileName, std::size_t uncompressedSize) = 0;

public:
  virtual bool MIKTEXTHISCALL OnError(const std::string& message) = 0;
};

class MIKTEXNOVTABLE Extractor
{
public:
  virtual MIKTEXTHISCALL ~Extractor() noexcept = 0;

public:
  virtual void MIKTEXTHISCALL Extract(const MiKTeX::Util::PathName& path, const MiKTeX::Util::PathName& destDir, bool makeDirectories, IExtractCallback* callback, const std::string& prefix) = 0;

public:
  void MIKTEXTHISCALL Extract(const MiKTeX::Util::PathName& path, const MiKTeX::Util::PathName& destDir, bool makeDirectories)
  {
    return Extract(path, destDir, makeDirectories, nullptr, "");
  }

public:
  void MIKTEXTHISCALL Extract(const MiKTeX::Util::PathName& path, const MiKTeX::Util::PathName& destDir)
  {
    return Extract(path, destDir, false, nullptr, "");
  }

public:
  virtual void MIKTEXTHISCALL Extract(MiKTeX::Core::Stream* stream, const MiKTeX::Util::PathName& destDir, bool makeDirectories, IExtractCallback* callback, const std::string& prefix) = 0;

public:
  void MIKTEXTHISCALL Extract(MiKTeX::Core::Stream* stream, const MiKTeX::Util::PathName& destDir, bool makeDirectories)
  {
    return Extract(stream, destDir, makeDirectories, nullptr, "");
  }

public:
  void MIKTEXTHISCALL Extract(MiKTeX::Core::Stream* stream, const MiKTeX::Util::PathName& destDir)
  {
    return Extract(stream, destDir, false, nullptr, "");
  }

public:
  static MIKTEXEXTRACTORCEEAPI(std::unique_ptr<Extractor>) CreateExtractor(ArchiveFileType archiveFileType);

public:
  static const std::string GetFileNameExtension(ArchiveFileType archiveFileType)
  {
    switch (archiveFileType)
    {
    case ArchiveFileType::MSCab:
      return MIKTEX_CABINET_FILE_SUFFIX;
    case ArchiveFileType::TarBzip2:
      return MIKTEX_TARBZIP2_FILE_SUFFIX;
    case ArchiveFileType::TarLzma:
      return MIKTEX_TARLZMA_FILE_SUFFIX;
    case ArchiveFileType::TarXz:
      return MIKTEX_TARXZ_FILE_SUFFIX;
    case ArchiveFileType::Zip:
      return MIKTEX_ZIP_FILE_SUFFIX;
    case ArchiveFileType::Tar:
      return MIKTEX_TAR_FILE_SUFFIX;
    default:
      MIKTEX_UNEXPECTED();
    }
  }
};

MIKTEX_EXTRACTOR_END_NAMESPACE;

#endif

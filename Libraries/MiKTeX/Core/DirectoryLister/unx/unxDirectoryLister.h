/* unxDirectoryLister.h:                                -*- C++ -*-

   Copyright (C) 1996-2018 Christian Schenk

   This file is part of the MiKTeX Core Library.

   The MiKTeX Core Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The MiKTeX Core Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the MiKTeX Core Library; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#pragma once

#if !defined(F2A2B73E1341485FAFAB1FC525782032)
#define F2A2B73E1341485FAFAB1FC525782032

#include <miktex/Core/DirectoryLister>
#include <miktex/Util/PathName>

CORE_INTERNAL_BEGIN_NAMESPACE;

class unxDirectoryLister :
  public MiKTeX::Core::DirectoryLister
{
public:
  ~unxDirectoryLister() noexcept override;

public:
  unxDirectoryLister(const MiKTeX::Util::PathName& directory, const char* pattern, int options);

public:
  void Close() override;

public:
  bool GetNext(MiKTeX::Core::DirectoryEntry& direntry) override;

public:
  bool GetNext(MiKTeX::Core::DirectoryEntry2& direntry2) override;

private:
  bool GetNext(MiKTeX::Core::DirectoryEntry2& direntry2, bool simple);

private:
  DIR * dir = nullptr;

private:
  MiKTeX::Util::PathName directory;

private:
  std::string pattern;

private:
  int options = (int)Options::None;

private:
  friend class MiKTeX::Core::DirectoryLister;
};

CORE_INTERNAL_END_NAMESPACE;

#endif

/* RootDirectoryInternals.h:                            -*- C++ -*-

   Copyright (C) 1996-2019 Christian Schenk

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

#if !defined(FFCF19389D64414EBC1FB50A73140032)
#define FFCF19389D64414EBC1FB50A73140032

#include <miktex/Core/RootDirectoryInfo>

#include "Fndb/FileNameDatabase.h"

CORE_INTERNAL_BEGIN_NAMESPACE;

struct RootDirectoryInternals :
  MiKTeX::Core::RootDirectoryInfo
{
public:
  RootDirectoryInternals()
  {
  }

public:
  RootDirectoryInternals(const MiKTeX::Util::PathName& unexpandedPath, const MiKTeX::Util::PathName& path) :
    unexpandedPath(unexpandedPath)
  {
    this->path = path;
  }

public:
  const MiKTeX::Util::PathName& get_UnexpandedPath() const
  {
    return unexpandedPath;
  }

public:
  const MiKTeX::Util::PathName& get_Path() const
  {
    return path;
  }

public:
  void set_NoFndb(bool f)
  {
    this->noFndb = f;
  }

public:
  bool get_NoFndb() const
  {
    return noFndb;
  }

public:
  void set_Common(bool f)
  {
    if (f)
    {
      this->attributes += Attribute::Common;
    }
    else
    {
      this->attributes -= Attribute::Common;
    }
  }

public:
  void set_Other(bool f)
  {
    if (f)
    {
      this->attributes += Attribute::Other;
    }
    else
    {
      this->attributes -= Attribute::Other;
    }
  }

public:
  void set_User(bool f)
  {
    if (f)
    {
      this->attributes += Attribute::User;
    }
    else
    {
      this->attributes -= Attribute::User;
    }
  }

public:
  void SetFndb(std::shared_ptr<FileNameDatabase> fndb)
  {
    this->fndb = fndb;
  }

public:
  std::shared_ptr<FileNameDatabase> GetFndb() const
  {
    return fndb;
  }

private:
  MiKTeX::Util::PathName unexpandedPath;

  // associated file name database object
private:
  std::shared_ptr<FileNameDatabase> fndb;

  // true, if a file name database doesn't exist
private:
  bool noFndb = false;
};

CORE_INTERNAL_END_NAMESPACE;

#endif

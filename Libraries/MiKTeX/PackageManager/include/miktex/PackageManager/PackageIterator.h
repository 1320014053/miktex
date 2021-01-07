/* miktex/PackageManager/PackageIterator.h:             -*- C++ -*-

   Copyright (C) 2001-2019 Christian Schenk

   This file is part of MiKTeX Package Manager.

   MiKTeX Package Manager is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   MiKTeX Package Manager is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with MiKTeX Package Manager; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#pragma once

#if !defined(E2B06574362B414885CF42E8C46BDB28)
#define E2B06574362B414885CF42E8C46BDB28

#include "config.h"

#include <miktex/Util/OptionSet>

#include "PackageInfo.h"

MIKTEX_PACKAGES_BEGIN_NAMESPACE;

/// Package filter.
enum class PackageFilter
{
  /// Top-level package filter.
  Top,
  /// Obsolete packages.
  Obsolete,
};

typedef MiKTeX::Util::OptionSet<PackageFilter> PackageFilterSet;

/// Instances of this class can be used to browse the package database.
class MIKTEXNOVTABLE PackageIterator
{
public:
  virtual MIKTEXTHISCALL ~PackageIterator() noexcept = 0;

  /// Releases all resources used by this object.
public:
  virtual void MIKTEXTHISCALL Dispose() = 0;

  /// Adds a browse filter.
  /// @param filter Filter flags to be added.
  /// @param lpsz Optional filter argument.
public:
  virtual void MIKTEXTHISCALL AddFilter(PackageFilterSet filter) = 0;

  /// Gets the next record in the package database.
  /// @param[out] packageInfo The package record.
  /// @return Returns `false`, if there are no more records in the database.
public:
  virtual bool MIKTEXTHISCALL GetNext(PackageInfo& packageInfo) = 0;
};

MIKTEX_PACKAGES_END_NAMESPACE;

#endif

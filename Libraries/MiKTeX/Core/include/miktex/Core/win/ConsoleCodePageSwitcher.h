/* miktex/Core/win/ConsoleCodePageSwitcher.h:

   Copyright (C) 2021 Christian Schenk

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

#include <miktex/Core/config.h>

MIKTEX_CORE_BEGIN_NAMESPACE;

class ConsoleCodePageSwitcher
{
public:
  MIKTEXCOREEXPORT MIKTEXTHISCALL ConsoleCodePageSwitcher();

public:
  ConsoleCodePageSwitcher(const ConsoleCodePageSwitcher& other) = delete;

public:
  ConsoleCodePageSwitcher& operator=(const ConsoleCodePageSwitcher& other) = delete;

public:
  ConsoleCodePageSwitcher(ConsoleCodePageSwitcher&& other) = delete;

public:
  ConsoleCodePageSwitcher& operator=(ConsoleCodePageSwitcher&& other) = delete;

public:
  MIKTEXCOREEXPORT virtual MIKTEXTHISCALL ~ConsoleCodePageSwitcher() noexcept;

private:
  unsigned int previousOutputCodePageID = 0;
};

MIKTEX_CORE_END_NAMESPACE;

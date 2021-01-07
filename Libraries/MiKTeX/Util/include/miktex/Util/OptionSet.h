/* miktex/Util/OptionSet.h:

   Copyright (C) 1996-2021 Christian Schenk

   This file is part of the MiKTeX Util Library.

   The MiKTeX Util Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The MiKTeX Util Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the MiKTeX Util Library; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#pragma once

#if !defined(DA160798149E44048A2AD243F813ACCD)
#define DA160798149E44048A2AD243F813ACCD

#include <miktex/Util/config.h>

#include <cstddef>

#include <bitset>
#include <initializer_list>

MIKTEX_UTIL_BEGIN_NAMESPACE;

template<typename EnumClass_, int Size_ = 32> class OptionSet
{
public:
  OptionSet() = default;

public:
  OptionSet(const OptionSet& other) = default;

public:
  OptionSet& operator=(const OptionSet& other) = default;

public:
  OptionSet(OptionSet&& other) = default;

public:
  OptionSet& operator=(OptionSet&& other) = default;

public:
  ~OptionSet() = default;

public:
  OptionSet(const std::initializer_list<EnumClass_>& options)
  {
    for (const EnumClass_& opt : options)
    {
      bits[(std::size_t)opt] = true;
    }
  }

public:
  OptionSet& operator+=(EnumClass_ opt)
  {
    bits[(std::size_t)opt] = true;
    return *this;
  }

public:
  OptionSet& operator+=(const OptionSet<EnumClass_>& other)
  {
    this->bits |= other.bits;
    return *this;
  }

public:
  OptionSet operator+(const EnumClass_& other) const
  {
    OptionSet<EnumClass_> result(*this);
    return result += other;
  }

public:
  OptionSet& operator-=(EnumClass_ opt)
  {
    bits[(std::size_t)opt] = false;
    return *this;
  }

public:
  OptionSet operator-(const EnumClass_& other) const
  {
    OptionSet<EnumClass_> result(*this);
    return result -= other;
  }

public:
  bool operator[](EnumClass_ opt) const
  {
    return bits[(std::size_t)opt];
  }

public:
  bool operator==(const OptionSet<EnumClass_>& other) const
  {
    return bits == other.bits;
  }

public:
  bool operator!=(const OptionSet<EnumClass_>& other) const
  {
    return bits != other.bits;
  }

public:
  void Set()
  {
    bits.set();
  }

public:
  void Reset()
  {
    bits.reset();
  }

private:
  std::bitset<Size_> bits;
};

MIKTEX_UTIL_END_NAMESPACE;

#endif

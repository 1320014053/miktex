/* miktex/Core/MD5.h:                                   -*- C++ -*-

   Copyright (C) 1996-2021 Christian Schenk

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

#if !defined(F16928B95BB64B778B3E396992FFFCDD)
#define F16928B95BB64B778B3E396992FFFCDD

#include <miktex/Core/config.h>

#include <algorithm>
#include <array>
#include <ostream>
#include <string>
#include <vector>

#include <miktex/Util/PathName>

#include "Utils.h"

#include <md5.h>

MIKTEX_CORE_BEGIN_NAMESPACE;

/// Instances of this struct represent MD5 values.
class MD5 :
  public std::array<md5_byte_t, 16>
{
  /// Calculates the MD5 value of a file.
  /// @param lpszPath The path name of the file.
  /// @return Returns the MD5 of the file.
public:
  static MIKTEXCORECEEAPI(MD5) FromFile(const MiKTeX::Util::PathName& path);

  /// Calculates the MD5 value of a char sequence.
  /// @param s The char sequence.
  /// @return Returns the MD5 of the char sequence.
public:
  static MIKTEXCORECEEAPI(MD5) FromChars(const std::string& s);

  /// Parses the string represention of an MD5.
  /// @param lpszHexString The string representation (32 hex characters).
  /// @return Returns the MD5.
public:
  static MIKTEXCORECEEAPI(MD5) Parse(const std::string& hexString);

  /// Converts this MD5 into a string object.
  /// @return Returns a string object.
public:
  std::string ToString() const
  {
    return Utils::Hexify(&this->front(), this->size());
  }
};

/// Instances of this struct can be used to calculate MD5 values.
class MD5Builder
{
  /// Initializes a new MD5Builder object.
public:
  MD5Builder()
  {
    Init();
  }

public:
  MD5Builder(const MD5Builder& other) = default;

public:
  MD5Builder& operator=(const MD5Builder& other) = default;

public:
  MD5Builder(MD5Builder&& other) = default;

public:
  MD5Builder& operator=(MD5Builder&& other) = default;

public:
  ~MD5Builder() = default;

  /// Resets the state of this MD5Builder object.
public:
  void Init()
  {
    md5_init(&ctx);
  }

  /// Updates the state of this MD5Builder object.
  /// @param ptr Bytes to be contributed to the MD5 value.
  /// @param size Size of the byte buffer.
public:
  void Update(const void* ptr, size_t size)
  {
    md5_append(&ctx, reinterpret_cast<const md5_byte_t*>(ptr), static_cast<int>(size));
  }

  /// Calculates the final MD5 value.
  /// @return Returns the MD5 object.
public:
  MD5 Final()
  {
    md5_finish(&ctx, &md5[0]);
    return md5;
  }

  /// Gets the calculated MD5 value.
  /// @return Returns the MD5 object.
public:
  MD5 GetMD5() const
  {
    return md5;
  }

private:
  md5_state_t ctx;

private:
  MD5 md5;
};

inline std::ostream& operator<<(std::ostream& os, const MD5& md5)
{
  return os << md5.ToString();
}


MIKTEX_CORE_END_NAMESPACE;

#endif

/**
 * @file miktex/TeXAndFriends/CharacterConverterImpl.h
 * @author Christian Schenk
 * @brief Character converter implementation
 *
 * @copyright Copyright © 2017-2022 Christian Schenk
 *
 * This file is part of the MiKTeX TeXMF Framework.
 *
 * The MiKTeX TeXMF Framework is licensed under GNU General Public License
 * version 2 or any later version.
 */

#pragma once

#include <miktex/TeXAndFriends/config.h>

#include "WebApp.h"

MIKTEX_TEXMF_BEGIN_NAMESPACE;

template<class PROGRAM_CLASS> class CharacterConverterImpl :
    public ICharacterConverter
{

public:

    CharacterConverterImpl(PROGRAM_CLASS& program) :
        program(program)
    {
    }

    char* xchr() override
    {
#if defined(MIKTEX_XETEX)
        MIKTEX_UNEXPECTED();
#else
        MIKTEX_ASSERT(sizeof(program.xchr[0]) == sizeof(char));
        return reinterpret_cast<char*>(&program.xchr[0]);
#endif
    }

    char* xord() override
    {
#if defined(MIKTEX_XETEX)
        MIKTEX_UNEXPECTED();
#else
        MIKTEX_ASSERT(sizeof(program.xord[0]) == sizeof(char));
        return reinterpret_cast<char*>(&program.xord[0]);
#endif
    }

    char* xprn() override
    {
#if (defined(MIKTEX_META_COMPILER) || defined(MIKTEX_TEX_COMPILER)) && !defined(MIKTEX_XETEX)
        MIKTEX_ASSERT(sizeof(program.xprn[0]) == sizeof(char));
        return reinterpret_cast<char*>(&program.xprn[0]);
#else
        MIKTEX_UNEXPECTED();
#endif
    }

private:

    PROGRAM_CLASS& program;

};

MIKTEX_TEXMF_END_NAMESPACE;

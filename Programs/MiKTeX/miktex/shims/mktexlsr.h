/**
 * @file shims/mktexlsr.cpp
 * @author Christian Schenk
 * @brief mktexlsr shim
 *
 * @copyright Copyright © 2022 Christian Schenk
 *
 * This file is part of One MiKTeX Utility.
 *
 * One MiKTeX Utility is licensed under GNU General Public
 * License version 2 or any later version.
 */

#include <string>
#include <vector>

#include "internal.h"

namespace OneMiKTeXUtility::Shims
{
    void mktexlsr(OneMiKTeXUtility::ApplicationContext* ctx, std::vector<std::string>& arguments);
}

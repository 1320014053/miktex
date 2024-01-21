/**
 * @file topics/packages/commands/checkupgrade.cpp
 * @author Christian Schenk
 * @brief packages check-upgrade
 *
 * @copyright Copyright © 2022-2024 Christian Schenk
 *
 * This file is part of One MiKTeX Utility.
 *
 * One MiKTeX Utility is licensed under GNU General Public
 * License version 2 or any later version.
 */

#include <config.h>

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <miktex/Core/Session>
#include <miktex/PackageManager/PackageManager>
#include <miktex/Setup/SetupService>
#include <miktex/Util/PathName>
#include <miktex/Wrappers/PoptWrapper>

#include "internal.h"

#include "commands.h"

#include "private.h"

namespace
{
    class UpgradeInfoComparer
    {
    public:
        bool operator() (const  MiKTeX::Packages::PackageInstaller::UpgradeInfo& upg1, const  MiKTeX::Packages::PackageInstaller::UpgradeInfo& upg2) const
        {
            return MiKTeX::Util::PathName::Compare(MiKTeX::Util::PathName(upg1.packageId), MiKTeX::Util::PathName(upg2.packageId)) < 0;
        }
    };

    class CheckUpgradeCommand :
        public OneMiKTeXUtility::Topics::Command
    {
        std::string Description() override
        {
            return T_("Check for MiKTeX upgrades");
        }

        int MIKTEXTHISCALL Execute(OneMiKTeXUtility::ApplicationContext& ctx, const std::vector<std::string>& arguments) override;

        std::string Name() override
        {
            return "check-upgrade";
        }

        std::string Synopsis() override
        {
            return "check-upgrade [--repository <repository>] <package-level>";
        }

        bool CheckUpgrade(OneMiKTeXUtility::ApplicationContext& ctx, MiKTeX::Packages::PackageLevel packageLevel, const std::string& repository);
    };
}

using namespace std;

using namespace MiKTeX::Core;
using namespace MiKTeX::Packages;
using namespace MiKTeX::Setup;
using namespace MiKTeX::Util;
using namespace MiKTeX::Wrappers;

using namespace OneMiKTeXUtility;
using namespace OneMiKTeXUtility::Topics;
using namespace OneMiKTeXUtility::Topics::Packages;

unique_ptr<Command> Commands::CheckUpgrade()
{
    return make_unique<CheckUpgradeCommand>();
}

enum Option
{
    OPT_AAA = 1,
    OPT_REPOSITORY,
};

static const struct poptOption options[] =
{
    {
        "repository", 0,
        POPT_ARG_STRING, nullptr,
        OPT_REPOSITORY,
        T_("Use the specified location as the package repository.  The location can be either a fully qualified path name (a local package repository) or an URL (a remote package repository)."),
        T_("LOCATION")
    },
    POPT_AUTOHELP
    POPT_TABLEEND
};

int CheckUpgradeCommand::Execute(ApplicationContext& ctx, const vector<string>& arguments)
{
    auto argv = MakeArgv(arguments);
    PoptWrapper popt(static_cast<int>(argv.size() - 1), &argv[0], options);
    int option;
    string repository;
    while ((option = popt.GetNextOpt()) >= 0)
    {
        switch (option)
        {
        case OPT_REPOSITORY:
            repository = popt.GetOptArg();
        }
    }
    if (option != -1)
    {
        ctx.ui->IncorrectUsage(fmt::format("{0}: {1}", popt.BadOption(POPT_BADOPTION_NOALIAS), popt.Strerror(option)));
    }
    auto leftOvers = popt.GetLeftovers();
    if (leftOvers.size() != 1)
    {
        ctx.ui->IncorrectUsage(T_("expected one <package-level> argument"));
    }
    auto packageLevel = ToPackageLevel(leftOvers[0]);
    if (packageLevel == PackageLevel::None)
    {
        ctx.ui->FatalError(fmt::format(T_("{0}: unknown package level"), leftOvers[0]));
    }
    return CheckUpgrade(ctx, packageLevel, repository) ? 100 : 0;
}

bool CheckUpgradeCommand::CheckUpgrade(ApplicationContext& ctx, PackageLevel packageLevel, const string& repository)
{
    MyPackageInstallerCallback cb;
    auto packageInstaller = ctx.packageManager->CreateInstaller({ &cb, true, true });
    if (!repository.empty())
    {
        packageInstaller->SetRepository(repository);
    }
    cb.ctx = &ctx;
    cb.packageInstaller = packageInstaller.get();
    packageInstaller->FindUpgrades(packageLevel);
    vector<PackageInstaller::UpgradeInfo> upgrades = packageInstaller->GetUpgrades();
    if (upgrades.empty())
    {
        ctx.ui->Verbose(0, T_("There are currently no upgrades available."));
        return false;
    }
    sort(upgrades.begin(), upgrades.end(), UpgradeInfoComparer());
    for (const PackageInstaller::UpgradeInfo& upg : upgrades)
    {
        ctx.ui->Output(upg.packageId);
    }
    return true;
}

/**
 * @file topics/fontmaps/commands/show-option.cpp
 * @author Christian Schenk
 * @brief fontmaps show-option
 *
 * @copyright Copyright © 2021-2022 Christian Schenk
 *
 * This file is part of One MiKTeX Utility.
 *
 * One MiKTeX Utility is licensed under GNU General Public
 * License version 2 or any later version.
 */

#include <config.h>

#include <memory>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <miktex/Wrappers/PoptWrapper>

#include "internal.h"

#include "commands.h"

#include "FontMapManager.h"

namespace
{
    class ShowOptionCommand :
        public OneMiKTeXUtility::Topics::Command
    {
        std::string Description() override
        {
            return T_("Show a configuration option");
        }

        int MIKTEXTHISCALL Execute(OneMiKTeXUtility::ApplicationContext& ctx, const std::vector<std::string>& arguments) override;

        std::string Name() override
        {
            return "show-option";
        }

        std::string Synopsis() override
        {
            return "show-option --name=NAME [--template=TEMPLATE]";
        }

        const std::string defaultTemplate = "{value}";
    };
}

using namespace std;

using namespace MiKTeX::Wrappers;

using namespace OneMiKTeXUtility;
using namespace OneMiKTeXUtility::Topics;
using namespace OneMiKTeXUtility::Topics::FontMaps;

unique_ptr<Command> Commands::ShowOption()
{
    return make_unique<ShowOptionCommand>();
}

enum Option
{
    OPT_AAA = 1,
    OPT_NAME,
    OPT_TEMPLATE,
};

static const struct poptOption options[] =
{
    {
        "name", 0,
        POPT_ARG_STRING, nullptr,
        OPT_NAME,
        T_("Specify the option name."),
        "NAME"
    },
    {
        "template", 0,
        POPT_ARG_STRING, nullptr,
        OPT_TEMPLATE,
        T_("Specify the output template."),
        "TEMPLATE"
    },
    POPT_AUTOHELP
    POPT_TABLEEND
};

int ShowOptionCommand::Execute(ApplicationContext& ctx, const vector<string>& arguments)
{
    auto argv = MakeArgv(arguments);
    PoptWrapper popt(static_cast<int>(argv.size() - 1), &argv[0], options);
    int option;
    string outputTemplate = this->defaultTemplate;
    string name;
    while ((option = popt.GetNextOpt()) >= 0)
    {
        switch (option)
        {
        case OPT_NAME:
            name = popt.GetOptArg();
            break;
        case OPT_TEMPLATE:
            outputTemplate = popt.GetOptArg();
            break;
        }
    }
    if (option != -1)
    {
        ctx.ui->IncorrectUsage(fmt::format("{0}: {1}", popt.BadOption(POPT_BADOPTION_NOALIAS), popt.Strerror(option)));
    }
    if (!popt.GetLeftovers().empty())
    {
        ctx.ui->IncorrectUsage(T_("unexpected command arguments"));
    }
    if (name.empty())
    {
        ctx.ui->IncorrectUsage(T_("expected --name=NAME"));
    }
    FontMapManager mgr;
    mgr.Init(ctx);
    ctx.ui->Output(fmt::format(outputTemplate,
        fmt::arg("name", name),
        fmt::arg("value", mgr.Option(name))));
    return 0;
}

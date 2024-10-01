#include <iostream>
#include <optional>

#include "args.h"
#include "ansi.h"
#include "helpers.h"
#include "quotes.h"
#include "commands.h"

// ----
// MAIN
// ----

int main(int argc, char *argv[])
{
    Config *cfg = new Config();
    int parse_result = cfg->parse_arguments(argc, argv);
    if (parse_result != 0)
    {
        return parse_result;
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::optional<std::string> subcommand = cfg->get_positional_argument(0).value_or("random");

    try
    {
        if (subcommand == "random")
        {
            show_random_quote(*cfg);
        }
        else if (subcommand == "help")
        {
            print_help();
        }
        else if (subcommand == "version")
        {
            print_version();
        }
        else
        {
            print_help();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1; // Exit with status code 1 indicating failure
    }

    return 0; // Exit with status code 0 indicating success
}

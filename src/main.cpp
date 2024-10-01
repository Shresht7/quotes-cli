#include <iostream>
#include <optional>

#include "config.h"
#include "ansi.h"
#include "helpers.h"
#include "quotes.h"
#include "commands.h"

// ----
// MAIN
// ----

int main(int argc, char *argv[])
{
    // Instantiate the Configuration
    Config *cfg = new Config();

    // Parse the command-line arguments
    int parse_result = cfg->parse_arguments(argc, argv);
    if (parse_result == EXIT_FAILURE)
    {
        return parse_result;
    }

    // Run the command-handler
    try
    {
        std::optional<std::string> subcommand = cfg->get_positional_argument(0).value_or("random");
        if (subcommand == "random")
        {
            show_random_quote(*cfg);
        }
        else if (subcommand == "get")
        {
            get_quote(*cfg);
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
            std::cerr << "Unknown subcommand: " << subcommand.value() << std::endl;
            print_help();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

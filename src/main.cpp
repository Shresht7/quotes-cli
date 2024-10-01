#include <iostream>
#include <optional>
#include <memory>

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
    auto cfg = std::make_unique<Config>();

    // If the output is being redirected, change the format
    if (is_output_redirected())
    {
        IS_COLOR_ENABLED = false;
        cfg->margin = 0;
    }

    // Parse the command-line arguments
    int parse_result = cfg->parse_arguments(argc, argv);
    if (parse_result == EXIT_FAILURE)
    {
        return parse_result;
    }

    // Run the command-handler
    try
    {
        std::string subcommand = cfg->get_positional_argument(0).value_or("random");
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
            std::cerr << "Unknown subcommand: " << subcommand << std::endl;
            print_help();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

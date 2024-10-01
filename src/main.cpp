#include <iostream>
#include <optional>

#include "args.h"
#include "ansi.h"
#include "helpers.h"
#include "quotes.h"

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

    std::optional<std::string> subcommand = cfg->get_positional_argument(0);

    if (subcommand)
    {
        std::cout << subcommand.value() << std::endl;
    }
    else
    {
        std::cout << "Absolutely Nothing" << std::endl;
    }

    try
    {
        // Read the Quotes from the CSV file
        Quotes quotes;
        quotes.read_file(cfg->filepath);

        // If the output is being redirected, change the format
        if (is_output_redirected())
        {
            IS_COLOR_ENABLED = false;
            cfg->margin = 0;
        }

        // Get a random quote and write it to stdout
        if (cfg->plain)
        {
            std::cout << cfg->format_quote(quotes.get_random()) << std::endl;
        }
        else
        {
            std::cout << cfg->format_styled_quote(quotes.get_random()) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1; // Exit with status code 1 indicating failure
    }

    return 0; // Exit with status code 0 indicating success
}

#include <iostream>

#include "args.h"
#include "ansi.h"
#include "helpers.h"
#include "quotes.h"

void show_random_quote(Config &cfg)
{
    // Read the Quotes from the CSV file
    Quotes quotes;
    quotes.read_file(cfg.filepath);

    // If the output is being redirected, change the format
    if (is_output_redirected())
    {
        IS_COLOR_ENABLED = false;
        cfg.margin = 0;
    }

    // Get a random quote and write it to stdout
    if (cfg.plain)
    {
        std::cout << cfg.format_quote(quotes.get_random()) << std::endl;
    }
    else
    {
        std::cout << cfg.format_styled_quote(quotes.get_random()) << std::endl;
    }
}

void get_quote(Config &cfg)
{
    // Read the Quotes from the CSV file
    Quotes quotes;
    quotes.read_file(cfg.filepath);

    // If the output is being redirected, change the format
    if (is_output_redirected())
    {
        IS_COLOR_ENABLED = false;
        cfg.margin = 0;
    }

    // Get the second positional argument as the index
    std::string indexStr = cfg.get_positional_argument(1).value_or("0");
    unsigned int i = atoi(indexStr.c_str());

    // Get a random quote and write it to stdout
    if (cfg.plain)
    {
        std::cout << cfg.format_quote(quotes.get(i)) << std::endl;
    }
    else
    {
        std::cout << cfg.format_styled_quote(quotes.get(i)) << std::endl;
    }
}

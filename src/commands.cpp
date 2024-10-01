#include <iostream>

#include "config.h"
#include "ansi.h"
#include "helpers.h"
#include "quotes.h"

void show_random_quote(Config &cfg)
{
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Read the Quotes from the CSV file
    Quotes quotes;
    quotes.read_file(cfg.filepath);

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

    // Get the second positional argument as the index
    std::string indexStr = cfg.get_positional_argument(1).value_or("0");
    unsigned int i = std::stoi(indexStr);

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

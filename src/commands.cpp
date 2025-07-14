#include <iostream>
#include <filesystem>

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

void list_quotes(Config &cfg)
{
    // Read the quotes from the file
    Quotes quotes;
    quotes.read_file(cfg.filepath);

    if (cfg.output_format == "csv")
    {
        quotes.write_csv("-"); // Use "-" to indicate stdout
    }
    else if (cfg.output_format == "json")
    {
        quotes.write_json("-"); // Use "-" to indicate stdout
    }
    else
    {
        for (unsigned int i = 0; i < quotes.size(); ++i)
        {
            Quote q = quotes.get(i);
            std::cout << i << ": " << q.text << " - " << q.author << std::endl;
        }
    }
}

void create_quote(Config &cfg)
{
    Quotes quotes;
    try
    {
        quotes.read_file(cfg.filepath);
    }
    catch (const std::exception &e)
    {
        // Ensure the directory exists before trying to read/write the file
        make_directories(cfg.filepath);
        // Write the empty Quotes object to create an empty file
        quotes.write_file(cfg.filepath);
    }

    std::string quote_text;
    if (cfg.quote_text.empty())
    {
        std::cout << "Enter quote: ";
        std::getline(std::cin, quote_text);
    }
    else
    {
        quote_text = cfg.quote_text;
    }

    std::string author_name;
    if (cfg.author_name.empty())
    {
        std::cout << "Enter author: ";
        std::getline(std::cin, author_name);
    }
    else
    {
        author_name = cfg.author_name;
    }

    quotes.add_quote({quote_text, author_name});
    quotes.write_file(cfg.filepath);

    std::cout << "Quote added successfully!\tID: " << quotes.size() - 1 << std::endl;
}

void edit_quotes(Config &cfg)
{
    std::string command;
#ifdef _WIN32
    command = "start " + resolve_path(cfg.filepath).string();
#elif __APPLE__
    command = "open " + resolve_path(cfg.filepath).string();
#else
    command = "xdg-open " + resolve_path(cfg.filepath).string();
#endif

    int result = system(command.c_str());
    if (result != 0)
    {
        throw std::runtime_error("Failed to open file: " + resolve_path(cfg.filepath).string());
    }
}

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
    Quote random_quote = quotes.get_random();

    if (cfg.output_format == "csv")
    {
        std::cout << cfg.format_quote_csv(random_quote) << std::endl;
    }
    else if (cfg.output_format == "json")
    {
        std::cout << cfg.format_quote_json(random_quote) << std::endl;
    }
    else if (cfg.plain)
    {
        std::cout << cfg.format_quote(random_quote) << std::endl;
    }
    else
    {
        std::cout << cfg.format_styled_quote(random_quote) << std::endl;
    }
}

void get_quote(Config &cfg)
{
    // Read the Quotes from the CSV file
    Quotes quotes;
    quotes.read_file(cfg.filepath);

    // Get the second positional argument as the index
    std::string indexStr = cfg.get_positional_argument(1).value_or("");
    if (indexStr.empty())
    {
        throw std::runtime_error("Missing quote ID. Usage: quotes get <id>");
    }

    unsigned int i;
    try
    {
        i = std::stoi(indexStr);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::runtime_error("Invalid quote ID: " + indexStr + ". Please provide a valid number.");
    }
    catch (const std::out_of_range &e)
    {
        throw std::runtime_error("Quote ID out of range: " + indexStr + ". Please provide a valid number.");
    }

    Quote quote = quotes.get(i);
    if (cfg.output_format == "csv")
    {
        std::cout << cfg.format_quote_csv(quote) << std::endl;
    }
    else if (cfg.output_format == "json")
    {
        std::cout << cfg.format_quote_json(quote) << std::endl;
    }
    else if (cfg.plain)
    {
        std::cout << cfg.format_quote(quote) << std::endl;
    }
    else
    {
        std::cout << cfg.format_styled_quote(quote) << std::endl;
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

void delete_quote(Config &cfg)
{
    Quotes quotes;
    quotes.read_file(cfg.filepath);

    std::string indexStr = cfg.get_positional_argument(1).value_or("");
    if (indexStr.empty())
    {
        throw std::runtime_error("Missing quote ID. Usage: quotes delete <id>");
    }

    unsigned int index;
    try
    {
        index = std::stoi(indexStr);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::runtime_error("Invalid quote ID: " + indexStr + ". Please provide a valid number.");
    }
    catch (const std::out_of_range &e)
    {
        throw std::runtime_error("Quote ID out of range: " + indexStr + ". Please provide a valid number.");
    }

    quotes.delete_quote(index);
    quotes.write_file(cfg.filepath);

    std::cout << "Quote deleted successfully!" << std::endl;
}

void search_quotes(Config &cfg)
{
    Quotes quotes;
    quotes.read_file(cfg.filepath);

    std::string search_keyword = cfg.get_positional_argument(1).value_or("");

    // If no specific search flags are provided, use the positional argument as a general search keyword
    if (cfg.quote_text.empty() && cfg.author_name.empty() && !search_keyword.empty())
    {
        cfg.quote_text = search_keyword;
        cfg.author_name = search_keyword;
    }

    if (cfg.quote_text.empty() && cfg.author_name.empty())
    {
        throw std::runtime_error("Missing search keyword. Usage: quotes search <keyword> or quotes search --text <keyword> or quotes search --author <keyword>");
    }

    std::cout << "Search Results:" << std::endl;
    bool found_any = false;
    for (unsigned int i = 0; i < quotes.size(); ++i)
    {
        Quote q = quotes.get(i);
        bool text_match = false;
        bool author_match = false;

        if (!cfg.quote_text.empty())
        {
            std::string lower_quote_text = to_lower(q.text);
            std::string lower_search_text = to_lower(cfg.quote_text);
            if (lower_quote_text.find(lower_search_text) != std::string::npos)
            {
                text_match = true;
            }
        }

        if (!cfg.author_name.empty())
        {
            std::string lower_author_name = to_lower(q.author);
            std::string lower_search_author = to_lower(cfg.author_name);
            if (lower_author_name.find(lower_search_author) != std::string::npos)
            {
                author_match = true;
            }
        }

        // If both text and author flags are provided, both must match.
        // If only one is provided, that one must match.
        // If no flags are provided, but a general keyword is, then either text or author must match.
        if ((!cfg.quote_text.empty() && !cfg.author_name.empty() && (text_match || author_match)) ||
            (!cfg.quote_text.empty() && cfg.author_name.empty() && text_match) ||
            (cfg.quote_text.empty() && !cfg.author_name.empty() && author_match) ||
            (search_keyword.empty() && (text_match || author_match)))
        {
            std::cout << i << ": " << q.text << " - " << q.author << std::endl;
            found_any = true;
        }
    }

    if (!found_any)
    {
        std::cout << "No quotes found matching your criteria." << std::endl;
    }
}

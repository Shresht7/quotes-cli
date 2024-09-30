#include <iostream>
#include <sstream>

#include "args.h"
#include "ansi.h"
#include "helpers.h"
#include "quotes.h"

// ------------
// FORMAT QUOTE
// ------------

/// @brief Formats the quote to its appropriate string representation
/// @param q The quote object with the text and author fields
/// @return A string fit for outputting to the console
std::string format_quote(Quote q)
{
    return "\n\"" + q.text + "\"\n  - " + q.author + "\n";
}

std::string format_styled_quote(const Quote &quote, const std::string &separator, std::string &color)
{
    Color clr = color_from_string(color);

    std::string quote_message = " " + quote.text;
    std::string quote_author = "  -- " + quote.author;
    std::string separator_line = " " + std::string(separator.length() * quote_message.length(), separator.front());
    quote_message = ansi_color(quote_message, Color::BrightWhite);
    quote_author = ansi_color(quote_author, Color::BrightBlack);
    separator_line = ansi_color(separator_line, clr);

    std::ostringstream oss;
    oss << "\n"
        << separator_line << "\n"
        << quote_message << "\n"
        << quote_author << "\n"
        << separator_line << "\n";

    return oss.str();
}

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

    try
    {
        // Obtain the filepath from the command-line arguments
        std::string filetype = get_file_extension(cfg->filepath);

        // Read the Quotes from the CSV file
        Quotes quotes;

        // Read quotes based on the specified file extension
        if (filetype == "csv")
        {
            quotes.read_csv(cfg->filepath);
        }
        else if (filetype == "json")
        {
            quotes.read_json(cfg->filepath);
        }
        else
        {
            std::cerr << "Unsupported file type: " << filetype << std::endl;
            return 1;
        }

        // Get a random quote and write it to stdout
        std::cout << format_styled_quote(quotes.get_random(), "=", cfg->color) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0; // Exit with status code 0 indicating success
}

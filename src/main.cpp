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
std::string format_quote(Quote q, unsigned int margin)
{
    std::ostringstream oss;

    oss << repeat("\n", margin)
        << "\"" + q.text + "\"\n - " + q.author
        << repeat("\n", margin);

    return oss.str();
}

std::string format_styled_quote(const Quote &quote, const std::string &border, std::string &color, unsigned int margin)
{
    Color clr = color_from_string(color);

    std::string quote_message = " " + quote.text;
    std::string quote_author = "  -- " + quote.author;
    std::string border_line = " " + std::string(border.length() * quote_message.length(), border.front());
    quote_message = ansi_color(quote_message, Color::BrightWhite);
    quote_author = ansi_color(quote_author, Color::BrightBlack);
    border_line = ansi_color(border_line, clr);

    std::ostringstream oss;
    oss << repeat("\n", margin)
        << border_line << "\n"
        << quote_message << "\n"
        << quote_author << "\n"
        << border_line << repeat("\n", margin);

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
        std::filesystem::path filepath = resolve_path(cfg->filepath);
        std::string filetype = get_file_extension(cfg->filepath);

        // Read the Quotes from the CSV file
        Quotes quotes;

        // Read quotes based on the specified file extension
        if (filetype == "csv")
        {
            quotes.read_csv(filepath.string());
        }
        else if (filetype == "json")
        {
            quotes.read_json(filepath.string());
        }
        else
        {
            std::cerr << "Unsupported file type: " << filetype << std::endl;
            return 1;
        }

        // Get a random quote and write it to stdout
        if (cfg->plain)
        {
            std::cout << format_quote(quotes.get_random(), cfg->margin) << std::endl;
        }
        else
        {
            std::cout << format_styled_quote(quotes.get_random(), cfg->border, cfg->color, cfg->margin) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0; // Exit with status code 0 indicating success
}

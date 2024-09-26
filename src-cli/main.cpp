#include <iostream>
#include <sstream>

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

std::string format_styled_quote(const Quote &quote, const std::string &separator, const std::string &color)
{
    std::string color_code;
    if (color == "BrightMagenta")
    {
        color_code = "\033[95m";
    }
    else if (color == "BrightCyan")
    {
        color_code = "\033[96m";
    }
    else
    {
        color_code = "\033[0m"; // Default color
    }

    std::string reset_code = "\033[0m";
    std::string quote_message = " " + quote.text;
    std::string quote_author = "  -- " + quote.author;
    std::string separator_line = " " + color_code + std::string(separator.length() * quote_message.length(), separator.front()) + reset_code;

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
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return 1; // Exit with status code 1 indicating an error
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    try
    {
        // Obtain the filepath from the command-line arguments
        std::string filepath = argv[1];
        std::string filetype = get_file_extension(filepath);

        // Read the Quotes from the CSV file
        Quotes quotes;

        // Read quotes based on the specified file extension
        if (filetype == "csv")
        {
            quotes.read_csv(filepath);
        }
        else if (filetype == "json")
        {
            quotes.read_json(filepath);
        }
        else
        {
            std::cerr << "Unsupported file type: " << filetype << std::endl;
            return 1;
        }

        // Get a random quote and write it to stdout
        std::cout << format_styled_quote(quotes.get_random(), "=", "BrightCyan") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0; // Exit with status code 0 indicating success
}

#include <iostream>

#include "quotes.h"

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

        // Read the Quotes from the CSV file
        Quotes quotes;
        quotes.read_csv(filepath);

        // Get a random quote and write it to stdout
        std::cout << format_quote(quotes.get_random()) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0; // Exit with status code 0 indicating success
}

/// @brief Formats the quote to its appropriate string representation
/// @param q The quote object with the text and author fields
/// @return A string fit for outputting to the console
std::string format_quote(Quote q)
{
    return "\"" + q.text + "\"\n  - " + q.author;
}

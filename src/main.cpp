#include <iostream>

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
        return 1;
    }

    return 0; // Exit with status code 0 indicating success
}

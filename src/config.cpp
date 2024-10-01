#include <iostream>
#include <sstream>

#include "ansi.h"
#include "config.h"
#include "helpers.h"

/// Version number of the application
const std::string VERSION = "v0.1.0";

/// @brief Prints the version number to the screen
void print_version()
{
    std::cout << VERSION << std::endl;
}

/// @brief The help message to show
const std::string HELP_MESSAGE = "\nUsage: quotes [OPTIONS]\n"
                                 "\n"
                                 "Options:\n"
                                 "\n"
                                 "  -f, --filepath <path>       Path to the CSV file containing quotes (default: quotes.csv)\n"
                                 "  -b, --border <char>         Border character (default: '=')\n"
                                 "  -c, --color <color>         Color for the border (default: 'default')\n"
                                 "  -m, --margin <number>       The number of lines to leave as margin (default: 1)\n"
                                 "  --no-color / --plain        Plain output\n"
                                 "\n"
                                 "  -h, --help                  Show the help message\n"
                                 "  -v, --version               Show the version number\n"
                                 "\n"
                                 "Examples:\n"
                                 "\n"
                                 "  ./quotes -f quotes.csv -s \"-\" -c cyan\n\n";

/// @brief Prints the help message to the screen
void print_help()
{
    std::cout << HELP_MESSAGE << std::endl;
}

// Helper function to check if a string contains another string
// TODO: Change the contains function to take in variadic arguments
bool contains(const char *str, const char *sub)
{
    return std::strstr(str, sub) != nullptr;
}

// Default constructor
Config::Config() : filepath("~\\Data\\quotes.csv"), border("="), margin(1), color("Magenta"), plain(false) {}

// Parse command-line arguments and update the configuration
int Config::parse_arguments(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (contains(argv[i], "-f") || contains(argv[i], "--filepath"))
        {
            if (i + 1 < argc)
            {
                filepath = argv[++i];
            }
            else
            {
                // TODO: Throw error instead
                std::cerr << "Error: -f/--filepath option requires an argument\n";
                return 1;
            }
        }
        else if (contains(argv[i], "-b") || contains(argv[i], "--border"))
        {
            if (i + 1 < argc)
            {
                border = argv[++i];
            }
            else
            {
                std::cerr << "Error: -b/--border option requires an argument\n";
                return 1;
            }
        }
        else if (contains(argv[i], "--no-color") || contains(argv[i], "--plain"))
        {
            IS_COLOR_ENABLED = false;
            plain = true;
        }
        else if (contains(argv[i], "-c") || contains(argv[i], "--color"))
        {
            if (i + 1 < argc)
            {
                color = argv[++i];
            }
            else
            {
                std::cerr << "Error: -c/--color option requires an argument\n";
                return 1;
            }
        }
        else if (contains(argv[i], "-m") || contains(argv[i], "--margin"))
        {
            if (i + 1 < argc)
            {
                margin = atoi(argv[++i]);
            }
            else
            {
                std::cerr << "Error: -m/--margin option requires an argument\n";
                return 1;
            }
        }
        else if (contains(argv[i], "-h") || contains(argv[i], "--help"))
        {
            print_help();
            return 1;
        }
        else if (contains(argv[i], "-v") || contains(argv[i], "--version"))
        {
            print_version();
            return 1;
        }
        else if (contains(argv[i], "-"))
        {
            // At this point, this is an unrecognized flag/option
            std::cerr << "Unknown option: " << argv[i] << "\n";
            print_help();
            return 1;
        }
        else
        {
            // If not an option/flag, treat it as an positional argument
            args.push_back(argv[i]);
        }
    }
    return 0;
}

std::optional<std::string> Config::get_positional_argument(unsigned int n)
{
    if (n >= args.size())
    {
        return std::nullopt;
    }
    return args[n];
}

// ------------
// FORMAT QUOTE
// ------------

/// @brief Formats the quote to its appropriate string representation
/// @param q The quote object with the text and author fields
/// @return A string fit for outputting to the console
std::string Config::format_quote(Quote q)
{
    std::ostringstream oss;

    oss << repeat("\n", margin)
        << "\"" + q.text + "\"\n - " + q.author
        << repeat("\n", margin);

    return oss.str();
}

std::string Config::format_styled_quote(const Quote &quote)
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

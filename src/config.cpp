#include <iostream>
#include <sstream>

#include "ansi.h"
#include "config.h"
#include "helpers.h"

/// Version number of the application
const std::string VERSION = "v0.1.0";

void print_version()
{
    std::cout << VERSION << std::endl;
}

/// @brief The help message to show
const std::string HELP_MESSAGE = "\nUsage: quotes [SUBCOMMAND] [OPTIONS]\n"
                                 "\n"
                                 "Subcommands:\n"
                                 "  random                       Show a random quote\n"
                                 "  get <id>                     Get a specific quote by ID\n"
                                 "  help                         Show the help message\n"
                                 "  version                      Show the version number\n"
                                 "\n"
                                 "Options:\n"
                                 "  -f, --filepath <path>        Path to the CSV file containing quotes (default: quotes.csv)\n"
                                 "  -c, --color                  The text color\n"
                                 "  --author-color               The color to use for the author\n"
                                 "  -m, --margin <number>        The number of lines to leave as margin (default: 1)\n"
                                 "  -b, --border <char>          Border character (default: '=')\n"
                                 "  --border-color <color>       Color for the border (default: 'default')\n"
                                 "  --no-borders                 Disables borders\n"
                                 "  --no-color / --plain         Plain output\n"
                                 "\n"
                                 "  -h, --help                   Show the help message\n"
                                 "  -v, --version                Show the version number\n"
                                 "\n"
                                 "Examples:\n"
                                 "  quotes\n"
                                 "  quotes random\n"
                                 "  quotes --margin 2 --color cyan\n\n";

void print_help()
{
    std::cout << HELP_MESSAGE << std::endl;
}

/// @brief function to check if two strings match (case-insensitive)
bool contains(const char *a, const char *b)
{
    return match(std::string(a), std::string(b));
}

// Default constructor
Config::Config() : filepath("~\\Data\\quotes.csv"),
                   border("="),
                   margin(1),
                   color("BrightWhite"),
                   author_color("BrightBlack"),
                   border_color("Magenta"),
                   no_borders(false),
                   plain(false)
{
}

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
                std::cerr << "Error: -f/--filepath option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (contains(argv[i], "-b") || contains(argv[i], "--border"))
        {
            if (i + 1 < argc)
            {
                border = argv[++i];
                if (border == "" || border == "none")
                {
                    no_borders = true;
                }
            }
            else
            {
                std::cerr << "Error: -b/--border option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (contains(argv[i], "--no-borders"))
        {
            no_borders = true;
        }
        else if (contains(argv[i], "--no-color") || contains(argv[i], "--plain"))
        {
            IS_COLOR_ENABLED = false;
            no_borders = true;
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
                return EXIT_FAILURE;
            }
        }
        else if (contains(argv[i], "--author-color"))
        {
            if (i + 1 < argc)
            {
                author_color = argv[++i];
            }
            else
            {
                std::cerr << "Error: --author-color option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (contains(argv[i], "--border-color"))
        {
            if (i + 1 < argc)
            {
                border_color = argv[++i];
            }
            else
            {
                std::cerr << "Err: --border-color option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (contains(argv[i], "-m") || contains(argv[i], "--margin"))
        {
            if (i + 1 < argc)
            {
                margin = std::stoi(argv[++i]);
            }
            else
            {
                std::cerr << "Error: -m/--margin option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (contains(argv[i], "-h") || contains(argv[i], "--help"))
        {
            print_help();
            return EXIT_FAILURE;
        }
        else if (contains(argv[i], "-v") || contains(argv[i], "--version"))
        {
            print_version();
            return EXIT_FAILURE;
        }
        else if (contains(argv[i], "-"))
        {
            // At this point, this is an unrecognized flag/option
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            print_help();
            return EXIT_FAILURE;
        }
        else
        {
            // If not an option/flag, treat it as an positional argument
            args.push_back(argv[i]);
        }
    }
    return EXIT_SUCCESS;
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

std::string Config::format_quote(const Quote &q)
{
    std::ostringstream oss;
    std::string quote_message = ansi_color('"' + q.text + '"', color_from_string(color));
    std::string quote_author = ansi_color("- " + q.author, color_from_string(author_color));

    oss << repeat("\n", margin)
        << quote_message
        << "\n"
        << quote_author
        << repeat("\n", margin);

    return oss.str();
}

std::string Config::format_styled_quote(const Quote &quote)
{
    std::string quote_message = " " + quote.text;
    std::string quote_author = "  -- " + quote.author;
    quote_message = ansi_color(quote_message, color_from_string(color));
    quote_author = ansi_color(quote_author, color_from_string(author_color));

    std::string border_line = "";
    if (!no_borders)
    {
        border_line = " " + std::string(border.length() * quote_message.length(), border.front());
        border_line = ansi_color(border_line, color_from_string(border_color));
    }

    std::ostringstream oss;
    oss << repeat("\n", margin);

    if (!no_borders)
    {
        oss << border_line << "\n";
    }
    oss << quote_message << "\n"
        << quote_author;

    if (!no_borders)
    {
        oss << "\n"
            << border_line;
    }

    oss << repeat("\n", margin);

    return oss.str();
}

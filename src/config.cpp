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
                                 "  list                         List all quotes\n"
                                 "      --format                    The format to use (`csv`, `json`, `default`)\n"
                                 "  create                       Add a new quote\n"
                                 "      --text                       The quote text (optional)\n"
                                 "      --author                     The author name (optional)\n"
                                 "  help                         Show the help message\n"
                                 "  version                      Show the version number\n"
                                 "\n"
                                 "Options:\n"
                                 "  -f, --filepath <path>        Path to the CSV file containing quotes (default: quotes.csv)\n"
                                 "  -s, --style                  The ansi styles/colors for the quote text\n"
                                 "  --author-style               The ansi styles/colors for the author\n"
                                 "  -m, --margin <number>        The number of lines to leave as margin (default: 1)\n"
                                 "  -b, --border <char>          Border character (default: '=')\n"
                                 "  --border-color <color>       Color for the border (default: 'default')\n"
                                 "  --quotes                     Surround the quote with quotation marks\n"
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

// Default constructor
Config::Config() : filepath("~/Data/quotes.csv"),
                   border("="),
                   margin(1),
                   style("BrightWhite"),
                   author_style("BrightBlack"),
                   border_color("Magenta"),
                   no_borders(false),
                   plain(false),
                   surround_with_quotes(false),
                   output_format("plain")
{
}

// Parse command-line arguments and update the configuration
int Config::parse_arguments(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-f" || arg == "--filepath")
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
        else if (arg == "-b" || arg == "--border")
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
        else if (arg == "--no-borders")
        {
            no_borders = true;
        }
        else if (arg == "--quotes")
        {
            surround_with_quotes = true;
        }
        else if (arg == "--no-color" || arg == "--plain")
        {
            IS_COLOR_ENABLED = false;
            no_borders = true;
            plain = true;
        }
        else if (arg == "-s" || arg == "--style")
        {
            if (i + 1 < argc)
            {
                style = argv[++i];
            }
            else
            {
                std::cerr << "Error: -s/--style option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (arg == "--author-style")
        {
            if (i + 1 < argc)
            {
                author_style = argv[++i];
            }
            else
            {
                std::cerr << "Error: --author-style option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (arg == "--border-color")
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
        else if (arg == "-m" || arg == "--margin")
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
        else if (arg == "-h" || arg == "--help")
        {
            print_help();
            return EXIT_FAILURE;
        }
        else if (arg == "-v" || arg == "--version")
        {
            print_version();
            return EXIT_FAILURE;
        }
        else if (arg == "--text")
        {
            if (i + 1 < argc)
            {
                quote_text = argv[++i];
            }
            else
            {
                quote_text = "";
            }
        }
        else if (arg == "--author")
        {
            if (i + 1 < argc)
            {
                author_name = argv[++i];
            }
            else
            {
                author_name = "";
            }
        }
        else if (arg == "--format")
        {
            if (i + 1 < argc)
            {
                output_format = argv[++i];
            }
            else
            {
                std::cerr << "Error: --format option requires an argument\n";
                return EXIT_FAILURE;
            }
        }
        else if (arg[0] == '-')
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
    std::string quote_text = surround_with_quotes ? "\"" + q.text + "\"" : q.text;
    std::string quote_message = ansi(quote_text, ansi_codes_from_string(style));
    std::string quote_author = ansi("- " + q.author, ansi_codes_from_string(author_style));

    oss << repeat("\n", margin)
        << quote_message
        << "\n"
        << quote_author
        << repeat("\n", margin);

    return oss.str();
}

std::string Config::format_styled_quote(const Quote &quote)
{
    std::string quote_text = surround_with_quotes ? "\"" + quote.text + "\"" : quote.text;
    std::string quote_message = " " + quote_text;
    std::string quote_author = "  -- " + quote.author;

    std::string border_line = "";
    if (!no_borders)
    {
        border_line = " " + std::string(border.length() * quote_message.length(), border.front());
        border_line = ansi(border_line, ansi_codes_from_string(border_color));
    }

    // Apply colors after determining the length of the border line as ANSI codes can mess with the length
    quote_message = ansi(quote_message, ansi_codes_from_string(style));
    quote_author = ansi(quote_author, ansi_codes_from_string(author_style));

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

#include <iostream>

#include "args.h"

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
                                 "  -f, --filepath <path>     Path to the CSV file containing quotes (default: quotes.csv)\n"
                                 "  -s, --separator <char>    Separator character (default: '=')\n"
                                 "  -c, --color <color>       Color for the separator (default: 'default')\n"
                                 "\n"
                                 "  -h, --help                Show the help message\n"
                                 "  -v, --version             Show the version number\n"
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
Config::Config() : filepath("~\\Data\\quotes.csv"), separator("="), color("Default") {}

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
        else if (contains(argv[i], "-s") || contains(argv[i], "--separator"))
        {
            if (i + 1 < argc)
            {
                separator = argv[++i];
            }
            else
            {
                std::cerr << "Error: -s/--separator option requires an argument\n";
                return 1;
            }
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
        else
        {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            print_help();
            return 1;
        }
    }
    return 0;
}

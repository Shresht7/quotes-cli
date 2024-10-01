#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <optional>
#include "quotes.h"

void print_version();

void print_help();

// Configuration struct for CLI
class Config
{
private:
    /// @brief The vector of positional arguments
    std::vector<std::string> args;

public:
    /// @brief The path to the source file containing the quotes
    std::string filepath;

    /// @brief The style of borders
    std::string border;

    /// @brief The border color
    std::string color;

    /// @brief The number of blank lines before and after the output
    unsigned int margin;

    /// @brief Indicates if the output should be plain and simple
    bool plain;

    // Default Constructor
    Config();

    /// @brief Parses the command-line arguments
    /// @param argc The total count of arguments
    /// @param argv The vector containing the command-line arguments
    int parse_arguments(int argc, char *argv[]);

    /// @brief Retrieve the positional argument at the given index
    /// @param n The position of the argument
    /// @return The positional argument appearing at the given index or "" if it doesn't exist
    std::optional<std::string> get_positional_argument(unsigned int n);

    std::string format_quote(Quote q);
    std::string format_styled_quote(const Quote &quote);
};

#endif // CONFIG_H

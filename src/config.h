#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <optional>
#include "quotes.h"

/// @brief Prints the version number to the screen
void print_version();

/// @brief Prints the help message to the screen
void print_help();

// Configuration class for CLI
class Config
{
private:
    /// @brief The vector of positional arguments
    std::vector<std::string> args;

public:
    /// @brief The path to the source file containing the quotes
    std::string filepath;

    /// @brief The ansi styles/colors for the quote text
    std::string style;

    /// @brief The ansi styles/colors for the author
    std::string author_style;

    /// @brief The style of borders
    std::string border;

    /// @brief The border color
    std::string border_color;

    /// @brief The number of blank lines before and after the output
    unsigned int margin;

    /// @brief Indicates whether to draw borders or not
    bool no_borders;

    /// @brief Indicates if the output should be plain and simple
    bool plain;

    /// @brief Indicates whether to surround the quote with quotation marks
    bool surround_with_quotes;

    // Default Constructor
    Config();

    /// @brief Parses the command-line arguments
    /// @param argc The total count of arguments
    /// @param argv The vector containing the command-line arguments
    int parse_arguments(int argc, char *argv[]);

    /// @brief Retrieve the positional argument at the given index
    /// @param n The position of the argument
    /// @return The positional argument appearing at the given index or std::nullopt if it doesn't exist
    std::optional<std::string> get_positional_argument(unsigned int n);

    /// @brief Formats the quote to its appropriate string representation
    /// @param quote The quote object with the text and author fields
    /// @return A string fit for outputting to the console
    std::string format_quote(const Quote &quote);

    /// @brief Formats the styled quote for outputting to the console
    /// @param quote The quote object with the text and author fields
    /// @return A styled string fit for outputting to the console
    std::string format_styled_quote(const Quote &quote);
};

#endif // CONFIG_H

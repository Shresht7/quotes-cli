#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <optional>
#include "quotes.h"

void print_version();

void print_help();

// Configuration struct for CLI
class Config
{
private:
    std::vector<std::string> args;

public:
    std::string filepath;

    std::string border;
    std::string color;
    unsigned int margin;

    bool plain;

    // Default Constructor
    Config();

    // Method to parse command-line arguments
    int parse_arguments(int argc, char *argv[]);

    /// @brief Retrieve the positional argument at the given index
    /// @param n The position of the argument
    /// @return The positional argument appearing at the given index or "" if it doesn't exist
    std::optional<std::string> get_positional_argument(unsigned int n);

    std::string format_quote(Quote q);

    std::string format_styled_quote(const Quote &quote);
};

#endif // ARGS_H

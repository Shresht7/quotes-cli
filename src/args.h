#ifndef ARGS_H
#define ARGS_H

#include <string>
#include "quotes.h"

void print_version();

void print_help();

// Configuration struct for CLI
class Config
{
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

    std::string format_quote(Quote q);

    std::string format_styled_quote(const Quote &quote);
};

#endif // ARGS_H

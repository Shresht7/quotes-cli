#ifndef ARGS_H
#define ARGS_H

#include <string>

void print_version();

void print_help();

// Configuration struct for CLI
class Config
{
public:
    std::string filepath;
    std::string separator;
    std::string color;

    // Default Constructor
    Config();

    // Method to parse command-line arguments
    int parse_arguments(int argc, char *argv[]);
};

#endif // ARGS_H

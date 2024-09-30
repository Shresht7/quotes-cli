#ifndef ARGS_H
#define ARGS_H

const std::string VERSION;

void print_version();

const std::string HELP_MESSAGE;

void print_help();

struct Config
{
    std::string filepath;
    std::string separator;
    std::string color;
};

bool contains(const std::string str, const std::string sub);

int parse_arguments(int argc, char *argv[], Config &cfg);

#endif // ARGS_H

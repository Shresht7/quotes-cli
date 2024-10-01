#ifndef COMMANDS_H
#define COMMANDS_H

#include "config.h"

/// @brief Displays a random quote from the CSV file.
/// @param cfg The configuration object containing settings for displaying the quote.
void show_random_quote(Config &cfg);

/// @brief Retrieves and displays a specific quote by index from the CSV file.
/// @param cfg The configuration object containing settings for displaying the quote.
void get_quote(Config &cfg);

#endif // COMMANDS_H

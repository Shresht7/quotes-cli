#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <vector>

/// @brief Trim leading and trailing whitespace and quotes from a string
/// @param str The string to trim
/// @return The trimmed string
std::string trim(const std::string &str);

/// @brief Split a line into fields respecting quoted commas
/// @param line The CSV line to split
/// @return A vector of strings representing the fields
std::vector<std::string> split_csv_line(const std::string &line);

#endif // HELPERS_H

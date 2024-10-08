#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <vector>
#include <filesystem>

/// @brief Compares the two strings and returns true if they are the same. (Case-Insensitive)
/// @return A boolean indicating whether two strings are the same.
bool match(std::string &a, std::string &b);

/// @brief Create a new string by repeating the given characters
/// @param s The string to repeat
/// @param count The number of times to repeat the string
/// @return A new string created by repeating the given characters
std::string repeat(const std::string &s, unsigned int count);

/// @brief Trim leading and trailing whitespace and quotes from a string
/// @param str The string to trim
/// @return The trimmed string
std::string trim(const std::string &str);

/// @brief Split a line into fields respecting quoted commas
/// @param line The CSV line to split
/// @return A vector of strings representing the fields
std::vector<std::string> split_csv_line(const std::string &line);

/// @brief Resolves the given string as a filesystem path
/// @param path The path string to resolve
/// @return The actual filesystem path
std::filesystem::path resolve_path(const std::string &path);

/// @brief Helper function to extract the file extension from a file path
std::string get_file_extension(const std::string &filepath);

/// @brief Determine if the standard output is being redirected somewhere
/// @return A boolean indicating true if STDOUT is being redirected, or false if outputting to the screen
bool is_output_redirected();

#endif // HELPERS_H

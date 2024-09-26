#include <string>
#include <cctype>

/// @brief Trim leading and trailing whitespace and quotes from a string
/// @param str The string to trim
/// @return The trimmed string

std::string trim(const std::string &str)
{
    size_t start = 0;
    size_t end = str.size();

    // Trim leading whitespace
    while (start < end && std::isspace(static_cast<unsigned char>(str[start])))
    {
        start++;
    }

    // Trim trailing whitespace
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1])))
    {
        end--;
    }

    // Trim leading and trailing quotes
    if (start < end && str[start] == '"')
    {
        start++;
    }
    if (end > start && str[end - 1] == '"')
    {
        end--;
    }

    return str.substr(start, end - start);
}

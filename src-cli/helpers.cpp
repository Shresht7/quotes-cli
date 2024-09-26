#include <string>
#include <vector>
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

/// @brief Split a line into fields respecting quoted commas
/// @param line The CSV line to split
/// @return A vector of strings representing the fields
std::vector<std::string> split_csv_line(const std::string &line)
{
    std::vector<std::string> result;
    std::string item;
    bool in_quotes = false;

    for (char c : line)
    {
        if (c == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (c == ',' && !in_quotes)
        {
            result.push_back(trim(item));
            item.clear();
        }
        else
        {
            item += c;
        }
    }
    result.push_back(trim(item));
    return result;
}

// Function to extract the file extension from a file path
std::string get_file_extension(const std::string &filepath)
{
    size_t last_dot = filepath.find_last_of(".");
    if (last_dot == std::string::npos)
    {
        return ""; // No file extension found
    }
    return filepath.substr(last_dot + 1); // Return substring after the last dot
}

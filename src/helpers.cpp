#include <string>
#include <vector>
#include <cctype>
#include <filesystem>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

bool match(std::string &a, std::string &b)
{
    // Transform to lowercase
    for (char &c : a)
    {
        c = std::tolower(c);
    }
    for (char &c : b)
    {
        c = std::tolower(c);
    }
    return a == b;
}

std::string repeat(const std::string &s, unsigned int count)
{
    std::string result;
    result.reserve(s.size() * count); // Reserve space to improve performance by reducing the number of re-allocations required
    for (int i = 0; i < count; i++)
    {
        result += s;
    }
    return result;
}

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

/// @brief  the location of the HOME or USERPROFILE from the environment variables
const char *get_home()
{
    const char *home = std::getenv("HOME");
    if (!home)
    {
        const char *userprofile = std::getenv("USERPROFILE");
        if (!userprofile)
        {
            throw std::runtime_error("HOME/USERPROFILE Environment Variable not set");
        }
        return userprofile;
    }
    return home;
}

std::filesystem::path resolve_path(const std::string &path)
{
    // Parse the string as a filesystem path
    std::filesystem::path Location{path};

    // If the location is empty or is a regular absolute or relative path...
    if (Location.empty() || Location.string()[0] != '~')
    {
        return path; // ... return as is
    }
    Location = Location.string().substr(1);

    // Get the HOME
    const char *home = get_home();

    // Construct the full-path and return it
    return std::filesystem::path(home) / Location.relative_path();
}

std::string get_file_extension(const std::string &filepath)
{
    size_t last_dot = filepath.find_last_of(".");
    if (last_dot == std::string::npos)
    {
        return ""; // No file extension found
    }
    return filepath.substr(last_dot + 1); // Return substring after the last dot
}

bool is_output_redirected()
{
#ifdef _WIN32
    return isatty(_fileno(stdout)) == 0;
#else
    return isatty(fileno(stdout)) == 0;
#endif
}

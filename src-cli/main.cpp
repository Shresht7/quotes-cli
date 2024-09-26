#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

// Define a struct to store quotes and authors
struct Quote
{
    std::string text;
    std::string author;
};

/// @brief Trim leading and trailing whitespace and quotes from a string
/// @param str The string to trim
/// @return The trimmed string
std::string trim(const std::string &str)
{
    size_t start = 0;
    size_t end = str.size();

    // Trim leading whitespace
    while (start < end && std::isspace(str[start]))
    {
        start++;
    }

    // Trim trailing whitespace
    while (end > start && std::isspace(str[end - 1]))
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
    std::stringstream ss(line);
    std::string item;
    bool in_quotes = false;

    while (ss.good())
    {
        char c = ss.get();
        if (c == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (c == ',' && !in_quotes)
        {
            result.push_back(item);
            item.clear();
        }
        else
        {
            item += c;
        }
    }
    result.push_back(item);
    return result;
}

/// @brief Read the CSV file and parse the quotes
/// @param filepath Path to the CSV file containing the quotes
/// @param quotes The vector to store the quotes data
void read_csv(const std::string &filepath, std::vector<Quote> &quotes)
{
    std::ifstream file(filepath);

    // Show an error and exit if the file cannot be opened
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> fields = split_csv_line(line);
        if (fields.size() == 2)
        {
            quotes.push_back({trim(fields[0]), trim(fields[1])});
        }
    }

    file.close();

    if (quotes.empty())
    {
        throw std::runtime_error("The file is empty or contains no valid quotes.");
    }
}

/// @brief Retrieve a random quote from the quotes vector
/// @param quotes The vector of quotes
/// @return A random quote formatted as a string
std::string get_random_quote(const std::vector<Quote> &quotes)
{
    int index = std::rand() % quotes.size();
    return "\"" + quotes[index].text + "\"\n  - " + quotes[index].author;
}

// ----
// MAIN
// ----

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return 1; // Exit with status code 1 indicating an error
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    try
    {
        // Obtain the filepath from the command-line arguments
        std::string filepath = argv[1];

        // Read the Quotes from the CSV file
        std::vector<Quote> quotes;
        read_csv(filepath, quotes);

        // Get a random quote and write it to stdout
        std::cout << get_random_quote(quotes) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0; // Exit with status code 0 indicating success
}

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

/// @brief Trim leading and trailing quotes from a string
/// @param str The string to trim
/// @return The trimmed string
std::string trim(const std::string &str)
{
    size_t start = str.front() == '"' ? 1 : 0;
    size_t end = str.back() == '"' ? str.size() - 1 : str.size();
    return str.substr(start, end - start);
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
        std::stringstream ss(line);
        std::string quote, author;

        if (std::getline(ss, quote, ',') && std::getline(ss, author))
        {
            quotes.push_back({trim(quote), trim(author)});
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
/// @return A random quote as a string
std::string get_random_quote(const std::vector<Quote> &quotes)
{
    int index = std::rand() % quotes.size();
    return quotes[index].text + "\n\t - " + quotes[index].author;
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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

/// @brief Read the CSV file and parse the quotes
/// @param filepath Path to the CSV file containing the quotes
/// @param quotes The vector to store the quotes data
void read_csv(const std::string &filepath, std::vector<std::string> &quotes)
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
        quotes.push_back(line);
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
std::string get_random_quote(const std::vector<std::string> &quotes)
{
    int index = std::rand() % quotes.size();
    return quotes[index];
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
        std::vector<std::string> quotes;
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

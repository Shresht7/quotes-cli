#include <iostream>
#include <fstream>
#include <string>

#include "helpers.h"
#include "quotes.h"

/// @brief Read the CSV file and parse the quotes
/// @param filepath Path to the CSV file containing the quotes
void Quotes::read_csv(const std::string &filepath)
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
            quotes.push_back({fields[0], fields[1]});
        }
    }

    file.close();

    if (quotes.empty())
    {
        throw std::runtime_error("The file is empty or contains no valid quotes.");
    }
}

/// @brief Retrieve a random quote from the quotes vector
/// @return A random quote from the list
Quote Quotes::get_random() const
{
    if (quotes.empty())
    {
        throw std::runtime_error("No quotes available.");
    }
    int index = std::rand() % quotes.size();
    return quotes[index];
}

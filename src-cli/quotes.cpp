#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include <nlohmann/json.hpp> // Include the JSON library
using json = nlohmann::json;

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

/// @brief Read the JSON file and parse the quotes
/// @param filepath Path to the JSON file containing the quotes
void Quotes::read_json(const std::string &filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open JSON file");
    }

    json j;
    file >> j; // Parse the JSON data into a json object
    file.close();

    // Assuming the JSON structure is an array of objects with "quote" and "author"
    for (const auto &item : j)
    {
        if (item.contains("quote") && item.contains("author"))
        {
            quotes.push_back({trim(item["quote"].get<std::string>()),
                              trim(item["author"].get<std::string>())});
        }
    }

    if (quotes.empty())
    {
        throw std::runtime_error("The JSON file contains no valid quotes.");
    }
}

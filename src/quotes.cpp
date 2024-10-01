#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include <nlohmann/json.hpp> // Include the JSON library
using json = nlohmann::json;

#include "helpers.h"
#include "quotes.h"

void Quotes::read_file(const std::string &filepath)
{
    // Resolve the filepath from the given string
    std::filesystem::path path = resolve_path(filepath);
    std::string filetype = get_file_extension(filepath);

    // Read the file with the appropriate reader
    if (filetype == "csv")
    {
        read_csv(path.string());
    }
    else if (filetype == "json")
    {
        read_json(path.string());
    }
    else
    {
        throw std::runtime_error("Unsupported file type: " + path.string());
    }
}

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

Quote Quotes::get_random() const
{
    if (quotes.empty())
    {
        throw std::runtime_error("No quotes available.");
    }
    int index = std::rand() % quotes.size();
    return quotes[index];
}

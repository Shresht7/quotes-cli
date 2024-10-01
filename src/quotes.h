#ifndef QUOTES_H
#define QUOTES_H

#include <string>
#include <vector>

// Define a struct to store quotes and authors
struct Quote
{
    std::string text;
    std::string author;
};

class Quotes
{
private:
    /// Vector to hold all the quotes
    std::vector<Quote> quotes;

    /// @brief Read the CSV file and parse the quotes
    /// @param filepath Path to the CSV file containing the quotes
    void read_csv(const std::string &filepath);

    /// @brief Read the JSON file and parse the quotes
    /// @param filepath Path to the JSON file containing the quotes
    void read_json(const std::string &filepath);

public:
    Quotes() = default;

    /// @brief Retrieves a single quote from the vector
    /// @param n The index of the quote
    /// @return A single quote from the list of quotes
    Quote get(unsigned int n);

    /// @brief Retrieves a random quote from the vector
    /// @return A random quote from the list of quotes
    Quote get_random() const;

    /// @brief Reads the given file to parse the quotes
    /// @param filepath The path to the CSV or JSON file containing the quotes
    void read_file(const std::string &filepath);
};

#endif // QUOTES_H

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
public:
    Quotes() = default;
    void read_csv(const std::string &filepath);
    Quote get_random() const;

private:
    std::vector<Quote> quotes;
};

#endif // QUOTES_H

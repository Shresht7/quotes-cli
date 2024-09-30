#ifndef ANSI_H
#define ANSI_H

#include <string>

// Enumeration for ANSI colors
enum class Color
{
    Black = 30,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White = 37,
    Default = 39,
    BgBlack = 40,
    BgRed,
    BgGreen,
    BgYellow,
    BgBlue,
    BgMagenta,
    BgCyan,
    BgWhite = 47,
    BgDefault = 49,
    BrightBlack = 90,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,
    BrightDefault = 99,
    BgBrightBlack = 100,
    BgBrightRed,
    BgBrightGreen,
    BgBrightYellow,
    BgBrightBlue,
    BgBrightMagenta,
    BgBrightCyan,
    BgBrightWhite = 107,
    BgBrightDefault = 109,
};

extern bool IS_COLOR_ENABLED;

// Check if ANSI colors are enabled
bool is_color_enabled();

// Returns the ANSI code for the given color
std::string code(Color c);

// Apply ANSI color to a string
std::string ansi_color(const std::string &text, Color color);

// Convert string to color enum
Color color_from_string(std::string &color);

#endif // ANSI_H

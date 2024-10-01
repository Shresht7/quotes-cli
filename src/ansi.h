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

// Dictates whether ANSI colors are enabled
extern bool IS_COLOR_ENABLED;

/// @brief Returns a boolean indicating whether ANSI colors are enabled or not
/// @return A boolean indicating whether ANSI colors are enabled or not
bool is_color_enabled();

/// @brief Creates the ANSI code for the given color
/// @param c The color from the Color enum
/// @return A string representing the ANSI code for the given color
std::string code(Color c);

/// @brief Wraps the given text in the correct ANSI color codes
/// @param text The text to apply ANSI styling to
/// @param color The color to use for the ANSI code
/// @return An ANSI string to render colors on the terminal
std::string ansi_color(const std::string &text, Color color);

/// @brief Parse the ANSI Color from a string
/// @param str The string to parse
/// @return The color from the ANSI Color enum
Color color_from_string(std::string &color);

#endif // ANSI_H

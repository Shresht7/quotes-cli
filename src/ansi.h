#ifndef ANSI_H
#define ANSI_H

#include <string>
#include <vector>

// Enumeration for ANSI styles and colors
enum class AnsiCode
{
    // Styles
    Bold = 1,
    Dim,
    Italic,
    Underline,
    Blink,
    Reverse = 7,
    Hidden,
    Strikethrough,

    // Foreground colors
    Black = 30,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Default = 39,

    // Background colors
    BgBlack = 40,
    BgRed,
    BgGreen,
    BgYellow,
    BgBlue,
    BgMagenta,
    BgCyan,
    BgWhite,
    BgDefault = 49,

    // Bright foreground colors
    BrightBlack = 90,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,

    // Bright background colors
    BgBrightBlack = 100,
    BgBrightRed,
    BgBrightGreen,
    BgBrightYellow,
    BgBrightBlue,
    BgBrightMagenta,
    BgBrightCyan,
    BgBrightWhite,
};

// Dictates whether ANSI colors are enabled
extern bool IS_COLOR_ENABLED;

/// @brief Returns a boolean indicating whether ANSI colors are enabled or not
/// @return A boolean indicating whether ANSI colors are enabled or not
bool is_color_enabled();

/// @brief Creates the ANSI code for the given colors
/// @param c A vector of colors from the AnsiCode enum
/// @return A string representing the ANSI code for the given colors
std::string code(std::vector<AnsiCode> c);

/// @brief Wraps the given text in the correct ANSI color codes
/// @param text The text to apply ANSI styling to
/// @param colors The colors to use for the ANSI code
/// @return An ANSI string to render colors on the terminal
std::string ansi_color(const std::string &text, std::vector<AnsiCode> colors);

/// @brief Parse ANSI codes from a string
/// @param str The string to parse (e.g. "red,bold")
/// @return A vector of AnsiCode enums
std::vector<AnsiCode> color_from_string(std::string &color);

#endif // ANSI_H

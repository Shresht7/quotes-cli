#include <cstdlib>
#include <stdexcept>

#include "ansi.h"

// Environment variable for disabling colors
const char *ENV_NO_COLOR = "NO_COLOR";

/// ANSI Reset Code: Resets the styles to the defaults
const std::string ANSI_RESET = "\x1b[0m";

/// @brief Returns a boolean indicating whether ANSI colors are enabled or not
/// @return A boolean indicating whether ANSI colors are enabled or not
bool is_color_enabled()
{
    const char *no_color = std::getenv(ENV_NO_COLOR);
    bool is_no_color = no_color != nullptr && std::string(no_color) != "";
    return !is_no_color;
}

/// @brief Creates the ANSI code for the given color
/// @param c The color from the Color enum
/// @return A string representing the ANSI code for the given color
std::string code(Color c)
{
    return "\x1b[" + std::to_string(static_cast<int>(c)) + "m";
}

/// @brief Wraps the given text in the correct ANSI color codes
/// @param text The text to apply ANSI styling to
/// @param color The color to use for the ANSI code
/// @return An ANSI string to render colors on the terminal
std::string ansi_color(const std::string &text, Color color)
{
    if (is_color_enabled())
    {
        return code(color) + text + ANSI_RESET;
    }
    else
    {
        return text;
    }
}

// -----------
// FROM STRING
// -----------

/// @brief Parse the ANSI Color from a string
/// @param str The string to parse
/// @return The color from the ANSI Color enum
Color color_from_string(const std::string &str)
{
    if (str == "Black")
        return Color::Black;
    else if (str == "Red")
        return Color::Red;
    else if (str == "Green")
        return Color::Green;
    else if (str == "Yellow")
        return Color::Yellow;
    else if (str == "Blue")
        return Color::Blue;
    else if (str == "Magenta")
        return Color::Magenta;
    else if (str == "Cyan")
        return Color::Cyan;
    else if (str == "White")
        return Color::White;
    else if (str == "Default")
        return Color::Default;
    else if (str == "BgBlack")
        return Color::BgBlack;
    else if (str == "BgRed")
        return Color::BgRed;
    else if (str == "BgGreen")
        return Color::BgGreen;
    else if (str == "BgYellow")
        return Color::BgYellow;
    else if (str == "BgBlue")
        return Color::BgBlue;
    else if (str == "BgMagenta")
        return Color::BgMagenta;
    else if (str == "BgCyan")
        return Color::BgCyan;
    else if (str == "BgWhite")
        return Color::BgWhite;
    else if (str == "BgDefault")
        return Color::BgDefault;
    else if (str == "BrightBlack")
        return Color::BrightBlack;
    else if (str == "BrightRed")
        return Color::BrightRed;
    else if (str == "BrightGreen")
        return Color::BrightGreen;
    else if (str == "BrightYellow")
        return Color::BrightYellow;
    else if (str == "BrightBlue")
        return Color::BrightBlue;
    else if (str == "BrightMagenta")
        return Color::BrightMagenta;
    else if (str == "BrightCyan")
        return Color::BrightCyan;
    else if (str == "BrightWhite")
        return Color::BrightWhite;
    else if (str == "BrightDefault")
        return Color::BrightDefault;
    else if (str == "BgBrightBlack")
        return Color::BgBrightBlack;
    else if (str == "BgBrightRed")
        return Color::BgBrightRed;
    else if (str == "BgBrightGreen")
        return Color::BgBrightGreen;
    else if (str == "BgBrightYellow")
        return Color::BgBrightYellow;
    else if (str == "BgBrightBlue")
        return Color::BgBrightBlue;
    else if (str == "BgBrightMagenta")
        return Color::BgBrightMagenta;
    else if (str == "BgBrightCyan")
        return Color::BgBrightCyan;
    else if (str == "BgBrightWhite")
        return Color::BgBrightWhite;
    else if (str == "BgBrightDefault")
        return Color::BgBrightDefault;
    else
        throw std::invalid_argument("Unknown color: " + str);
}

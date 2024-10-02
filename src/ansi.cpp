#include <cstdlib>
#include <stdexcept>

#include "ansi.h"
#include "helpers.h"

// ---------
// ANSI CODE
// ---------

/// ANSI Reset Code: Resets the styles to the defaults
const std::string ANSI_RESET = "\x1b[0m";

std::string code(Color c)
{
    return "\x1b[" + std::to_string(static_cast<int>(c)) + "m";
}

// ----------
// ANSI COLOR
// ----------

// Environment variable for disabling colors
const char *ENV_NO_COLOR = "NO_COLOR";

bool IS_COLOR_ENABLED = true;

bool is_color_enabled()
{
    const char *no_color = std::getenv(ENV_NO_COLOR);
    bool is_no_color = no_color != nullptr && std::string(no_color) != "";
    return IS_COLOR_ENABLED && !is_no_color;
}

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

Color color_from_string(std::string &str)
{
    std::string Black = "Black";
    std::string Red = "Red";
    std::string Green = "Green";
    std::string Yellow = "Yellow";
    std::string Blue = "Blue";
    std::string Magenta = "Magenta";
    std::string Cyan = "Cyan";
    std::string White = "White";
    std::string Default = "Default";
    std::string BgBlack = "BgBlack";
    std::string BgRed = "BgRed";
    std::string BgGreen = "BgGreen";
    std::string BgYellow = "BgYellow";
    std::string BgBlue = "BgBlue";
    std::string BgMagenta = "BgMagenta";
    std::string BgCyan = "BgCyan";
    std::string BgWhite = "BgWhite";
    std::string BgDefault = "BgDefault";
    std::string BrightBlack = "BrightBlack";
    std::string BrightRed = "BrightRed";
    std::string BrightGreen = "BrightGreen";
    std::string BrightYellow = "BrightYellow";
    std::string BrightBlue = "BrightBlue";
    std::string BrightMagenta = "BrightMagenta";
    std::string BrightCyan = "BrightCyan";
    std::string BrightWhite = "BrightWhite";
    std::string BrightDefault = "BrightDefault";
    std::string BgBrightBlack = "BgBrightBlack";
    std::string BgBrightRed = "BgBrightRed";
    std::string BgBrightGreen = "BgBrightGreen";
    std::string BgBrightYellow = "BgBrightYellow";
    std::string BgBrightBlue = "BgBrightBlue";
    std::string BgBrightMagenta = "BgBrightMagenta";
    std::string BgBrightCyan = "BgBrightCyan";
    std::string BgBrightWhite = "BgBrightWhite";
    std::string BgBrightDefault = "BgBrightDefault";

    if (match(str, Black))
        return Color::Black;
    else if (match(str, Red))
        return Color::Red;
    else if (match(str, Green))
        return Color::Green;
    else if (match(str, Yellow))
        return Color::Yellow;
    else if (match(str, Blue))
        return Color::Blue;
    else if (match(str, Magenta))
        return Color::Magenta;
    else if (match(str, Cyan))
        return Color::Cyan;
    else if (match(str, White))
        return Color::White;
    else if (match(str, Default))
        return Color::Default;
    else if (match(str, BgBlack))
        return Color::BgBlack;
    else if (match(str, BgRed))
        return Color::BgRed;
    else if (match(str, BgGreen))
        return Color::BgGreen;
    else if (match(str, BgYellow))
        return Color::BgYellow;
    else if (match(str, BgBlue))
        return Color::BgBlue;
    else if (match(str, BgMagenta))
        return Color::BgMagenta;
    else if (match(str, BgCyan))
        return Color::BgCyan;
    else if (match(str, BgWhite))
        return Color::BgWhite;
    else if (match(str, BgDefault))
        return Color::BgDefault;
    else if (match(str, BrightBlack))
        return Color::BrightBlack;
    else if (match(str, BrightRed))
        return Color::BrightRed;
    else if (match(str, BrightGreen))
        return Color::BrightGreen;
    else if (match(str, BrightYellow))
        return Color::BrightYellow;
    else if (match(str, BrightBlue))
        return Color::BrightBlue;
    else if (match(str, BrightMagenta))
        return Color::BrightMagenta;
    else if (match(str, BrightCyan))
        return Color::BrightCyan;
    else if (match(str, BrightWhite))
        return Color::BrightWhite;
    else if (match(str, BrightDefault))
        return Color::BrightDefault;
    else if (match(str, BgBrightBlack))
        return Color::BgBrightBlack;
    else if (match(str, BgBrightRed))
        return Color::BgBrightRed;
    else if (match(str, BgBrightGreen))
        return Color::BgBrightGreen;
    else if (match(str, BgBrightYellow))
        return Color::BgBrightYellow;
    else if (match(str, BgBrightBlue))
        return Color::BgBrightBlue;
    else if (match(str, BgBrightMagenta))
        return Color::BgBrightMagenta;
    else if (match(str, BgBrightCyan))
        return Color::BgBrightCyan;
    else if (match(str, BgBrightWhite))
        return Color::BgBrightWhite;
    else if (match(str, BgBrightDefault))
        return Color::BgBrightDefault;
    else
        throw std::invalid_argument("Unknown color: " + str);
}

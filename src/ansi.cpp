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
    if (match(str, std::string("Black")))
        return Color::Black;
    else if (match(str, std::string("Red")))
        return Color::Red;
    else if (match(str, std::string("Green")))
        return Color::Green;
    else if (match(str, std::string("Yellow")))
        return Color::Yellow;
    else if (match(str, std::string("Blue")))
        return Color::Blue;
    else if (match(str, std::string("Magenta")))
        return Color::Magenta;
    else if (match(str, std::string("Cyan")))
        return Color::Cyan;
    else if (match(str, std::string("White")))
        return Color::White;
    else if (match(str, std::string("Default")))
        return Color::Default;
    else if (match(str, std::string("BgBlack")))
        return Color::BgBlack;
    else if (match(str, std::string("BgRed")))
        return Color::BgRed;
    else if (match(str, std::string("BgGreen")))
        return Color::BgGreen;
    else if (match(str, std::string("BgYellow")))
        return Color::BgYellow;
    else if (match(str, std::string("BgBlue")))
        return Color::BgBlue;
    else if (match(str, std::string("BgMagenta")))
        return Color::BgMagenta;
    else if (match(str, std::string("BgCyan")))
        return Color::BgCyan;
    else if (match(str, std::string("BgWhite")))
        return Color::BgWhite;
    else if (match(str, std::string("BgDefault")))
        return Color::BgDefault;
    else if (match(str, std::string("BrightBlack")))
        return Color::BrightBlack;
    else if (match(str, std::string("BrightRed")))
        return Color::BrightRed;
    else if (match(str, std::string("BrightGreen")))
        return Color::BrightGreen;
    else if (match(str, std::string("BrightYellow")))
        return Color::BrightYellow;
    else if (match(str, std::string("BrightBlue")))
        return Color::BrightBlue;
    else if (match(str, std::string("BrightMagenta")))
        return Color::BrightMagenta;
    else if (match(str, std::string("BrightCyan")))
        return Color::BrightCyan;
    else if (match(str, std::string("BrightWhite")))
        return Color::BrightWhite;
    else if (match(str, std::string("BrightDefault")))
        return Color::BrightDefault;
    else if (match(str, std::string("BgBrightBlack")))
        return Color::BgBrightBlack;
    else if (match(str, std::string("BgBrightRed")))
        return Color::BgBrightRed;
    else if (match(str, std::string("BgBrightGreen")))
        return Color::BgBrightGreen;
    else if (match(str, std::string("BgBrightYellow")))
        return Color::BgBrightYellow;
    else if (match(str, std::string("BgBrightBlue")))
        return Color::BgBrightBlue;
    else if (match(str, std::string("BgBrightMagenta")))
        return Color::BgBrightMagenta;
    else if (match(str, std::string("BgBrightCyan")))
        return Color::BgBrightCyan;
    else if (match(str, std::string("BgBrightWhite")))
        return Color::BgBrightWhite;
    else if (match(str, std::string("BgBrightDefault")))
        return Color::BgBrightDefault;
    else
        throw std::invalid_argument("Unknown color: " + str);
}

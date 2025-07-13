#include <vector>
#include <cstdlib>
#include <stdexcept>

#include "ansi.h"
#include "helpers.h"

// ---------
// ANSI CODE
// ---------

/// ANSI Reset Code: Resets the styles to the defaults
const std::string ANSI_RESET = "\x1b[0m";

std::string code(std::vector<Color> c)
{
    std::string code = "\x1b[";
    for (auto color : c)
    {
        code += std::to_string(static_cast<int>(color)) + ";";
    }
    code.pop_back(); // Remove the trailing semicolon
    code += "m";
    return code;
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

std::string ansi_color(const std::string &text, std::vector<Color> colors)
{
    if (is_color_enabled())
    {
        return code(colors) + text + ANSI_RESET;
    }
    else
    {
        return text;
    }
}

std::vector<Color> color_from_string(std::string &str)
{
    std::vector<Color> codes = {};

    std::vector<std::string> codesStr = split_csv_line(str);
    std::string Italic = "italic";
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

    for (auto code : codesStr)
    {
        if (match(code, Italic))
            codes.push_back(Color::Italic);
        else if (match(code, Black))
            codes.push_back(Color::Black);
        else if (match(code, Red))
            codes.push_back(Color::Red);
        else if (match(code, Green))
            codes.push_back(Color::Green);
        else if (match(code, Yellow))
            codes.push_back(Color::Yellow);
        else if (match(code, Blue))
            codes.push_back(Color::Blue);
        else if (match(code, Magenta))
            codes.push_back(Color::Magenta);
        else if (match(code, Cyan))
            codes.push_back(Color::Cyan);
        else if (match(code, White))
            codes.push_back(Color::White);
        else if (match(code, Default))
            codes.push_back(Color::Default);
        else if (match(code, BgBlack))
            codes.push_back(Color::BgBlack);
        else if (match(code, BgRed))
            codes.push_back(Color::BgRed);
        else if (match(code, BgGreen))
            codes.push_back(Color::BgGreen);
        else if (match(code, BgYellow))
            codes.push_back(Color::BgYellow);
        else if (match(code, BgBlue))
            codes.push_back(Color::BgBlue);
        else if (match(code, BgMagenta))
            codes.push_back(Color::BgMagenta);
        else if (match(code, BgCyan))
            codes.push_back(Color::BgCyan);
        else if (match(code, BgWhite))
            codes.push_back(Color::BgWhite);
        else if (match(code, BgDefault))
            codes.push_back(Color::BgDefault);
        else if (match(code, BrightBlack))
            codes.push_back(Color::BrightBlack);
        else if (match(code, BrightRed))
            codes.push_back(Color::BrightRed);
        else if (match(code, BrightGreen))
            codes.push_back(Color::BrightGreen);
        else if (match(code, BrightYellow))
            codes.push_back(Color::BrightYellow);
        else if (match(code, BrightBlue))
            codes.push_back(Color::BrightBlue);
        else if (match(code, BrightMagenta))
            codes.push_back(Color::BrightMagenta);
        else if (match(code, BrightCyan))
            codes.push_back(Color::BrightCyan);
        else if (match(code, BrightWhite))
            codes.push_back(Color::BrightWhite);
        else if (match(code, BrightDefault))
            codes.push_back(Color::BrightDefault);
        else if (match(code, BgBrightBlack))
            codes.push_back(Color::BgBrightBlack);
        else if (match(code, BgBrightRed))
            codes.push_back(Color::BgBrightRed);
        else if (match(code, BgBrightGreen))
            codes.push_back(Color::BgBrightGreen);
        else if (match(code, BgBrightYellow))
            codes.push_back(Color::BgBrightYellow);
        else if (match(code, BgBrightBlue))
            codes.push_back(Color::BgBrightBlue);
        else if (match(code, BgBrightMagenta))
            codes.push_back(Color::BgBrightMagenta);
        else if (match(code, BgBrightCyan))
            codes.push_back(Color::BgBrightCyan);
        else if (match(code, BgBrightWhite))
            codes.push_back(Color::BgBrightWhite);
        else if (match(code, BgBrightDefault))
            codes.push_back(Color::BgBrightDefault);
        else
            throw std::invalid_argument("Unknown color: " + code);
    }

    return codes;
}

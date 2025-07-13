#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <map>

#include "ansi.h"
#include "helpers.h"

// ---------
// ANSI CODE
// ---------

/// ANSI Reset Code: Resets the styles to the defaults
const std::string ANSI_RESET = "\x1b[0m";

std::string code(std::vector<AnsiCode> c)
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

std::string ansi(const std::string &text, std::vector<AnsiCode> colors)
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

const std::map<std::string, AnsiCode> CODE_MAP = {
    {"bold", AnsiCode::Bold},
    {"dim", AnsiCode::Dim},
    {"italic", AnsiCode::Italic},
    {"underline", AnsiCode::Underline},
    {"blink", AnsiCode::Blink},
    {"reverse", AnsiCode::Reverse},
    {"hidden", AnsiCode::Hidden},
    {"strikethrough", AnsiCode::Strikethrough},
    {"black", AnsiCode::Black},
    {"red", AnsiCode::Red},
    {"green", AnsiCode::Green},
    {"yellow", AnsiCode::Yellow},
    {"blue", AnsiCode::Blue},
    {"magenta", AnsiCode::Magenta},
    {"cyan", AnsiCode::Cyan},
    {"white", AnsiCode::White},
    {"default", AnsiCode::Default},
    {"bgblack", AnsiCode::BgBlack},
    {"bgred", AnsiCode::BgRed},
    {"bggreen", AnsiCode::BgGreen},
    {"bgyellow", AnsiCode::BgYellow},
    {"bgblue", AnsiCode::BgBlue},
    {"bgmagenta", AnsiCode::BgMagenta},
    {"bgcyan", AnsiCode::BgCyan},
    {"bgwhite", AnsiCode::BgWhite},
    {"bgdefault", AnsiCode::BgDefault},
    {"brightblack", AnsiCode::BrightBlack},
    {"brightred", AnsiCode::BrightRed},
    {"brightgreen", AnsiCode::BrightGreen},
    {"brightyellow", AnsiCode::BrightYellow},
    {"brightblue", AnsiCode::BrightBlue},
    {"brightmagenta", AnsiCode::BrightMagenta},
    {"brightcyan", AnsiCode::BrightCyan},
    {"brightwhite", AnsiCode::BrightWhite},
    {"bgbrightblack", AnsiCode::BgBrightBlack},
    {"bgbrightred", AnsiCode::BgBrightRed},
    {"bgbrightgreen", AnsiCode::BgBrightGreen},
    {"bgbrightyellow", AnsiCode::BgBrightYellow},
    {"bgbrightblue", AnsiCode::BgBrightBlue},
    {"bgbrightmagenta", AnsiCode::BgBrightMagenta},
    {"bgbrightcyan", AnsiCode::BgBrightCyan},
    {"bgbrightwhite", AnsiCode::BgBrightWhite},
};

std::vector<AnsiCode> ansi_codes_from_string(std::string &str)
{
    std::vector<AnsiCode> codes = {};
    std::vector<std::string> codesStr = split_csv_line(str);

    for (auto code : codesStr)
    {
        auto it = CODE_MAP.find(to_lower(code));
        if (it != CODE_MAP.end())
        {
            codes.push_back(it->second);
        }
        else
        {
            throw std::invalid_argument("Unknown color: " + code);
        }
    }

    return codes;
}

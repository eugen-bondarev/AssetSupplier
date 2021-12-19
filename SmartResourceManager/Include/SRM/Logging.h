#pragma once

#include <stdexcept>
#include "Common.h"
#include <string>
#include <memory>

namespace srm
{
    template<typename... Args>
    String StringFormat(const String& format, Args&&... args)
    {
        int size_s{ std::snprintf(nullptr, 0, format.c_str(), args...) + 1 };
        if (size_s <= 0) 
        { 
            throw std::runtime_error("Error during formatting."); 
        }

        const size_t size{ static_cast<size_t>(size_s) };
        std::unique_ptr<char[]> buf{ std::make_unique<char[]>(size) };

        std::snprintf(buf.get(), size, format.c_str(), args...);

        return String(buf.get(), buf.get() + size - 1);
    }

    SRM_API void ConsoleOut(const String& message);
}

#define SRM_COLOR_ID_BLACK           "30"
#define SRM_COLOR_ID_RED             "31"
#define SRM_COLOR_ID_GREEN           "32"
#define SRM_COLOR_ID_YELLOW          "33"
#define SRM_COLOR_ID_BLUE            "34"
#define SRM_COLOR_ID_MAGENTA         "35"
#define SRM_COLOR_ID_CYAN            "36"
#define SRM_COLOR_ID_WHITE           "37"
#define SRM_COLOR_ID_BRIGHT_BLACK    "90"
#define SRM_COLOR_ID_BRIGHT_RED      "91"
#define SRM_COLOR_ID_BRIGHT_GREEN    "92"
#define SRM_COLOR_ID_BRIGHT_YELLOW   "93"
#define SRM_COLOR_ID_BRIGHT_BLUE     "94"
#define SRM_COLOR_ID_BRIGHT_MAGENTA  "95"
#define SRM_COLOR_ID_BRIGHT_CYAN     "96"
#define SRM_COLOR_ID_BRIGHT_WHITE    "97"

#define SRM_CUSTOM_COLOR_START(x) "\x1B[" x "m"
#define SRM_CUSTOM_COLOR_END "\033[0m"

#define SRM_COLORED_STRING(x, color) SRM_CUSTOM_COLOR_START(color) x SRM_CUSTOM_COLOR_END

#define SRM_CONSOLE_OUT(...)\
    ::srm::ConsoleOut(::srm::StringFormat(__VA_ARGS__))

#define SRM_CONSOLE_INFO(...)\
    ::srm::ConsoleOut("[Asu][" SRM_COLORED_STRING("Info", SRM_COLOR_ID_GREEN) "] " + ::srm::StringFormat(__VA_ARGS__))

#define SRM_CONSOLE_WARN(...)\
    ::srm::ConsoleOut("[Asu][" SRM_COLORED_STRING("Warning", SRM_COLOR_ID_YELLOW) "] " + ::srm::StringFormat(__VA_ARGS__))

#define SRM_CONSOLE_ERR(...)\
    ::srm::ConsoleOut("[Asu][" SRM_COLORED_STRING("Error", SRM_COLOR_ID_RED) "] " + ::srm::StringFormat(__VA_ARGS__))

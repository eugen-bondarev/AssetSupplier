#pragma once

#include <stdexcept>
#include "Common.h"
#include <string>
#include <memory>

namespace Asu
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

    void ConsoleOut(const String& message);
}

#define COLOR_GREEN_START "\x1B[32m"
#define COLOR_RED_START "\x1B[31m"
#define COLOR_YELLOW_START "\x1B[33m"

#define COLOR_END "\033[0m"

#define ASU_CONSOLE_OUT(...) ::Asu::ConsoleOut(::Asu::StringFormat(__VA_ARGS__))
#define ASU_CONSOLE_INFO(...) ::Asu::ConsoleOut("[Asu][" COLOR_GREEN_START "Info" COLOR_END "] " + ::Asu::StringFormat(__VA_ARGS__))
#define ASU_CONSOLE_WARN(...) ::Asu::ConsoleOut("[Asu][" COLOR_YELLOW_START "Warning" COLOR_END "] " + ::Asu::StringFormat(__VA_ARGS__))
#define ASU_CONSOLE_ERR(...) ::Asu::ConsoleOut("[Asu][" COLOR_RED_START "Error" COLOR_END "] " + ::Asu::StringFormat(__VA_ARGS__))

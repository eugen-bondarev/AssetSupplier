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

#define ASU_CONSOLE_OUT(...) ::Asu::ConsoleOut(::Asu::StringFormat(__VA_ARGS__))
#define ASU_CONSOLE_INFO(...) ASU_CONSOLE_OUT("[Asu][Info] " __VA_ARGS__)
#define ASU_CONSOLE_WARN(...) ASU_CONSOLE_OUT("[Asu][Warning] " __VA_ARGS__)
#define ASU_CONSOLE_ERR(...) ASU_CONSOLE_OUT("[Asu][Error] " __VA_ARGS__)
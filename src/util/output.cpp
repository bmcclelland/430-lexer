#include "output.hpp"
#include "config.hpp"
#include "future.hpp"
#include <iostream>

namespace lexer {

Mutex output_mutex;
//TODO use this mutex

void _safe_print(char const* x) {
    if constexpr (config::win32) {
        std::wcout << x;
    }
    else {
        std::cout << x;
        std::cout << std::flush;
    }
}

void _safe_print(wchar_t const* x) {
    if constexpr (config::win32) {
        std::wcout << x;
    }
    else {
        std::cout << x;
        std::cout << std::flush;
    }
}

void _safe_print(std::string const& x) {
    if constexpr (config::win32) {
        std::wcout << to_wide(x);
    }
    else {
        std::cout << x;
        std::cout << std::flush;
    }
}

void _safe_print(std::wstring const& x) {
    if constexpr (config::win32) {
        std::wcout << x;
    }
    else {
        std::cout << from_wide(x);
        std::cout << std::flush;
    }
}

} //lexer

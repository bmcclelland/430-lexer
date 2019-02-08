#pragma once

#include "string.hpp"

namespace lexer {

void _safe_print(String const&);
void _safe_print(WString const&);
void _safe_print(char const*);
void _safe_print(wchar_t const*);

template <typename T>
void _safe_print(T const& t) {
	_safe_print(to_string(t));
}

template <typename... Ts>
void safe_print(Ts&&... ts) {
	(_safe_print(std::forward<Ts>(ts)), ...);
}

} //lexer

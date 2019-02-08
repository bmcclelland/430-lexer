#pragma once

#include <functional>

namespace lexer {

template <typename... Ts>
using Function = std::function<Ts...>;

} //lexer

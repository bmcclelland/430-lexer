#pragma once

#include <stdexcept>

namespace lexer {

template <typename Base, typename Tag>
class Exception : public Base {
    using Base::Base;
};

template <typename Tag>
using LogicError = Exception<std::logic_error, Tag>;

template <typename Tag>
using RuntimeError = Exception<std::runtime_error, Tag>;

} //lexer

#pragma once

#include "string.hpp"
#include "variant.hpp"

namespace lexer {

struct TokenLPar {};
struct TokenRPar {};
struct TokenIf {};
struct TokenElse {};

struct TokenName { 
    String value; 

    TokenName(String const& value_)
        : value(value_)
    {}
};

struct TokenNum { 
    int value; 
   
    TokenNum(int value_) 
        : value(value_) 
    {} 
};

using Token = Variant<
    TokenLPar, 
    TokenRPar, 
    TokenName, 
    TokenNum,
    TokenIf,
    TokenElse
>;

String to_string(Token const&);

} // namespace lexer

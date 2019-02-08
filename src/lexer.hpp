#pragma once

#include "token.hpp"
#include "lexercore.hpp"
#include "variant.hpp"
#include "result.hpp"

namespace lexer {

struct LexerError {
    size_t where;
    String what;
};

using LexerResult = Result<Vector<Token>, LexerError>;

class Lexer : private LexerCore {
    public:
        Lexer(String const&);
        LexerResult run();
};

} // namespace lexer

#include "lexer.hpp"
#include "map.hpp"

namespace lexer {
   
static
Optional<Token> try_reserved(String const& key) {
    static const Map<String, Token> keywords {
        { "if", TokenIf() },
        { "else", TokenElse() },
    };

    return lookup(keywords, key);
}

Lexer::Lexer(String const& input) 
    : LexerCore(input)
{}

LexerResult Lexer::run() {
    Vector<Token> tokens;

    skip_ws();

    auto t = [&](auto&& f) {
        PosReverter p = save_pos();

        if (Optional<Token> result = f()) {
            tokens.push_back(result.value());
            skip_ws();
            p.disable();
            return true;
        }
        
        return false;
    };

    auto name_or_keyword = [&]() -> Optional<Token> {
        String value;
        
        if (!isalpha(cur())) {
            return failure;
        }

        do {
            value.push_back(cur());
            next();
        } 
        while (isalpha(cur()) || isdigit(cur()));

        if (Optional<Token> keyword = try_reserved(value)) {
            return keyword;
        }
    
        return TokenName(value);
    };
    
    auto num = [&]() -> Optional<Token> {
        String s;

        if (!isdigit(cur())) {
            return failure;
        }

        do {
            s.push_back(cur());
            next();
        } 
        while (isdigit(cur()));

        try {
            return TokenNum(stoi(s));
        }
        catch (std::exception const&) {
            return failure;
        }
    };

    auto lpar = [&]() -> Optional<Token> {
        if (cur() != '(') {
            return failure;
        }

        next();
        return TokenLPar{};
    };
    
    auto rpar = [&]() -> Optional<Token> {
        if (cur() != ')') {
            return failure;
        }

        next();
        return TokenRPar{};
    };

    while (!eof()) {
        if (t(name_or_keyword)
         || t(num)
         || t(lpar)
         || t(rpar)
         ) {
            // Ok.
        }
        else {
            return LexerError{pos(), "something"};
        }
    }

    return tokens;
}

} // namespace lexer

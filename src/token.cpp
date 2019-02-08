#include "token.hpp"

namespace lexer {

String to_string(Token const& t) {
    return t.match(
        [](TokenLPar) { return "(LPar)"s; },
        [](TokenRPar) { return "(RPar)"s; },
        [](TokenIf)   { return "(If)"s; },
        [](TokenElse) { return "(Else)"s; },
        [](TokenName const& name) {
            return "(Name " + name.value + ")";
        },
        [](TokenNum const& num) {
            return "(Num " + to_string(num.value) + ")";
        });
}

} // namespace lexer

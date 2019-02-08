#include "token.hpp"
#include "color.hpp"

namespace lexer {

static String const col_op   = to_string(Color::yellow);
static String const col_name = to_string(Color::cyan);
static String const col_kw   = to_string(Color::yellow);
static String const col_num  = to_string(Color::red);
static String const col_off  = to_string(Color::off);

String to_string(Token const& t) {
    return t.match(
        [](TokenLPar) { 
            return col_op + "(LPar)" + col_off; 
        },
        [](TokenRPar) { 
            return col_op + "(RPar)" + col_off; 
        },
        [](TokenIf)   { 
            return col_kw + "(If)" + col_off; 
        },
        [](TokenElse) { 
            return col_kw + "(Else)" + col_off; 
        },
        [](TokenName const& name) {
            return col_name + "(Name " + name.value + ")" + col_off;
        },
        [](TokenNum const& num) {
            return col_num + "(Num " + to_string(num.value) + ")" + col_off;
        });
}

} // namespace lexer

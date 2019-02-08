#include "string.hpp"
#include <boost/locale.hpp>

namespace lexer {

String to_string(bool b) {
    if (b) {
        return "true";
    }
    else {
        return "false";
    }
}

} // namespace lexer

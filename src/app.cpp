#include "app.hpp"
#include "lexer.hpp"

namespace lexer {

using namespace std;

int app(String const& input) {
    cout << "input: " << input << "\n";

    if (LexerResult result = lex(input)) {
        for (Token const& t : result.value()) {
            cout << to_fancy_string(t);
        }
        
        cout << "\n";
        return 0;
    }
    else {
        LexerError e = result.error();
        cout << "Error: " << e.what << " at " << e.where << "\n";
        return 1;
    }
}

} // namespace lexer

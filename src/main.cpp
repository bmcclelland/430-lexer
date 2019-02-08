#include "lexer.hpp"

int main() {
    using namespace lexer;
    using namespace std;
    
    String input = " if (var) x 4 5 else 45(num4 4num)";
    cout << "input: " << input << "\n";

    Lexer lexer(input);

    if (LexerResult result = lexer.run()) {
        for (Token const& t : result.value()) {
            cout << to_string(t);
        }
        
        cout << "\n";
    }
    else {
        LexerError e = result.error();
        cout << "Error: " << e.what << " at " << e.where << "\n";
    }
}

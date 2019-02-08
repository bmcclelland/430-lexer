#include "color.hpp"

namespace lexer {
    
String to_string(Color c) {
	return "\033[" 
		+ to_string(static_cast<int>(c)) 
		+ "m";
}

} //lexer


#pragma once

#include <string>

namespace lexer {

using String = std::string;
using FilePath = String;
using std::to_string;
using namespace std::literals::string_literals;

String to_string(bool);

} // namespace lexer

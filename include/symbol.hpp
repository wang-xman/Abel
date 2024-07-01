#ifndef ABEL_SYMBOL_HPP
#define ABEL_SYMBOL_HPP

#include <fstream>
#include <algorithm>
#include "error.hpp"
#include "typefy.hpp"

namespace abel {

namespace symbol {

// Standalone symbols
extern const std::string SPACE;
extern const std::string SHARP;
extern const std::string COLON;
extern const std::string COMMA;
extern const std::string ENDL;  // End of line (not in active use)
extern const std::string BACK_SLASH;
extern const std::string FORWARD_SLASH;
extern const std::string SINGLE_QUOTE;
extern const std::string DOUBLE_QUOTE;
extern const std::string BACK_TICK;
extern const std::string GRAVE_ACCENT;

// Algebraic symbols
extern const std::string MINUS;
extern const std::string PLUS;
extern const std::string DECIMAL_POINT;
extern const std::string HAT;

extern const std::string ADD;
extern const std::string SUBTRACT;
extern const std::string MULTIPLY;
extern const std::string DIVIDE;

// Paired symbols

// Braces (curly brackets {} )
extern const std::string L_BRACE;
extern const std::string R_BRACE;
// Brackets (square brackets [] )
extern const std::string L_BRACKET;
extern const std::string R_BRACKET;
// Parentheses (round brackets () )
extern const std::string L_PARENTHESIS;
extern const std::string R_PARENTHESIS;
// Chevrons (angle brackets <> ) 
extern const std::string L_CHEVRON;
extern const std::string R_CHEVRON;

// Container symbols

extern const std::vector<std::string> CONTAINER_TYPES;
extern const std::vector<std::string> ITERABLE_CONTAINERS;
/// Opening symbol for each container defined in CONTAINER_TYPES
extern const std::vector<std::string> CONTAINER_OPENING_SYMBOLS;
/// Token type string for container opening token
extern const std::vector<std::string> CONTAINER_OPENING_TOKEN_TYPES;
/// Closing symbol for each container defined in CONTAINER_TYPES
extern const std::vector<std::string> CONTAINER_CLOSING_SYMBOLS;
/// Token type string for container closing token
extern const std::vector<std::string> CONTAINER_CLOSING_TOKEN_TYPES;

} // end symbol

}
#endif
#include "symbol.hpp"

namespace abel {

namespace symbol {

// Standalone symbols

const std::string SPACE { " " };  // Single space
const std::string SHARP { "#" };  // Single-line comment
const std::string COLON { ":" };  // Key-value separator
const std::string COMMA { "," };  // Same level object separator
const std::string ENDL { "\n" };  // End of line (not in active use)
const std::string BACK_SLASH { "\\" };  // Back slash, need escape
const std::string FORWARD_SLASH { "/" };  // Forward slash, needs no escape
const std::string SINGLE_QUOTE { "\'" };  // Single quote
const std::string DOUBLE_QUOTE { "\"" };  // Double quote
const std::string BACK_TICK { "\u0060" }; // Back tick `
const std::string GRAVE_ACCENT { "\u0060" }; // Grave accent `

// Algebraic symbols
const std::string MINUS { "-" };  // Minus sign
const std::string PLUS { "+" };  // Plus sign
const std::string DECIMAL_POINT { "." };  // Decimal point
const std::string HAT { "^" };  // Hat symbol, as exponentiation
const std::string DOUBLE_MULTIPLY { "**" }; // Double multiply, as exponentiation

const std::string ADD { "+" };  // Add +
const std::string SUBTRACT { "-" };  // Subtract -
const std::string MULTIPLY { "*" };  // Multiply *
const std::string DIVIDE { "/" };  // Divide /

// Paried symbols
/// Braces (curly brackets)
const std::string L_BRACE { "{" };
const std::string R_BRACE { "}" };
/// Brackets (square brackets)
const std::string L_BRACKET { "[" };
const std::string R_BRACKET { "]" };
/// Parentheses (round brackets)
const std::string L_PARENTHESIS { "(" };
const std::string R_PARENTHESIS { ")" };
/// Chevrons (angle brackets) 
const std::string L_CHEVRON { "<" };
const std::string R_CHEVRON { ">" };

// Container symbols
const std::vector<std::string> CONTAINER_TYPES { "Dict", "List", "Tuple" };
const std::vector<std::string> ITERABLE_CONTAINERS { "List", "Tuple" };
const std::vector<std::string> CONTAINER_OPENING_SYMBOLS {
    L_BRACE, L_BRACKET, L_PARENTHESIS
};
const std::vector<std::string> CONTAINER_CLOSING_SYMBOLS {
    R_BRACE, R_BRACKET, R_PARENTHESIS
};
const std::vector<std::string> CONTAINER_OPENING_TOKEN_TYPES { // type strings
    "Dict_Opening", "List_Opening", "Tuple_Opening"
};
const std::vector<std::string> CONTAINER_CLOSING_TOKEN_TYPES { // type strings
    "Dict_Closing", "List_Closing", "Tuple_Closing"
};

} // end symbol

}
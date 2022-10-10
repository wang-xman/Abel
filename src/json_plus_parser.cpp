#include "json_plus_parser.hpp"

namespace abel {

JsonTerminalType JsonPlusParser::get_terminal_type(
        const std::string& literal, const LiteralScheme& scheme)
/*
    Determine JSON terminal data type for JSON+ parser.
    JSON+ parser accepts more data types than standard JSON
    parser.

    CAUTION! Type integer must be checked before double, double
    must be before complex. So, subset first.
*/
{
    JsonTerminalType terminal_type;
    if (scheme == LiteralScheme::Liberal) {
        if ( converter::is_null(literal) ) {
            terminal_type = JsonTerminalType::Null;
        } else if ( converter::is_bool(literal) ) {
            terminal_type = JsonTerminalType::Bool;
        } else if ( converter::is_integer(literal) ) {
            terminal_type = JsonTerminalType::Integer;
        } else if ( converter::is_double(literal) ) {
            terminal_type = JsonTerminalType::Double;
        } else if ( converter::is_complex(literal) ) {
            terminal_type = JsonTerminalType::Complex;
        } else if ( converter::is_binary(literal) ) {
            terminal_type = JsonTerminalType::Binary;
        } else if ( converter::is_bitstring(literal) ) {
            terminal_type = JsonTerminalType::Bitstring;
        } else {
            std::string msg = "Type of unquoted string '" + literal
                              + "' cannot be recognised.";
            error::SyntaxError err = error::SyntaxError(msg);
            err.set_line(current_line);
            throw err;
        }
    } else if (scheme == LiteralScheme::None) {
        std::string msg = "Collection scheme of '" + literal + "' is not set.";
        error::SyntaxError err = error::SyntaxError(msg);
        err.set_line(current_line);
        throw err;
    } else { // delimited string is always considered as text
        terminal_type = JsonTerminalType::Text;
    }
    return terminal_type;
}

JsonPlusParser::JsonPlusParser() {}

JsonPlusParser::~JsonPlusParser() {}

}
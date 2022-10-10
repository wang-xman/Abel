#include "util.hpp"

namespace abel {

namespace util {

void remove_space(std::string& str)
{
    str.erase( std::remove(str.begin(), str.end(), ' '), str.end() );
}

bool has_letter(std::string& src_str)
{
    int strlen = src_str.length();
    int letter_counter = 0;
    for (int i = 0; i < strlen; i++) {
        if ( std::isalpha(src_str[i]) ) {
            letter_counter += 1;
        }
    }
    return ! (letter_counter == 0);
}

bool begins_with_letter(std::string& src_str)
{
    return std::isalpha(src_str[0]);
}

bool begins_with_sign(std::string& src_str)
{
    return ( (src_str[0] == '-') || (src_str[0] == '+') );
}

bool is_algebraic_operator(const std::string& src_str)
{
    return ( src_str == symbol::ADD || src_str == symbol::SUBTRACT
             || src_str == symbol::MULTIPLY || src_str == symbol::DIVIDE
             || src_str == symbol::HAT || src_str == "**");
}

bool is_algebraic_operator(const char src_char)
{
    return ( src_char == '+' || src_char == '-'
             || src_char == '*' || src_char == '/' || src_char == '^');
}


bool is_valid_variable(const std::string& src_str)
{
    int ret = true;
    int strlen = src_str.length();
    int non_sign_starting_index = 0;

    if (src_str[0] == '+' || src_str[0] == '-') {
    /// Variable carries a sign
        non_sign_starting_index = 1;
    } else {
    /// Variable has no sign
        non_sign_starting_index = 0;
    }
    if ( !( src_str[non_sign_starting_index] == '_'
            || std::isalpha(src_str[non_sign_starting_index]) ) ) {
    /// First char must be either dash or letter
        ret = false;
    }
    /// Chars after first non-sign letter must be letter, number 
    for (int i = non_sign_starting_index + 1; i < strlen; i++) {
        if ( !( src_str[i] == '_' || src_str[i] == '.'
                || std::isalpha(src_str[i]) || std::isdigit(src_str[i]) ) ) // a bug fixed
        {
        /// After the first char, only letter, number and dash is allowed
            ret = false;
        }
    }
    return ret;
}

int index_of_matching_closing_symbol(const std::string& src_str,
                                     const int index_opening)
/*
    In the given string, finds the index of matching closing parenthesis.
    FIXME In delimiter object, there is a better and more general
    solution. TODO Should this be part of the delimiter object?
*/
{
    int match_counter = 1;
    int index_closing_symbol = 0;
    int strlen = src_str.length();

    for (int i = index_opening + 1; i < strlen; i++) {
        if (src_str[i] == '(') {
            match_counter += 1;
        } else if (src_str[i] == ')') {
            match_counter -= 1;
        }
        if (match_counter == 0) {
            index_closing_symbol = i;
            break;
        }
    }
    return index_closing_symbol;
}

bool is_opening_symbol(const std::string& sym)
{
    return std::find(
        symbol::CONTAINER_OPENING_SYMBOLS.begin(),
        symbol::CONTAINER_OPENING_SYMBOLS.end(), sym
    ) != symbol::CONTAINER_OPENING_SYMBOLS.end();
}

bool is_closing_symbol(const std::string& sym)
{
    return std::find(
        symbol::CONTAINER_CLOSING_SYMBOLS.begin(),
        symbol::CONTAINER_CLOSING_SYMBOLS.end(), sym
    ) != symbol::CONTAINER_CLOSING_SYMBOLS.end();
}

bool is_iterable_container(const std::string& type_str)
{
    return std::find(
        symbol::ITERABLE_CONTAINERS.begin(),
        symbol::ITERABLE_CONTAINERS.end(), type_str
    ) != symbol::ITERABLE_CONTAINERS.end();
}

std::string get_closing_symbol_by_opening(const std::string& opening_sym)
{
    std::string closing_symbol;
    int index;
    if ( is_opening_symbol(opening_sym) ) {
        index = std::distance(
            symbol::CONTAINER_OPENING_SYMBOLS.begin(),
            std::find(symbol::CONTAINER_OPENING_SYMBOLS.begin(),
                      symbol::CONTAINER_OPENING_SYMBOLS.end(), opening_sym));
        closing_symbol = symbol::CONTAINER_CLOSING_SYMBOLS[index];
    } else {
        throw error::UnrecognizedSymbol("Closing symbol can only be "
                                             "requested by an opening symbol.");
    }
    return closing_symbol;
}

} // end util

}

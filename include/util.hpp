#ifndef ABEL_UTIL_HPP
#define ABEL_UTIL_HPP

#include "symbol.hpp"

namespace abel {

namespace util {

void remove_space(std::string& /* str */);

bool has_letter(std::string&);

bool begins_with_letter(std::string&);

bool begins_with_sign(std::string&);

bool is_algebraic_operator(const std::string&);

bool is_algebraic_operator(const char);

bool is_valid_variable(const std::string&);

// TODO Should this be part of the delimiter object?
int index_of_matching_closing_symbol(const std::string& /* target string */,
                                     const int /* start index */);

bool is_opening_symbol(const std::string&);

bool is_closing_symbol(const std::string&);

bool is_iterable_container(const std::string&);

std::string get_closing_symbol_by_opening(const std::string&);

} // end util

}
#endif
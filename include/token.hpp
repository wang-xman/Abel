#ifndef ABEL_TOKEN_HPP
#define ABEL_TOKEN_HPP

#include "symbol.hpp"

namespace abel {

template <typename T>
struct Token {
    std::string literal = "";
    T type;
};

}
#endif
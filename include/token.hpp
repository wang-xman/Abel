#ifndef _ABEL_TOKEN_HPP_
#define _ABEL_TOKEN_HPP_

#include "symbol.hpp"

namespace abel {

template <typename T>
struct Token {
    std::string literal = "";
    T type;
};

}
#endif
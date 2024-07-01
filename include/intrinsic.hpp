#ifndef ABEL_INTRINSIC_HPP
#define ABEL_INTRINSIC_HPP

#include "null.hpp"
#include "bool.hpp"
#include "text.hpp"
#include "integer.hpp"
#include "double.hpp"
#include "complex.hpp"
#include "binary.hpp"
#include "bitstring.hpp"

namespace abel {

extern std::vector<std::string> NUMERIC_TYPES;

bool is_numeric_type(const object&);

bool is_numeric_type(const std::shared_ptr<object>&);

}
#endif
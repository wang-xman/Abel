#include "null.hpp"

namespace abel {

Null::Null() {}

Null::~Null() {}

std::string Null::type_name() const { return type_name_string; }

}
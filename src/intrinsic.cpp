#include "intrinsic.hpp"

namespace abel {

std::vector<std::string> NUMERIC_TYPES { "Integer", "Double", "Complex" };

bool is_numeric_type(const object& ref) {
    return std::find(NUMERIC_TYPES.begin(), NUMERIC_TYPES.end(), ref.type_name())
            != NUMERIC_TYPES.end();
}

bool is_numeric_type(const std::shared_ptr<object>& sptr) {
    return std::find(NUMERIC_TYPES.begin(), NUMERIC_TYPES.end(), sptr->type_name())
            != NUMERIC_TYPES.end();
}

}
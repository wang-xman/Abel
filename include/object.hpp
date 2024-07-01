#ifndef ABEL_OBJECT_HPP
#define ABEL_OBJECT_HPP

#include "error.hpp"
#include "typefy.hpp"

namespace abel {

class object {
private:
    std::string type_name_string = "object";

public:
    object() {}

    virtual ~object() {}

    virtual std::string type_name() const;
};

}
#endif
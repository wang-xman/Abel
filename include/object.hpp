#ifndef _ABEL_OBJECT_HPP_
#define _ABEL_OBJECT_HPP_

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
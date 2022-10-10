#ifndef _ABEL_NULL_HPP_
#define _ABEL_NULL_HPP_

#include "object.hpp"

namespace abel {

class Null : public object {
private:
    std::string type_name_string = "Null";

protected:
    int internal = 0;

public:
    Null();

    ~Null();

    std::string type_name() const override;
};

}
#endif
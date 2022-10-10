/* TODO 1. Conversion to integer */
#ifndef _ABEL_BINARY_HPP_
#define _ABEL_BINARY_HPP_

#include "text.hpp"

namespace abel {

namespace util {

bool is_valid_binary_string(std::string&);

} // end abel::util

class Binary : public object {
private:
    std::string type_name_string = "Binary";

protected:
    std::string internal;

public:
    Binary();
    explicit Binary(std::string&);
    explicit Binary(std::string&&);
    explicit Binary(const std::shared_ptr<object>);

    ~Binary();
    
    Binary& operator=(const std::string&);
    Binary& operator=(const std::shared_ptr<Text>);
    Binary& operator=(const std::shared_ptr<object>);

    // Conversion
    operator std::string();
    operator int(); // TODO Convert a binary into integer.

    std::string type_name() const override;
    virtual std::string value() const;
};

// NOTE! Not independently unittested. But test in JSON+ loader.
bool operator==(const Binary&, const Binary&); // Binary == Binary
bool operator!=(const Binary&, const Binary&); // Binary != Binary

}
#endif

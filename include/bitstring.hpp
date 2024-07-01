#ifndef ABEL_BITSTRING_HPP
#define ABEL_BITSTRING_HPP

#include "text.hpp"

namespace abel {

namespace util {

bool is_valid_bitstring(std::string& src_str);

} // end abel::util

class Bitstring : public Text {
private:
    std::string type_name_string = "Bitstring";

public:
    Bitstring();
    explicit Bitstring(std::string&);
    explicit Bitstring(std::string&&);
    //TODO explicit Bitstring(const std::shared_ptr<Text>);
    explicit Bitstring(const std::shared_ptr<object>);

    ~Bitstring();
    
    // Copy assignment operator. Don't override the default.
    Bitstring& operator=(const std::string&);
    Bitstring& operator=(const std::shared_ptr<Text>);
    Bitstring& operator=(const std::shared_ptr<object>);

    // Conversion
    operator std::string();
    // TODO Convert a bitstring into integer or double
    operator int();
    operator double();

    std::string type_name() const override;
    // TODO Perhaps meaningless to have this value method. Should be more
    // concrete.
    virtual std::string value() const override;
};

// NOTE! Not independently unittested. But test in JSON+ loader.
bool operator==(const Bitstring&, const Bitstring&); // Bitstring == Bitstring
bool operator!=(const Bitstring&, const Bitstring&); // Bitstring == Bitstring

}
#endif
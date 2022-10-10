#include "binary.hpp"

namespace abel {

namespace util {

bool is_valid_binary_string(std::string& src_str)
{
    int ret = true;
    int strlen = src_str.length();
    if (strlen <= 2) {
    // if only two characters, no.
        ret = false;
    } else if ( !(src_str[0] == '0' && src_str[1] == 'b') ) {
    // if not begins with "0b", no
        ret = false;
    } else {
    // rest must be either '0' or '1'.
        for (int i = 2; i < strlen; i++) {
            if ( !(src_str[i] == '0' || src_str[i] == '1') ) {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

} // end abel::util

Binary::Binary() {}

Binary::Binary(std::string& str)
{
    try {
        if ( !util::is_valid_binary_string(str) ) {
            std::string msg = str + " is not a valid Abel binary string.";
            throw error::SyntaxError(msg);
        }
    } catch (error::SyntaxError& err) { err.make_show(); }
    internal = str;
}

Binary::Binary(std::string&& rstr)
{
    try {
        if ( !util::is_valid_binary_string(rstr) ) {
            std::string msg = rstr + " is not a valid Abel binary string.";
            throw error::SyntaxError(msg);
        }
    } catch (error::SyntaxError& err) { err.make_show(); }
    internal = rstr;
}

// TODO Need a constructor to convert String to Binary.
//Binary::Binary(const std::shared_ptr<String> sptr) : internal(sptr->value()) {}

Binary::Binary(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Binary") {
            std::string msg = "Cannot copy-contruct a non-Binary type shared"
                              "pointer of object to a Binary object.";
            throw error::IncompatibleType(msg);
        }
    } catch(error::IncompatibleType& err) { err.make_show(); }
    internal = std::dynamic_pointer_cast<Binary>(sptr)->value();
}

Binary::~Binary() {}

Binary& Binary::operator=(const std::string& c_string_ref)
{
    std::string src_str = c_string_ref;
    try {
        if ( !util::is_valid_binary_string(src_str) ) {
            std::string msg = src_str + " is not a valid Abel binary string.";
            throw error::SyntaxError(msg);
        }
    } catch (error::SyntaxError& err) { err.make_show(); }
    internal = c_string_ref;
    return *this;
}

Binary& Binary::operator=(const std::shared_ptr<Text> sptr)
{
    std::string value = sptr->value();
    try {
        if ( !util::is_valid_binary_string(value) ) {
            std::string msg = value + " is not a valid Abel binary string.";
            throw error::SyntaxError(msg);
        }
    } catch (error::SyntaxError& err) { err.make_show(); }
    internal = value;
    return *this;
}

Binary& Binary::operator=(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Binary") {
            std::string msg = "Cannot assign a non-Binary type shared"
                              "pointer of object to a Binary object.";
            throw error::IncompatibleType(msg);
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    internal = std::dynamic_pointer_cast<Binary>(sptr)->value();
    return *this;
}

Binary::operator std::string() { return internal; }

std::string Binary::type_name() const { return type_name_string; }
std::string Binary::value() const { return internal; }

bool operator==(const Binary& l_bin_ref, const Binary& r_bin_ref)
{
    return l_bin_ref.value() == r_bin_ref.value();
};

bool operator!=(const Binary& l_bin_ref, const Binary& r_bin_ref)
{
    return !(l_bin_ref == r_bin_ref);
};

}
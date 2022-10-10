#include "bitstring.hpp"

namespace abel {

namespace util {

bool is_valid_bitstring(std::string& src_str)
{
    int ret = true;
    int strlen = src_str.length();
    int dot_counter = 0;
    if (strlen < 3) {
    // cannot be empty
        ret = false;
    } else if ( !(src_str[0] == '_' && src_str[1] == 'b') ) {
    // must begin with "_b" prefix
        ret = false;
    } else if ( src_str == "_b.") {
    // cannot be "_b.", makes no sense.
        ret = false;
    } else {
    // rest must be either '0', '1', or dot
        for (int i = 2; i < strlen; i++) {
            if ( !(src_str[i] == '0' || src_str[i] == '1'
                   || src_str[i] == '.') ) {
                ret = false;
                break;
            } else if (src_str[i] == '.') {
                dot_counter += 1;
                if (dot_counter > 1) {
                // cannot have more than 1 dot.
                    ret = false;
                    break;
                } else {
                    if (strlen == 1) {
                    // bitstring cannot be just a dot
                        ret = false;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}
} // end abel::util

Bitstring::Bitstring() {}

Bitstring::Bitstring(std::string& str)
{
    try {
        if ( !util::is_valid_bitstring(str) ) {
            throw error::SyntaxError(str + " is not a valid Abel bitstring.");
        }
    } catch(error::SyntaxError& err) { err.make_show(); }
    internal = str;
}

Bitstring::Bitstring(std::string&& rstr)
{
    try {
        if ( !util::is_valid_bitstring(rstr) ) {
            throw error::SyntaxError(rstr + " is not a valid Abel bitstring.");
        }
    } catch(error::SyntaxError& err) { err.make_show(); }
    internal = rstr;
}

// TODO Need a constructor to convert Text to Bitstring.
//Bitstring::Bitstring(const std::shared_ptr<Text> sptr) : internal(sptr->value()) {}

Bitstring::Bitstring(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Bitstring") {
            std::string msg = "Cannot copy-contruct a non-Bitstring type shared"
                              "pointer of object to a Bitstring object.";
            throw error::IncompatibleType(msg);
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    internal = std::dynamic_pointer_cast<Bitstring>(sptr)->value();
}

Bitstring::~Bitstring() {}

/// Copy assigment operators
Bitstring& Bitstring::operator=(const std::string& c_string_ref)
{
    std::string src_str = c_string_ref;
    try {
        if ( !util::is_valid_bitstring(src_str) ) {
            throw error::SyntaxError(src_str + "  is not a valid Abel bitstring.");
        }
    } catch (error::SyntaxError& err) { err.make_show(); }
    internal = c_string_ref;
    return *this;
}

// From shared pointer Text type
Bitstring& Bitstring::operator=(const std::shared_ptr<Text> sptr)
{
    std::string src_str = sptr->value();
    try {
        if ( !util::is_valid_bitstring(src_str) ) {
            throw error::SyntaxError(src_str + "is not a valid Abel bitstring.");
        }
    } catch (error::SyntaxError& err) { err.make_show(); }
    internal = sptr->value();
    return *this;
}

// From shared pointer object type
Bitstring& Bitstring::operator=(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Bitstring") {
            std::string msg = "Cannot assign a non-Bitstring type shared"
                              "pointer of object to a Bitstring object.";
            throw error::IncompatibleType(msg);
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    internal = std::dynamic_pointer_cast<Bitstring>(sptr)->value();
    return *this;
}

// Conversion
Bitstring::operator std::string() { return internal; }
// TODO Convert into integer

// Public methods
std::string Bitstring::type_name() const { return type_name_string; }
// TODO Perhaps meaningless to have this value method.
// Should be more concrete.
std::string Bitstring::value() const { return internal; }

bool operator==(const Bitstring& l_bin_ref, const Bitstring& r_bin_ref)
{
    return l_bin_ref.value() == r_bin_ref.value();
};

bool operator!=(const Bitstring& l_bin_ref, const Bitstring& r_bin_ref)
{
    return !(l_bin_ref == r_bin_ref);
};

}
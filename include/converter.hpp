#ifndef _ABEL_CONVERTER_HPP_
#define _ABEL_CONVERTER_HPP_

#include "intrinsic.hpp"
#include "util.hpp"

namespace abel {

/* Data type indentifier (DTI) structure */
struct DataTypeIdentifier {
    bool is_identified = false;
    std::string type_string = "";
    std::string data_string = "";
    std::string real_string = "";
    std::string imag_string = "";
};

namespace converter {

    // Null
    bool is_null(const std::string&);
    Null as_null(const std::string&);

    // Bool
    bool is_bool(const std::string&);
    Bool as_bool(const std::string&);

    // Integer
    bool is_integer(const std::string&);
    bool is_unsigned_integer(const std::string&);
    bool is_positive_integer(const std::string&);
    bool is_negative_integer(const std::string&);
    Integer as_integer(const std::string&);

    // Double
    DataTypeIdentifier identify_double(const std::string&);
    bool is_double(const std::string&);
    bool is_unsigned_double(const std::string&);
    bool is_positive_double(const std::string&);
    bool is_negative_double(const std::string&);
    Double as_double(const std::string&);

    // Complex
    DataTypeIdentifier identify_complex(const std::string&);
    bool is_complex(const std::string&);
    Complex as_complex(const std::string&);

    // Binary
    bool is_binary(const std::string&);
    Binary as_binary(const std::string&);

    // Bistring
    bool is_bitstring(const std::string&);
    Bitstring as_bitstring(const std::string&);

} // converter

}
#endif
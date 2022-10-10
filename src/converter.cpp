#include "converter.hpp"

namespace abel {

namespace converter {

bool is_null(const std::string& src_str)
/*
    FIXME! Using NULL causes segmentation fault.
*/
{
    return (src_str == "null");
}

Null as_null(const std::string& src_str)
{
    Null ret;
    if ( !is_null(src_str) ) {
        throw error::DataTypeConversionError(
                "Failed to identify and convert a Null type.");
    }
    return ret;
}

bool is_bool(const std::string& src_str)
{
    return (src_str == "true" || src_str == "false");
}

Bool as_bool(const std::string& src_str)
{
    Bool ret;
    if ( is_bool(src_str) ) {
        if (src_str == "true") {
            ret = true;
        } else {
            ret = false;
        }
    } else {
        throw error::DataTypeConversionError(
                "Failed to identify and convert a Bool type.");
    }
    return ret;
}

bool is_integer(const std::string& src_str)
{
    bool ret = false;
    int non_digit_counter = 0;
    int strlen = src_str.length();

    if (src_str[0] == '-' || src_str[0] == '+') {
        for (int index = 1; index < strlen; index++) {
            if ( !std::isdigit(src_str[index]) ) {
                non_digit_counter += 1;
            }
        }
        if (non_digit_counter == 0) {
            ret = true;
        }
    } else if (src_str.length() == 0) { // empty string is not integer
        ret = false;
    } else {
        for (int index = 0; index < strlen; index++) {
            if ( !std::isdigit(src_str[index]) ) {
                non_digit_counter += 1;
            }
        }
        if (non_digit_counter == 0) {
            ret = true;
        }
    }
    return ret;
}

bool is_unsigned_integer(const std::string& src_str)
/*
    Unsigned integer. Without plus or minus sign
*/
{
    return is_integer(src_str) && std::isdigit(src_str[0]);
}

bool is_positive_integer(const std::string& src_str)
/*
    Positive integer. With plus sign.
*/
{
    return is_integer(src_str) && (src_str[0] == '+');
}

bool is_negative_integer(const std::string& src_str)
/*
    Negative integer. With minus sign.
*/
{
    return is_integer(src_str) && (src_str[0] == '-');
}

Integer as_integer(const std::string& src_str)
{
    Integer ret;
    if ( is_integer(src_str) ) {
        ret = std::stoi(src_str);
    } else {
        throw error::DataTypeConversionError(
                "Failed to identify and convert an Integer type.");
    }
    return ret;
}

// Double identifier
DataTypeIdentifier identify_double(const std::string& src_str)
{
    DataTypeIdentifier dti;
    bool ret = true;
    int strlen = src_str.length(); // string length
    int sign_counter = 0;
    int decimal_point_counter = 0;
    int decimal_point_position = 0;
    int exp_counter = 0;
    int exp_position = 0;

    // iterates through source string
    for (int index = 0; index < strlen; index++) {
        if ( src_str[index] == '-' || src_str[index] == '+' ) {
            sign_counter += 1;
            // Sign cannot be the last symbol, also excludes the case of
            // '+' or '-', i.e only a sign.
            if (index == strlen - 1) {
                ret = false;
                break;
            } else if (index == 0) { // sign is first symbol
                // if has more two characters,
                // then the second one cannot be 'e', 'E', '-', or '+'.
                if (strlen >= 2 && (
                        src_str[index + 1] == 'e'
                        || src_str[index + 1] == 'E' 
                        || src_str[index + 1] == '-'
                        || src_str[index + 1] == '+') )
                {
                    ret = false;
                    break;
                }
                // Excolude '-.e' or '+.e' type of expression
                if ( strlen >= 3 && src_str[index + 1] == '.'
                        && (src_str[index + 2] == 'e'
                            || src_str[index + 2] == 'E' ) )
                {
                    ret = false;
                    break;
                }

            } else {
                // Symbol 'e' or 'E' cannot follow a sign immediately.
                if (src_str[index + 1] == 'e' || src_str[index + 1] == 'E') {
                    ret = false;
                    break;
                }
            }
            // If sign is not the first symbol, only 'e' or 'E' can be on its left.
            if (index != 0) {
                if ( !(src_str[index - 1] == 'e'
                        || src_str[index - 1] == 'E') )
                {
                    ret = false;
                    break;
                }
            }
            // second sign
            if (sign_counter == 2) {
                // second sign must be on the right of exponent symbol
                if ( !(src_str[index - 1] == 'e'
                        || src_str[index - 1] == 'E') )
                {
                    ret = false;
                    break;
                }
                // on the right of second sign, must be a digit.
                if (index == strlen - 1) { // cannot be the last symbol
                    ret = false;
                    break;
                } else { 
                    if ( !std::isdigit(src_str[index + 1]) ) {
                        ret = false;
                        break;
                    }
                }
            }
            // More than two signs, NO!
            if (sign_counter > 2) {
                ret = false;
                break;
            }
        } else if (src_str[index] == '.') {
            decimal_point_counter += 1;
            // Just a decimal point '.', NO!
            if (strlen == 1) {
                ret = false;
                break;
            }
            // Only has at most 1 decimal point
            if (decimal_point_counter > 1) {
                ret = false;
                break;
            } else {
                decimal_point_position = index;
            }
            // If symbol 'e' appears before decimal point, NO!
            if (exp_counter == 1) {
                ret = false;
                break;
            }
            // decimal not the first symbol
            if (index != 0) {
                // If decimal not first symbol, must be either a sign
                // or a digit on its left.
                if ( !(src_str[index - 1] == '+'
                        || src_str[index - 1] == '-'
                        || std::isdigit(src_str[index - 1])) )
                {
                    ret = false;
                    break;
                }
            }
        } else if ( src_str[index] == 'e' || src_str[index] == 'E') {
            exp_counter += 1;
            if (exp_counter > 1) {
                ret = false;
                break;
            } else {
                exp_position = index;
            }
            // If already has a decimal point, it must be before symbol 'e'
            if (decimal_point_counter == 1) {
                // if decimal pointer appears after 'e', NO!
                if (decimal_point_position > exp_position) {
                    ret = false;
                    break;
                }
            }
            // Exp cannot be the first or last symbol
            if (index == strlen - 1 || index == 0) {
                ret = false;
                break;
            }
        } else {
            if ( !std::isdigit(src_str[index]) ) {
                ret = false;
                break;
            }
        }
    }
    // empty string is not a double.
    if (strlen == 0) {
        ret = false;
    }

    if (ret == true) {
        dti.is_identified = true;
        dti.type_string = "Double";
        dti.data_string = src_str;
    }
    return dti;
}

bool is_double(const std::string& src_str)
{
    DataTypeIdentifier dti = identify_double(src_str);
    return dti.is_identified;
}

// TODO Test the following 3.
// Unsigned double. Without plus or minus sign
bool is_unsigned_double(const std::string& src_str)
{
    return is_double(src_str) && std::isdigit(src_str[0]);
}

// Positive double. With plus sign.
bool is_positive_double(const std::string& src_str)
{
    return is_double(src_str) && (src_str[0] == '+');
}

// Negative double. With minus sign.
bool is_negative_double(const std::string& src_str)
{
    return is_double(src_str) && (src_str[0] == '-');
}

Double as_double(const std::string& src_str)
{
    Double ret;
    if ( is_double(src_str) ) {
        ret = std::stod(src_str);
    } else {
        throw error::DataTypeConversionError(
                "Failed to identify and convert a Double type.");
    }
    return ret;
}

// Complex identifier.
DataTypeIdentifier identify_complex(const std::string& src_str)
/*
    The imaginary part usually carries the sign!
*/
{
    DataTypeIdentifier dti;
    dti.type_string = "Complex";

    bool ret = true;
    int strlen = src_str.length();
    int position_pivot_sign = 0;
    bool has_pivot_sign = false;

    if (src_str == "j") { // only 'j', okay
        ret = true;
        dti.is_identified = true;
        dti.real_string = "0.0";
        dti.imag_string = "1.0";
    } else if (src_str == "+j") {
        ret = true;
        dti.is_identified = true;
        dti.imag_string = "+1.0";
        dti.real_string = "0.0";
    } else if (src_str == "-j") {
        ret = true;
        dti.is_identified = true;
        dti.imag_string = "-1.0";
        dti.real_string = "0.0";
    } else if ( !(src_str.back() == 'j') ) {
        // if last symbol is not 'j', check if the whole string is a double
        if ( is_double(src_str) ) {
            ret = true;
            dti.is_identified = true;
            dti.real_string = src_str;
        } else {
            ret = false;
        }
    } else { // Symbol 'j' at the end and has at least 2 characters.
        // Search for the pivot sign one letter before last j.
        for (int index = src_str.length() - 2; index >= 0; index--) {
            if (src_str[index] == '-' || src_str[index] == '+') {
                // sign is not the first symbol
                if (index != 0) {
                    // Must be (digit, 'j', or '.') on right side,
                    // (digit or '.') on left side
                    if ( (src_str[index + 1] == 'j'
                           || src_str[index + 1] == '.'
                           || std::isdigit(src_str[index + 1]))
                         && (src_str[index - 1] == '.'
                              || std::isdigit(src_str[index - 1])) )
                    {
                        has_pivot_sign = true;
                        position_pivot_sign = index;
                        break;
                    } else {
                        continue;
                    }
                } else { // Sign is the first symbol, index = 0
                    // Rule out two signs in a row, as double cannot parse it.
                    if (strlen >= 2 && (src_str[index + 1] == '-'
                                        || src_str[index + 1] == '+') ) 
                    {
                        ret = false;
                        break;
                    }
                    // if no pivot sign found, first one is.
                    if (!has_pivot_sign) {
                        has_pivot_sign = true;
                    }
                }
            }
        } // end pivot sign searching 
        // Pivot sign found
        if (has_pivot_sign) {
            // Rule out '-.j' or '+.j' sequence
            if ( src_str[position_pivot_sign + 1] == '.'
                 && src_str[position_pivot_sign + 2] == 'j') {
                ret = false;
            } else {
                // Sign is the first symbol
                if (position_pivot_sign == 0) {
                    // Expressions '-j' or '+j' are okay
                    if (src_str[1] == 'j') {
                        ret = true;
                        dti.is_identified = true;
                        dti.real_string = "0.0";
                        if (src_str[0] == '-') {
                            dti.imag_string = "-1.0";    
                        } else {
                            dti.imag_string = "1.0";
                        }
                    } else {
                        // Test symbols from (include) the sign to the one
                        // before symbol 'j'.
                        std::string subliteral = src_str.substr(0, strlen-1);
                        ret = is_double(subliteral);
                        if (ret) {
                            dti.is_identified = true;
                            dti.real_string = "0.0";
                            dti.imag_string = subliteral;
                        }
                    }
                } else { // pivot sign in between, has then two sub-literals
                    // CAUTION! The second parametrer in `substr()` is the
                    // total length of the intended substring. This is different
                    // from slice used in Rable library. See the same function.
                    std::string leftsub = src_str.substr(0, position_pivot_sign);
                    std::string rightsub = src_str.substr(
                            position_pivot_sign, strlen-1-position_pivot_sign);
                    // Identify both sub-strings.
                    ret = is_double(leftsub) && is_double(rightsub);
                    if (ret) {
                        dti.is_identified = true;
                        if (leftsub == "") {
                            dti.real_string = "0.0";
                        } else {
                            dti.real_string = leftsub;
                        }
                        dti.imag_string = rightsub;
                    }
                }
            }
        } else { // no pivot sign
            // Note: case of only 'j' has been discussed at the beginning
            std::string sub = src_str.substr(0, strlen-1);
            ret = is_double(sub);
            if (ret) {
                dti.is_identified = true;
                dti.real_string = "0.0";
                dti.imag_string = sub;
            }
        }
    }
    return dti;
}

// Verifier.
bool is_complex(const std::string& src_str)
{
    DataTypeIdentifier identifier = identify_complex(src_str);
    return identifier.is_identified;
}

Complex as_complex(const std::string& src_str)
{
    DataTypeIdentifier identifier = identify_complex(src_str);
    Complex ret;
    if (identifier.is_identified) {
        double real = std::stod(identifier.real_string);
        double imag = std::stod(identifier.imag_string);
        ret = Complex(real, imag);
    } else {
        throw error::DataTypeConversionError(
                "Failed to identify and convert a Complex (double) type.");
    }
    return ret;
}

// Binary
bool is_binary(const std::string& src_str)
{
    std::string str = src_str;
    return util::is_valid_binary_string(str);
}

Binary as_binary(const std::string& src_str)
{
    Binary ret;
    if ( is_binary(src_str) ) {
        ret = src_str;
    } else {
        throw error::DataTypeConversionError(
                "Failed to identify and convert a Binary type.");
    }
    return ret;
}

// Bitstring
bool is_bitstring(const std::string& src_str)
{
    std::string str = src_str;
    return util::is_valid_bitstring(str);
}

Bitstring as_bitstring(const std::string& src_str)
{
    Bitstring ret;
    if ( is_bitstring(src_str) ) {
        ret = src_str;
    } else {
        throw error::DataTypeConversionError(
                "Failed to identify and convert a Bitstring type.");
    }
    return ret;
}

} // converter

}
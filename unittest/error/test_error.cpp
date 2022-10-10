/* Unittest: error */
#include "dora.hpp"
#include "error.hpp"

int main()
{
    abel::error::IncompatibleType err = abel::error::IncompatibleType("Incompatible Type");
    dora::assert_equal(__LINE__, err.get_header(), "INCOMPATIBLE_TYPE");
    dora::assert_equal(__LINE__, err.get_line(), -9999);
    dora::assert_equal(__LINE__, err.get_msg(), "Incompatible Type");

    abel::error::IndexOutOfRange err1 = abel::error::IndexOutOfRange("Index out of range");
    dora::assert_equal(__LINE__, err1.get_header(), "INDEX_OUT_OF_RANGE");
    dora::assert_equal(__LINE__, err1.get_line(), -9999);
    dora::assert_equal(__LINE__, err1.get_msg(), "Index out of range");

    abel::error::KeyNotFound err2 = abel::error::KeyNotFound("Key not found");
    dora::assert_equal(__LINE__, err2.get_header(), "KEY_NOT_FOUND");
    dora::assert_equal(__LINE__, err2.get_line(), -9999);
    dora::assert_equal(__LINE__, err2.get_msg(), "Key not found");


    abel::error::DuplicateKey err3 = abel::error::DuplicateKey("Duplicate key");
    err3.set_line(10000); // set line number
    dora::assert_equal(__LINE__, err3.get_header(), "DUPLICATE_KEY");
    dora::assert_equal(__LINE__, err3.get_line(), 10000);
    dora::assert_equal(__LINE__, err3.get_msg(), "Duplicate key");
}
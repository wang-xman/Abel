/* Unit test: binary */
#include <iostream>
#include "binary.hpp"
#include "dora.hpp"

using namespace abel;

void test_valid_binary_string()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string test_string = "";        
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "0b";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "10";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "00";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "0";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "1";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        // "0b" along makes no sense
        test_string = "0b";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        // space not acceptable
        test_string = "0 b0";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        // non binary characters not acceptable.
        test_string = "0b0a";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "0b5010";
        dora::assert_false( __LINE__, util::is_valid_binary_string(test_string) );
        // valid
        test_string = "0b0";
        dora::assert_true( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "0b00";
        dora::assert_true( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "0b10";
        dora::assert_true( __LINE__, util::is_valid_binary_string(test_string) );
        test_string = "0b001001";
        dora::assert_true( __LINE__, util::is_valid_binary_string(test_string) );
        // all 0's
        test_string = "0b000000";
        dora::assert_true( __LINE__, util::is_valid_binary_string(test_string) );
        // all 1's
        test_string = "0b11111111";
        dora::assert_true( __LINE__, util::is_valid_binary_string(test_string) );
    };
    test_case.all();
}

void test_type_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string test_string = "0b10101";
        Binary test_binary(test_string);
        dora::assert_equal(__LINE__, test_binary.type_name(), "Binary");
    };

    test_case.pool = [](){
        Binary test_binary("0b10101");
        dora::assert_equal(__LINE__, test_binary.type_name(), "Binary");
        dora::assert_equal(__LINE__, test_binary.value(), "0b10101");
        // directly convert into a std::string type
        std::string str = test_binary;
        dora::assert_equal(__LINE__, str, "0b10101");
    };
    
    test_case.all();
}

void test_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string test_string = "0b10102";
        // Triggers error
        //Binary test_binary(test_string);
    };

    test_case.all();
}

int main()
{
    test_valid_binary_string();
    test_type_method();
    test_constructor();
}
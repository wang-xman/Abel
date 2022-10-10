/* Unit test: binary */
#include <iostream>
#include "bitstring.hpp"
#include "dora.hpp"

using namespace abel;

void test_valid_bitstring()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string test_string = "";        
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "b";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "10";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "00";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "0";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "1";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        // "_b" along makes no sense
        test_string = "_b";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        // space not acceptable
        test_string = "_ b";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        // non binary characters not acceptable.
        test_string = "_b0a.";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "_b50.10";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "_b.";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
        // cannot have more than two dots
        test_string = "_b100.10.1";
        dora::assert_false( __LINE__, util::is_valid_bitstring(test_string) );
    };

    test_case.pool = [](){
        std::string test_string = "";
        // valid
        test_string = "_b0";
        dora::assert_true( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "_b00";
        dora::assert_true( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "_b10";
        dora::assert_true( __LINE__, util::is_valid_bitstring(test_string) );
        test_string = "_b001001";
        dora::assert_true( __LINE__, util::is_valid_bitstring(test_string) );
        // all 0's with dot
        test_string = "_b000.000";
        dora::assert_true( __LINE__, util::is_valid_bitstring(test_string) );
        // all 1's wit dot
        test_string = "_b.11111111";
        dora::assert_true( __LINE__, util::is_valid_bitstring(test_string) );
    };
    test_case.all();
}

void test_type_method() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_string = "_b10101";
        Bitstring test_bitstring(test_string);
        dora::assert_equal(__LINE__, test_bitstring.type_name(), "Bitstring");
    };

    test_case.pool = [](){
        Bitstring test_bitstring("_b10.101");
        dora::assert_equal(__LINE__, test_bitstring.type_name(), "Bitstring");
        dora::assert_equal(__LINE__, test_bitstring.value(), "_b10.101");
        // directly convert into a std::string type
        std::string str = test_bitstring;
        dora::assert_equal(__LINE__, str, "_b10.101");
    };
    
    test_case.all();
}

void test_constructor() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string test_string = "_b10102";
        // Triggers error
        //Bitstring test_bitstring(test_string);
    };

    test_case.all();
}


int main() {
    test_valid_bitstring();
    test_type_method();
    test_constructor();
}
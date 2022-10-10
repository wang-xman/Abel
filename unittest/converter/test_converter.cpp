/* Unittest: converter */
#include <iostream>
#include "converter.hpp"
#include "dora.hpp"

using namespace abel;

/* Identifiers */
// Null
void test_is_null()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        //converter::Converter tester; // converter for testing
        std::string test_string = "null";
        dora::assert_true(__LINE__, converter::is_null(test_string));
        dora::assert_true(__LINE__, converter::is_null("null"));
        // false
        dora::assert_false(__LINE__, converter::is_null("NULL"));
        // false
        dora::assert_false(__LINE__, converter::is_null("Null"));
        // WARNING causes segmentation fault
        //dora::assert_false(__LINE__, converter::is_null(NULL));
    };

    test_case.all();
}

// Bool
void test_is_bool()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        //converter::Converter tester; // converter for testing
        // string lvalues
        std::string test_string = "true";
        dora::assert_true(__LINE__, converter::is_bool(test_string));
        test_string = "false";
        dora::assert_true(__LINE__, converter::is_bool(test_string));
        // string rvalues
        dora::assert_true(__LINE__, converter::is_bool("true"));
        dora::assert_true(__LINE__, converter::is_bool("false"));

        // false
        dora::assert_false(__LINE__, converter::is_bool("TRUE"));
        dora::assert_false(__LINE__, converter::is_bool("FALSE"));
        dora::assert_false(__LINE__, converter::is_bool("True"));
        dora::assert_false(__LINE__, converter::is_bool("False"));
    };

    test_case.all();
}

// Integer
void test_is_integer()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // special cases
    test_case.pool = []() {
        //Converter tester; // converter for testing
        // string lvalues
        std::string test_string = "010";
        dora::assert_true(__LINE__, converter::is_integer(test_string));
        test_string = "000";
        dora::assert_true(__LINE__, converter::is_integer(test_string));
        // empty string
        test_string = "";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        // space
        test_string = "    ";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
    };
    
    // regular integers
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        // string lvalues
        std::string test_string = "0123";
        dora::assert_true(__LINE__, converter::is_integer(test_string));
        test_string = "+2719827391";
        dora::assert_true(__LINE__, converter::is_integer(test_string));
        test_string = "-625";
        dora::assert_true(__LINE__, converter::is_integer(test_string));
    };

    // non-integers
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        // string lvalues
        std::string test_string = "0.123";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        test_string = "+.2719827391";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        test_string = "-625.";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        test_string = "-0.0";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        // non digit
        test_string = ".";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        test_string = "109a";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
        test_string = "5e10";
        dora::assert_false(__LINE__, converter::is_integer(test_string));
    };

    test_case.all();
}

void test_is_unsigned_integer()
{
    dora::TestCase test_case(__FILE__, __func__);

    // regular integers
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        // string lvalues
        std::string test_string = "0123";
        dora::assert_true(__LINE__, converter::is_unsigned_integer(test_string));
        test_string = "+2719827391";
        dora::assert_false(__LINE__, converter::is_unsigned_integer(test_string));
        test_string = "-625";
        dora::assert_false(__LINE__, converter::is_unsigned_integer(test_string));
    };

    test_case.all();
}

void test_is_positive_integer()
{
    dora::TestCase test_case(__FILE__, __func__);

    // regular integers
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        // unsigned is considered different from positive
        std::string test_string = "0123";
        dora::assert_false(__LINE__, converter::is_positive_integer(test_string));
        test_string = "+2719827391";
        dora::assert_true(__LINE__, converter::is_positive_integer(test_string));
        test_string = "-625";
        dora::assert_false(__LINE__, converter::is_positive_integer(test_string));
    };

    test_case.all();
}

void test_is_negative_integer()
{
    dora::TestCase test_case(__FILE__, __func__);

    // regular integers
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        // unsigned is considered different from negative
        std::string test_string = "0123";
        dora::assert_false(__LINE__, converter::is_negative_integer(test_string));
        test_string = "+2719827391";
        dora::assert_false(__LINE__, converter::is_negative_integer(test_string));
        test_string = "+00";
        dora::assert_false(__LINE__, converter::is_negative_integer(test_string));
        // negative integers
        test_string = "-625";
        dora::assert_true(__LINE__, converter::is_negative_integer(test_string));
        test_string = "-00";
        dora::assert_true(__LINE__, converter::is_negative_integer(test_string));
    };

    test_case.all();
}

/// Double
void test_is_double()
{
    dora::TestCase test_case(__FILE__, __func__);

    // special cases
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string = "000";
        dora::assert_true(__LINE__, converter::is_double(test_string));
        // empty string is not double
        test_string = "";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // space is not double
        test_string = "  ";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // just a decimal point, NO!
        test_string = ".";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // cannot contain space
        test_string = " 1.0";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        test_string = "1.0e+5 ";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // exponential symbol can not be first one
        test_string = "e+10";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // sign cannot be last symbol
        test_string = ".5+";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        test_string = "1.e-";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // sign cannot be followed by 'e' immediately
        test_string = "-e";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        test_string = "+e+10";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // illegal
        test_string = "-.e+1";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        test_string = "+.e+10";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        // decimal cannot appear after 'e'
        test_string = "1e+1.0";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        test_string = "+-";
        dora::assert_false(__LINE__, converter::is_double(test_string));
        test_string = "-+";
        dora::assert_false(__LINE__, converter::is_double(test_string));
    };

    // integers are double too.
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string = "000";
        dora::assert_true(__LINE__, converter::is_double(test_string));
        test_string = "+2719827391";
        dora::assert_true(__LINE__, converter::is_double(test_string));
        test_string = "-625";
        dora::assert_true(__LINE__, converter::is_double(test_string));
    };

    // legal ones
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string;
        double target;
        test_string = "1.e+0"; target = 1.e+0;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = ".5E+1"; target = .5E+1; 
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "1.E+01"; target = 1.E+01;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "-1.E+00"; target = -1.E+00;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "1.e+0"; target = 1.e+0;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "-.5"; target = -.5;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = ".5"; target = .5;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "+1."; target = +1.;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "1."; target = 1.;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);
    };

    // legal, without 'e'
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string;
        double target;
        test_string = "-0.003"; target = -0.003;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "872656.12378"; target = 872656.12378;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);

        test_string = "-0008.000000008"; target = -0008.000000008;
        dora::assert_true(__LINE__, converter::is_double(test_string));
        dora::assert_equal(__LINE__, std::stod(test_string), target);
    };

    test_case.all();
}


/* Complex */

void test_is_complex()
{
    dora::TestCase test_case(__FILE__, __func__);

    // illegal
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string;
        test_string = ".j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "ej";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
    };

    // double front signs are illegal
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string;
        // double signs at front
        test_string = "+-j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "++j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "-+1.0+.1e+0j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "--.1e+0j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "+-.1e+0j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "++.1e+0j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "-+.1e+0j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
        test_string = "+-.5e+00-5.e+02j";
        dora::assert_false(__LINE__, converter::is_complex(test_string));
    };


    // special cases
    test_case.pool = []() {
        //converter::Converter tester; // converter for testing
        std::string test_string;
        test_string = "j";
        dora::assert_true(__LINE__, converter::is_complex(test_string));
        // '+j'
        test_string = "+j";
        dora::assert_true(__LINE__, converter::is_complex(test_string));
        // '-j'
        test_string = "-j";
        dora::assert_true(__LINE__, converter::is_complex(test_string));
        // double is also a valid complex
        test_string = "0";
        dora::assert_true(__LINE__, converter::is_complex(test_string));

        test_string = "0.1e-10";
        dora::assert_true(__LINE__, converter::is_complex(test_string));

        test_string = "1.0j";
        dora::assert_true(__LINE__, converter::is_complex(test_string));
    };

    // scientific notations
    test_case.pool = []() {
        //Converter tester; // converter for testing
        std::string test_string;
        test_string = "-.5e+00-5.e+02j";
        dora::assert_true(__LINE__, converter::is_complex(test_string));
        test_string = "-.1e+0j";
        dora::assert_true(__LINE__, converter::is_complex(test_string));
    };

    test_case.all();
}

void test_identify_complex()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        //Converter tester; // converter for testing
        DataTypeIdentifier dti;
        std::string test_string;
        test_string = "-.5e+00-5.e+02j";
        dti = converter::identify_complex(test_string);
        dora::assert_equal(__LINE__, dti.real_string, "-.5e+00");
        dora::assert_equal(__LINE__, dti.imag_string, "-5.e+02");
    };

    test_case.pool = []() {
        //Converter tester; // converter for testing
        DataTypeIdentifier dti;
        std::string test_string;
        test_string = "-j";
        dti = converter::identify_complex(test_string);
        dora::assert_equal(__LINE__, dti.real_string, "0.0");
        dora::assert_equal(__LINE__, dti.imag_string, "-1.0");
    };

    test_case.pool = []() {
        //Converter tester; // converter for testing
        DataTypeIdentifier dti;
        std::string test_string;
        test_string = "+.1j";
        dti = converter::identify_complex(test_string);
        dora::assert_equal(__LINE__, dti.real_string, "0.0");
        dora::assert_equal(__LINE__, dti.imag_string, "+.1");
    };

    test_case.pool = []() {
        //Converter tester; // converter for testing
        DataTypeIdentifier dti;
        std::string test_string;
        test_string = "-.1e+0j";
        dti = converter::identify_complex(test_string);
        dora::assert_equal(__LINE__, dti.real_string, "0.0");
        dora::assert_equal(__LINE__, dti.imag_string, "-.1e+0");
    };

    test_case.pool = []() {
        //Converter tester; // converter for testing
        DataTypeIdentifier dti;
        std::string test_string;
        test_string = ".5e-12+1.e+00j";
        dti = converter::identify_complex(test_string);
        dora::assert_equal(__LINE__, dti.real_string, ".5e-12");
        dora::assert_equal(__LINE__, dti.imag_string, "+1.e+00");
    };

    test_case.pool = []() {
        //Converter tester; // converter for testing
        DataTypeIdentifier dti;
        std::string test_string;
        test_string = "0+1.0j";
        dti = converter::identify_complex(test_string);
        dora::assert_equal(__LINE__, dti.is_identified, true);
        dora::assert_equal(__LINE__, dti.real_string, "0");
        dora::assert_equal(__LINE__, dti.imag_string, "+1.0");
    };

    test_case.all();

}

void test_as_complex()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string test_string;
        test_string = "1.0j";
        Complex comp = converter::as_complex(test_string);
    };

    test_case.all();
}

int main()
{
    test_is_null();
    test_is_bool();
    // Integer
    test_is_integer();
    test_is_unsigned_integer();
    test_is_positive_integer();
    test_is_negative_integer();
    // Double
    test_is_double();
    // Complex
    test_is_complex();
    test_identify_complex();
    test_as_complex();
}
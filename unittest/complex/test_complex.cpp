/* Unittest: complex */
#include "complex.hpp"
#include "dora.hpp"

void test_direct_init()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // direct init with numbers and type check
    test_case.pool = [](){
        abel::complex<double> z4 {1., 2.0};
        // Using template the type string is "complex_T"
        dora::assert_equal(__LINE__, z4.type_name(), "complex_T");
    };

    // direct init with numbers
    test_case.pool = [](){
        abel::complex<double> z4 {1., 2.0};
        dora::assert_equal(__LINE__, z4.real(), 1.0);
        dora::assert_equal(__LINE__, z4.imag(), 2.0);
    };

    // direct init with std::complex
    test_case.pool = [](){
        std::complex<int> c1 {4, 5};
        abel::complex<int> ci4 {c1};
        dora::assert_equal(__LINE__, ci4.real(), 4);
        dora::assert_equal(__LINE__, ci4.imag(), 5);
    };

    // special cases
    test_case.pool = [](){
        std::complex<int> std_c1 {4, 0}; // real
        abel::complex<int> ci4 {std_c1};
        dora::assert_equal(__LINE__, ci4.real(), 4);
        dora::assert_equal(__LINE__, ci4.imag(), 0);
    };

    test_case.all();
}

void test_conversion()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // conversion to std:complex
    test_case.pool = [](){
        abel::complex<double> z4 {1., 2.0};
        std::complex<double> std_z4 = std::complex<double>(z4);
        // compare
        dora::assert_equal(__LINE__, std_z4.real(), z4.real());
        dora::assert_equal(__LINE__, std_z4.imag(), z4.imag());
        // compare directly to std complex
        std::complex<double> std_z5 {1., 2.0};
        dora::assert_equal(__LINE__, std_z5.real(), z4.real());
        dora::assert_equal(__LINE__, std_z5.imag(), z4.imag());
    };

    test_case.all();
}


void test_equal()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // compare two Complex objects
    test_case.pool = [](){
        abel::complex<double> z1 {1., 2.0};
        abel::complex<double> z2 {1, 2};
        abel::complex<double> z3 {0.1, 0.2};
        dora::assert_true(__LINE__, z1 == z2);
        dora::assert_false(__LINE__, z1 == z3);
        dora::assert_true(__LINE__, z1 != z3);
    };

    // compare Complex and std::complex
    test_case.pool = [](){
        abel::complex<double> z1 {1., 2.0};
        std::complex<double> z2 {1, 2};
        std::complex<double> z3 {0.1, 0.2};
        dora::assert_true(__LINE__, z1 == z2);
        dora::assert_false(__LINE__, z1 == z3);
        dora::assert_true(__LINE__, z1 != z3);
    };
    
    // compare std::complex with abel::complex
    test_case.pool = [](){
        abel::complex<double> z1 {1., 2.0};
        std::complex<double> z2 {1, 2};
        std::complex<double> z3 {0.1, 0.2};
        dora::assert_true(__LINE__, z2 == z1);
        dora::assert_true(__LINE__, z3 != z1);
        dora::assert_false(__LINE__, z3 == z1);
    };

    test_case.all();
}

void test_Complex_class()
{
    dora::TestCase test_case(__FILE__, __func__);

    // type string for Complex is "Complex".
    test_case.pool = []() {
        abel::Complex z1 {1., 2.0};
        dora::assert_equal(__LINE__, z1.type_name(), "Complex");
    };

    // compare two Complex objects
    test_case.pool = [](){
        abel::Complex z1 {1., 2.0};
        double r2 = 1;
        double i2 = 2;
        abel::Complex z2 {r2, i2};
        abel::Complex z3 {0.1, 0.2};
        dora::assert_true(__LINE__, z1 == z2);
        dora::assert_false(__LINE__, z1 == z3);
        dora::assert_true(__LINE__, z1 != z3);
    };
    
    // Direct init with std::complex double type
    test_case.pool = []() {
        std::complex<double> c_std {4, 5};
        abel::Complex ci4 {c_std};
        dora::assert_equal(__LINE__, ci4.real(), 4);
        dora::assert_equal(__LINE__, ci4.imag(), 5);
    };
    
    // Dircty init with std::complex int type.
    test_case.pool = []() {
        std::complex<int> c_std {4, 5};
        abel::Complex ci4 {c_std};
        dora::assert_equal(__LINE__, ci4.real(), 4);
        dora::assert_equal(__LINE__, ci4.imag(), 5);
    };

    // Conversion to std:complex
    test_case.pool = [](){
        abel::Complex z4 {1., 2.0};
        std::complex<double> std_z4 = std::complex<double>(z4);
        // compare
        dora::assert_equal(__LINE__, std_z4.real(), z4.real());
        dora::assert_equal(__LINE__, std_z4.imag(), z4.imag());
        // compare directly to std complex
        std::complex<double> std_z5 {1., 2.0};
        dora::assert_equal(__LINE__, std_z5.real(), z4.real());
        dora::assert_equal(__LINE__, std_z5.imag(), z4.imag());
        // Compare Complex with std::complex
        dora::assert_equal(__LINE__, z4, std_z5);
        // Compare Complex.value() with std::complex
        dora::assert_equal(__LINE__, z4.value(), std_z5);
    };

    // Via abel::Double
    test_case.pool = []() {
        abel::Double r {4.0};
        abel::Double i {5.0};
        abel::Complex ci4 {r, i};
        dora::assert_equal(__LINE__, ci4.real(), 4);
        dora::assert_equal(__LINE__, ci4.imag(), 5);
    };

    // Via abel::Integer
    test_case.pool = []() {
        abel::Integer r {4};
        abel::Integer i {5};
        abel::Complex ci4 {r, i};
        dora::assert_equal(__LINE__, ci4.real(), 4);
        dora::assert_equal(__LINE__, ci4.imag(), 5);
    };

    test_case.all();
}

int main()
{
    test_direct_init();
    test_conversion();
    test_equal();

    test_Complex_class();
}
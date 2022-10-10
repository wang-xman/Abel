/* Unittest: double */
#include <iostream>
#include "double.hpp"
#include "dora.hpp"

using namespace abel;

void test_type_and_value_methods()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Double test(1);
        dora::assert_equal(__LINE__, test.type_name(), "Double");
    };

    test_case.pool = [](){
        Double test(5);
        dora::assert_equal(__LINE__, test.value(), 5);
    };

    test_case.all();
}

void test_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Construct from C++ double
    test_case.pool = [](){
        // from a rvalue;
        Double test_r (100.0);
        dora::assert_equal(__LINE__, test_r.type_name(), "Double");
        dora::assert_equal(__LINE__, test_r.value(), 100.00);
        // from a lvalue
        double c_double = 66;
        Double test_l (c_double);
        dora::assert_equal(__LINE__, test_l.type_name(), "Double");
        dora::assert_equal(__LINE__, test_l.value(), 66);
    };

    test_case.all();
}


void test_copy_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);

    // from Double object
    test_case.pool = [](){
        double c_src = 9000.0;
        // source Double object;
        Double test_src (c_src);
        // copy construct from source object.
        Double test_accept (test_src);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Double");
        dora::assert_equal(__LINE__, test_accept.value(), 9000.0);
        // change double variable
        c_src = 0.6;
        // src and accept objects unchanged
        dora::assert_equal(__LINE__, test_src.value(), 9000);
        dora::assert_equal(__LINE__, test_accept.value(), 9000);
        // change value of source object
        test_src = 6.0;
        // accept object doesn't change
        dora::assert_equal(__LINE__, test_accept.value(), 9000);
    };

    // from shared pointer Double
    test_case.pool = [](){
        double c_src = 9000.0;
        // source Double pointer;
        std::shared_ptr<Double> test_src (new Double(c_src));
        // copy construct from source object.
        Double test_accept (test_src);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Double");
        dora::assert_equal(__LINE__, test_accept.value(), 9000.0);
        // change double variable
        c_src = 0.6;
        // src and accept objects unchanged
        dora::assert_equal(__LINE__, test_src->value(), 9000);
        dora::assert_equal(__LINE__, test_accept.value(), 9000);
    };

    test_case.all();
}


void test_comparison()
{
    dora::TestCase test_case(__FILE__, __func__);

    // compare objects
    test_case.pool = [](){
        // source Double object;
        Double test_src (1000.0);
        // copy construct from source object.
        Double test_accept (800.0);
        dora::assert_true(__LINE__, test_src > test_accept);
        dora::assert_false(__LINE__, test_src < test_accept);
        dora::assert_false(__LINE__, test_src == test_accept);
        dora::assert_true(__LINE__, test_src != test_accept);
        // change double object
        test_accept = 1000.0;
        dora::assert_true(__LINE__, test_src == test_accept);
        dora::assert_false(__LINE__, test_src != test_accept);
    };

    // compare objects - signed
    test_case.pool = [](){
        // source Double object;
        Double test_src (10.0);
        // copy construct from source object.
        Double test_accept (-8.0);
        dora::assert_true(__LINE__, test_src > test_accept);
        dora::assert_true(__LINE__, test_accept < test_src);

        dora::assert_false(__LINE__, test_accept > test_src);
        dora::assert_false(__LINE__, test_src < test_accept);

        dora::assert_false(__LINE__, test_src == test_accept);
        dora::assert_false(__LINE__, test_accept == test_src);

        dora::assert_true(__LINE__, test_src != test_accept);
        dora::assert_true(__LINE__, test_accept != test_src);
        // change double object
        test_accept = 1000.0;
        dora::assert_false(__LINE__, test_src == test_accept);
        dora::assert_true(__LINE__, test_src != test_accept);
    };

    // compare object and rvalue number
    test_case.pool = [](){
        // source Double object;
        Double test_src (1000.0);
        dora::assert_true(__LINE__, test_src > 0.5);
        dora::assert_true(__LINE__, test_src < 40000);
        dora::assert_false(__LINE__, test_src > 40000);
        dora::assert_false(__LINE__, test_src == 10.0);
        dora::assert_true(__LINE__, test_src != 1.0);
    };

    // compare object and rvalue number - positive and negative
    test_case.pool = [](){
        // source Double object;
        Double test_src (-1000.0);
        dora::assert_false(__LINE__, test_src > -0.5); // -1000<0.5 true
        dora::assert_true(__LINE__, test_src < -80.5); // -1000<-80.5 true
        dora::assert_false(__LINE__, test_src > 0.5); // -1000>0.5 false
        dora::assert_true(__LINE__, test_src < 40000); // -1000<40000 true
        dora::assert_false(__LINE__, test_src > 40000); // -1000>40000 false
        dora::assert_false(__LINE__, test_src == 10.0); // -1000==10.0 false
        dora::assert_true(__LINE__, test_src != 1.0); // -1000!=1.0 true
    };

    test_case.all();
}

int main()
{
    test_type_and_value_methods();
    test_constructor();
    test_copy_constructor();
    test_comparison();
}
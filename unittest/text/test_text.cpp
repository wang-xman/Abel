/* Unittest: text */
#include <iostream>
#include "text.hpp"
#include "dora.hpp"

using namespace abel;

void test_type_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Text test_string("TEST_string");
        dora::assert_equal(__LINE__, test_string.type_name(), "Text");
    };
    test_case.all();
}

void test_value_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Text test_string("55x");
        dora::assert_equal(__LINE__, test_string.value(), "55x");
    };

    test_case.all();
}

void test_copy_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // Default copy constructor
    test_case.pool = [](){
        Text test_string1("100");
        dora::assert_equal(__LINE__, test_string1.type_name(), "Text");
        dora::assert_equal(__LINE__, test_string1.value(), "100");
        // copy-construct a new string object.
        Text test_accept (test_string1);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Text");
        dora::assert_equal(__LINE__, test_accept.value(), "100");
    };

    // Copy-construct from share pointer
    test_case.pool = [](){
        // a shared pointer.
        std::shared_ptr<Text> test_string1 (new Text("100"));
        dora::assert_equal(__LINE__, test_string1->type_name(), "Text");
        dora::assert_equal(__LINE__, test_string1->value(), "100");
        // copy-construct a new string object.
        Text test_accept (test_string1);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Text");
        dora::assert_equal(__LINE__, test_accept.value(), "100");
    };

    test_case.all();
}

void test_assignment()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Assign an object
    test_case.pool = [](){
        Text test_string1("100");
        Text test_accept("66");
        // Before assignment
        dora::assert_equal(__LINE__, test_accept.type_name(), "Text");
        dora::assert_equal(__LINE__, test_accept.value(), "66");
        // Assign an integer object to an integer object.
        test_accept = test_string1;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Text");
        dora::assert_equal(__LINE__, test_accept.value(), "100");
    };

    // Assign a variable. Value is copied.
    test_case.pool = [](){
        std::string src_string = "9000.0";
        Text test_accept;
        test_accept = src_string;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Text");
        dora::assert_equal(__LINE__, test_accept.value(), "9000.0");
        // change value of the variable
        src_string = "6.0";
        // Object internal value doesn't change
        dora::assert_equal(__LINE__, test_accept.value(), "9000.0");
    };

    // Assign a rvalue
    test_case.pool = [](){
        Text test_accept;
        test_accept = "5555.05";
        dora::assert_equal(__LINE__, test_accept.type_name(), "Text");
        dora::assert_equal(__LINE__, test_accept.value(), "5555.05");
    };

    test_case.all();
}

void test_stream()
{
     dora::TestCase test_case(__FILE__, __func__);

    // Assign an object
    test_case.pool = [](){
        Text test_accept("113366");
        std::cout << test_accept << "\n";
    };

    test_case.all();
}


int main()
{
    test_type_method();
    test_value_method();
    test_copy_constructor();
    test_assignment();
    test_stream();
}
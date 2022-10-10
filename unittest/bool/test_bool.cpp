/* Unittest: bool */
#include <iostream>
#include "bool.hpp"
#include "dora.hpp"

using namespace abel;

void test_type_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Bool test_bool(true);
        dora::assert_equal(__LINE__, test_bool.type_name(), "Bool");
    };
    test_case.all();
}

void test_value_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Bool test_bool(false);
        dora::assert_equal(__LINE__, test_bool.value(), false);
    };

    test_case.all();
}

void test_copy_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // Default copy constructor
    test_case.pool = [](){
        Bool test_bool1(true);
        dora::assert_equal(__LINE__, test_bool1.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_bool1.value(), true);
        // copy-construct a new Bool object.
        Bool test_accept (test_bool1);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), true);
    };

    // Copy-construct from share pointer
    test_case.pool = [](){
        // a shared pointer.
        std::shared_ptr<Bool> test_bool1 (new Bool(false));
        dora::assert_equal(__LINE__, test_bool1->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_bool1->value(), false);
        // copy-construct a new Bool object.
        Bool test_accept (test_bool1);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), false);
    };

    // Copy-construct from unique pointer
    test_case.pool = [](){
        // a shared pointer.
        //std::unique_ptr<Bool> test_bool1 (new Bool(false));
        std::unique_ptr<Bool> test_bool1 = std::make_unique<Bool>(false);
        dora::assert_equal(__LINE__, test_bool1->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_bool1->value(), false);
        // copy-construct a new Bool object.
        Bool test_accept (test_bool1);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), false);
        // WARNING! Following causes segmentation fault.
        //dora::assert_equal(__LINE__, test_bool1->value(), false);
    };

    // Copy-construct from unique pointer of object
    test_case.pool = [](){
        // a shared pointer.
        std::unique_ptr<Bool> test_bool1 = std::make_unique<Bool>(false);
        dora::assert_equal(__LINE__, test_bool1->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_bool1->value(), false);
        // downcast
        std::unique_ptr<object> downcasted = std::unique_ptr<object>(
            static_cast<object*>(test_bool1.release()));
        // copy-construct a new Bool object from pointer of object.
        Bool test_accept (downcasted);
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), false);
        // WARNING! The following cauese segmentation fault as downcasted
        // has been moved.
        //dora::assert_equal(__LINE__, downcasted->type_name(), "object");
    };

    test_case.all();
}

void test_assignment()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Assign an object
    test_case.pool = [](){
        Bool test_bool1 (true);
        Bool test_accept(false);
        // Before assignment
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), false);
        // Assign a Bool object to another Bool object.
        test_accept = test_bool1;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), true);
    };

    // Assign a variable. Value is copied.
    test_case.pool = [](){
        bool src_bool = true;
        Bool test_accept;
        test_accept = src_bool;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), true);
        // change value of the variable
        src_bool = false;
        // Object internal value doesn't change
        dora::assert_equal(__LINE__, test_accept.value(), true);
    };

    // Assign a rvalue
    test_case.pool = [](){
        Bool test_accept;
        test_accept = false;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), false);
    };

    // Assign a unique pointer move the original pointer.
    test_case.pool = [](){
        Bool test_accept;
        std::unique_ptr<Bool> ptr = std::make_unique<Bool>(false);
        test_accept = ptr;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Bool");
        dora::assert_equal(__LINE__, test_accept.value(), false);
        // WARNING! Causes segmentation fault due to move.
        //dora::assert_equal(__LINE__, ptr->value(), false);
    };

    test_case.all();
}


// Test compare operators
void test_comparison_operators()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Bool vs Bool
    test_case.pool = [](){
        Bool b1 (false);
        Bool b2 (true);
        dora::assert_true(__LINE__, b1 != b2);
        dora::assert_false(__LINE__, b1 == b2);
        dora::assert_false(__LINE__, b2 == b1);
        dora::assert_true(__LINE__, b2 != b1);
    };

    // Bool vs bool
    test_case.pool = [](){
        Bool b1 (false);
        bool b2 = true;
        dora::assert_true(__LINE__, b1 != b2);
        dora::assert_false(__LINE__, b1 == b2);
        dora::assert_false(__LINE__, b2 == b1);
        dora::assert_true(__LINE__, b2 != b1);
    };

    // Bool vs bool
    test_case.pool = [](){
        Bool b1 (false);
        bool b2 = false;
        dora::assert_false(__LINE__, b1 != b2);
        dora::assert_true(__LINE__, b1 == b2);
        dora::assert_false(__LINE__, b2 != b1);
        dora::assert_true(__LINE__, b2 == b1);
    };

    test_case.all();
}


// As along as it is working, no need to be include in test.
void test_stream()
{
     dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Bool test_accept(false);
        std::cout << test_accept << "\n";
    };

    test_case.all();
}


int main()
{
    test_type_method();
    test_value_method();
/// Copy constructors
    test_copy_constructor();
/// Copy assignment operator
    test_assignment();

/// Comparison operators
    test_comparison_operators();
}
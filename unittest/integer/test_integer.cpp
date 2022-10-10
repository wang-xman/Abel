/* Unittest: integer */
#include <iostream>
#include <memory>
#include "bool.hpp"
#include "integer.hpp"
#include "dora.hpp"

using namespace abel;

void test_instantiation()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // Instantiate
    test_case.pool = [](){
        Integer test1;
        dora::assert_equal(__LINE__, test1.type_name(), "Integer");
    };

    // Instantiate using aggregate
    test_case.pool = [](){
        Integer test1{};
        dora::assert_equal(__LINE__, test1.type_name(), "Integer");
    };

    test_case.all();
}

void test_init()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // Init using parenthesis.
    test_case.pool = [](){
        Integer test1 (1);
        dora::assert_equal(__LINE__, test1.type_name(), "Integer");
    };
    
    // Init using initialisation list
    test_case.pool = [](){
        Integer test1 {1};
        dora::assert_equal(__LINE__, test1.type_name(), "Integer");
    };
    test_case.all();
}


void test_copy_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);
    // Copy constructor
    test_case.pool = [](){
        Integer int_obj {10};
        Integer test {int_obj};
        dora::assert_equal(__LINE__, test.type_name(), "Integer");
    };
    
    // copy construct from a shared pointer
    test_case.pool = [](){
        std::shared_ptr<Integer> int_ptr (new Integer (100));
        Integer test {int_ptr};
        dora::assert_equal(__LINE__, test.type_name(), "Integer");
        dora::assert_equal(__LINE__, test.value(), 100);
    };

    // copy construct from a unique pointer
    test_case.pool = [](){
        std::unique_ptr<Integer> int_uptr = std::make_unique<Integer>(100);
        // copy constructor invoked
        Integer test {int_uptr};
        dora::assert_equal(__LINE__, test.type_name(), "Integer");
        dora::assert_equal(__LINE__, test.value(), 100);
        // CAUTION! The following causes segmentation fault due to invalid
        // unique pointer after move.
        //dora::assert_equal(__LINE__, int_uptr->value(), 100);
    };

    // copy construct from unique pointer of object
    test_case.pool = [](){
        std::unique_ptr<Integer> int_uptr = std::make_unique<Integer>(100);
        // cast the above back to a unique ptr of `object`
        std::unique_ptr<object> int_obj = std::unique_ptr<object>(int_uptr.release());
        // copy constructor from unique ptr of object
        Integer test {int_obj};
        dora::assert_equal(__LINE__, test.type_name(), "Integer");
        dora::assert_equal(__LINE__, test.value(), 100);
        // CAUTION! The following causes segmentation fault due to invalid
        // unique pointer after move.
        //dora::assert_equal(__LINE__, int_uptr->value(), 100);
    };

    // failed to copy construct from unique pointer of object typed differently
    test_case.pool = [](){
        // a unique pointer of Bool type.
        std::unique_ptr<Bool> bool_uptr = std::make_unique<Bool>(false);
        // cast the above back to a unique ptr of `object`
        std::unique_ptr<object> bool_obj = std::unique_ptr<object>(bool_uptr.release());
        // copy constructor from unique ptr of object, but typed Bool!
        Integer test {bool_obj};
    };

    test_case.all();
}


void test_type_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Integer test_int1(1);
        dora::assert_equal(__LINE__, test_int1.type_name(), "Integer");
    };
    test_case.all();
}

void test_value_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Integer test_int1(5);
        dora::assert_equal(__LINE__, test_int1.value(), 5);
    };

    test_case.all();
}

void test_assignment()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Assign an object
    test_case.pool = [](){
        Integer test_int1(100);
        Integer test_accept; //(66);
        // Before assignment
        dora::assert_equal(__LINE__, test_accept.type_name(), "Integer");
        //dora::assert_equal(__LINE__, test_accept.value(), 66);
        // Assign an integer object to an integer object.
        test_accept = test_int1;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Integer");
        dora::assert_equal(__LINE__, test_accept.value(), 100);
    };

    // Assign a variable. Value is copied.
    test_case.pool = [](){
        int src_int = 9000;
        Integer test_accept;
        test_accept = src_int;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Integer");
        dora::assert_equal(__LINE__, test_accept.value(), 9000);
        // change value of the variable
        src_int = 6;
        // Object internal value doesn't change
        dora::assert_equal(__LINE__, test_accept.value(), 9000);
    };

    // Assign a rvalue
    test_case.pool = [](){
        Integer test_accept;
        test_accept = 5555;
        dora::assert_equal(__LINE__, test_accept.type_name(), "Integer");
        dora::assert_equal(__LINE__, test_accept.value(), 5555);
    };

    test_case.all();
}


void test_conversion()
{
    dora::TestCase test_case(__FILE__, __func__);
    test_case.pool = [](){
        Integer integer1(10);
        int test = integer1;
        dora::assert_true(__LINE__, test == 10);
        int test2 = int(integer1);
        dora::assert_true(__LINE__, test2 == 10);
    };

    test_case.all();
}

void test_compare()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Compare two Integer objects > and <
    test_case.pool = [](){
        Integer i1(10);
        Integer i2(100);
        dora::assert_true(__LINE__, i1 < i2);
        dora::assert_true(__LINE__, i2 > i1);
        // Compare with C++ type_name
        dora::assert_true(__LINE__, i1 < 20);
        dora::assert_true(__LINE__, i2 > 20);
        dora::assert_true(__LINE__, i1 == 10);
        dora::assert_true(__LINE__, i2 == 100);
    };
    
    // Equal ==
    test_case.pool = [](){
        Integer i1(100);
        Integer i2(100);
        dora::assert_true(__LINE__, i1 == i2);
        dora::assert_true(__LINE__, i2 == i1);
    };

    // Not Equal !=
    test_case.pool = [](){
        Integer i1(100);
        Integer i2(200);
        dora::assert_true(__LINE__, i1 != i2);
        dora::assert_true(__LINE__, i2 != i1);
    };

    test_case.all();
}

void test_stream()
{
     dora::TestCase test_case(__FILE__, __func__);

    // Assign an object
    test_case.pool = [](){
        Integer test_accept(66);
        std::cout << test_accept << "\n";
    };

    test_case.all();
}


class TestObject : public object {
public:
    TestObject() {}
};

void test_converint_non_integer_object()
{
     dora::TestCase test_case(__FILE__, __func__);

    // Assign an object
    test_case.pool = [](){
        std::shared_ptr<TestObject> test_ptr (new TestObject());
        // Raise error
        Integer test_accept(test_ptr);
    };

    test_case.all();
}


int main()
{
    test_init();
    test_copy_constructor();

    test_type_method();
    test_value_method();

    test_assignment();
    test_conversion();

    test_compare();
    test_stream();
    test_converint_non_integer_object();
}
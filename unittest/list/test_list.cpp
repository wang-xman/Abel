/* Unittest: list */
#include <iostream>
#include <memory>
#include "dora.hpp"
#include "list.hpp"

using namespace abel;

class TestObject : public object {
public:
    TestObject(){}
    ~TestObject() {}
};

void test_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Default constuctor : Noninit list
    test_case.pool = [](){
        List test_list;
        dora::assert_equal(__LINE__, test_list.type_name(), "List");
        dora::assert_equal(__LINE__, test_list.size(), 0);
    };

    // Constructor : Aggregate init with numeric types
    test_case.pool = [](){
        // 1 -> int, 0.5 -> double
        List test_list {1, 0.5};
        dora::assert_equal(__LINE__, test_list.type_name(), "List");
        dora::assert_equal(__LINE__, test_list.size(), 2);
        // 1.0 -> double, 0.5f -> float
        List test_list_2 {1.0, 0.5f};
        dora::assert_equal(__LINE__, test_list_2.type_name(), "List");
        dora::assert_equal(__LINE__, test_list_2.size(), 2);
    };
    
    // Constructor : init with a list
    test_case.pool = [](){
        List item_list;
        List test_list {1, "Hello", item_list, item_list};
        dora::assert_equal(__LINE__, test_list.type_name(), "List");
        dora::assert_equal(__LINE__, test_list.size(), 4);
    };

    // Constructor : init with shared pointer of list
    test_case.pool = [](){
        List item_list;
        std::shared_ptr<List> list_sptr (new List());
        List test_list {1, "Hello", item_list, list_sptr};
        dora::assert_equal(__LINE__, test_list.type_name(), "List");
        dora::assert_equal(__LINE__, test_list.size(), 4);
    };

    // Constructor : init with share pointer to another object.
    test_case.pool = [](){
        //List item_list;
        std::shared_ptr<TestObject> test_sptr (new TestObject());
        List test_list {test_sptr};
        dora::assert_equal(__LINE__, test_list.type_name(), "List");
        dora::assert_equal(__LINE__, test_list.size(), 1);
    };

    test_case.all();
}

void test_copy_assignment_operator()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Copy assign from a share pointer of object
    test_case.pool = [](){
        List test_list;
        std::shared_ptr<TestObject> test_sptr( new TestObject() );
        // Caution! Must raise error.
        //test_list = test_sptr;
    };

    test_case.all();
};

void test_element_retrieve()
{
    dora::TestCase test_case(__FILE__, __func__);
    test_case.pool = [](){
        List item_list;
        Null test_null;
        List test_list {1, "Hello", item_list, item_list, true, test_null};
        dora::assert_equal(__LINE__, test_list[0]->type_name(), "Integer");
        dora::assert_equal(__LINE__, test_list[1]->type_name(), "Text");
        dora::assert_equal(__LINE__, test_list[2]->type_name(), "List");
        dora::assert_equal(__LINE__, test_list[3]->type_name(), "List");
        dora::assert_equal(__LINE__, test_list[4]->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_list[5]->type_name(), "Null");
    };

    // with boolean and null
    test_case.pool = [](){
        Bool test_bool (false);
        Null test_null;
        List test_list {true, false, test_null, test_bool, 1000};
        dora::assert_equal(__LINE__, test_list[0]->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_list[1]->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_list[2]->type_name(), "Null");
        dora::assert_equal(__LINE__, test_list[3]->type_name(), "Bool");
    };

    test_case.all();
};

void test_internal_get()
{
    dora::TestCase test_case(__FILE__, __func__);
    test_case.pool = [](){
        List item_list;
        Null test_null;
        List test_list {1, "Hello", item_list, item_list, true, test_null};
        dora::assert_equal(__LINE__, test_list.get(0)->type_name(), "Integer");
        dora::assert_equal(__LINE__, test_list.get(1)->type_name(), "Text");
        dora::assert_equal(__LINE__, test_list.get(2)->type_name(), "List");
        dora::assert_equal(__LINE__, test_list.get(3)->type_name(), "List");
        dora::assert_equal(__LINE__, test_list.get(4)->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_list.get(5)->type_name(), "Null");
    };

    // with boolean and null
    test_case.pool = [](){
        Bool test_bool (false);
        Null test_null;
        List test_list {true, false, test_null, test_bool};
        dora::assert_equal(__LINE__, test_list.get(0)->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_list.get(1)->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_list.get(2)->type_name(), "Null");
        dora::assert_equal(__LINE__, test_list.get(3)->type_name(), "Bool");
    };

    test_case.all();
};

void test_list_with_complex_numbers()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        List item_list;
        Complex c {0.5, 10.0};
        List test_list {1, "Hello", item_list, c};
        dora::assert_equal(__LINE__, test_list[0]->type_name(), "Integer");
        dora::assert_equal(__LINE__, test_list[1]->type_name(), "Text");
        dora::assert_equal(__LINE__, test_list[2]->type_name(), "List");
        dora::assert_equal(__LINE__, test_list[3]->type_name(), "Complex");
    };

    test_case.all();
}

void test_list_insert()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        List test_list;
        test_list.insert(0, 1);
        test_list.insert(1, "Hello");
        Complex c {0.5, 10.0};
        test_list.insert(2, c);
        Binary bin("0b10001"); //binary
        test_list.insert(3, bin);
        Bitstring bitstring("_b10001"); // bitstring
        test_list.insert(4, bitstring);
        dora::assert_equal(__LINE__, test_list[0]->type_name(), "Integer");
        dora::assert_equal(__LINE__, test_list[1]->type_name(), "Text");
        dora::assert_equal(__LINE__, test_list[2]->type_name(), "Complex");
        dora::assert_equal(__LINE__, test_list[3]->type_name(), "Binary");
        dora::assert_equal(__LINE__, test_list[4]->type_name(), "Bitstring");
    };

    test_case.all();
}

int main()
{
    test_constructor();
    test_copy_assignment_operator();
    test_element_retrieve();
    test_internal_get();
    test_list_with_complex_numbers();
    test_list_insert();
}
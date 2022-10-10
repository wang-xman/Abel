/* Unittest: tuple */
#include <iostream>
#include <memory>
#include "dora.hpp"
#include "tuple.hpp"

using namespace abel;

class TestObject : public object {
public:
    TestObject(){}
    ~TestObject() {}
};

void test_constructor()
{
    dora::TestCase test_case(__FILE__, __func__);

    // Default constuctor : Noninit tuple
    test_case.pool = [](){
        Tuple test_tuple;
        dora::assert_equal(__LINE__, test_tuple.type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple.size(), 0);
    };

    // Constructor : Aggregate init with numeric types
    test_case.pool = [](){
        // 1 -> int, 0.5 -> double
        Tuple test_tuple {1, 0.5};
        dora::assert_equal(__LINE__, test_tuple.type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple.size(), 2);
        // 1.0 -> double, 0.5f -> float
        Tuple test_tuple_2 {1.0, 0.5f};
        dora::assert_equal(__LINE__, test_tuple_2.type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple_2.size(), 2);
    };
    
    // Constructor : init with a tuple
    test_case.pool = [](){
        Tuple item_tuple;
        Tuple test_tuple {1, "Hello", item_tuple, item_tuple};
        dora::assert_equal(__LINE__, test_tuple.type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple.size(), 4);
    };

    // Constructor : init with shared pointer of tuple
    test_case.pool = [](){
        Tuple item_tuple;
        std::shared_ptr<Tuple> tuple_sptr (new Tuple());
        Tuple test_tuple {1, "Hello", item_tuple, tuple_sptr};
        dora::assert_equal(__LINE__, test_tuple.type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple.size(), 4);
    };

    // Constructor : init with share pointer to another object.
    test_case.pool = [](){
        std::shared_ptr<TestObject> test_sptr (new TestObject());
        Tuple test_tuple {test_sptr};
        dora::assert_equal(__LINE__, test_tuple.type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple.size(), 1);
    };

    test_case.all();
}

void test_element_retrieve()
{
    dora::TestCase test_case(__FILE__, __func__);
    test_case.pool = [](){
        Tuple item_tuple;
        Null test_null;
        List item_list; // list as an item of a tuple
        Tuple test_tuple {1, "Hello", item_tuple, item_tuple, true,
                          test_null, item_list};
        dora::assert_equal(__LINE__, test_tuple[0]->type_name(), "Integer");
        dora::assert_equal(__LINE__, test_tuple[1]->type_name(), "Text");
        dora::assert_equal(__LINE__, test_tuple[2]->type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple[3]->type_name(), "Tuple");
        dora::assert_equal(__LINE__, test_tuple[4]->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_tuple[5]->type_name(), "Null");
        dora::assert_equal(__LINE__, test_tuple[6]->type_name(), "List");
    };

    // with boolean and null
    test_case.pool = [](){
        Bool test_bool (false);
        Null test_null;
        Tuple test_tuple {true, false, test_null, test_bool};
        dora::assert_equal(__LINE__, test_tuple[0]->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_tuple[1]->type_name(), "Bool");
        dora::assert_equal(__LINE__, test_tuple[2]->type_name(), "Null");
        dora::assert_equal(__LINE__, test_tuple[3]->type_name(), "Bool");
    };

    test_case.all();
};

void test_tuple_with_complex_numbers()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        List item_list;
        Complex c {0.5, 10.0};
        Tuple test_tuple {1, "Hello", item_list, c};
        dora::assert_equal(__LINE__, test_tuple[0]->type_name(), "Integer");
        dora::assert_equal(__LINE__, test_tuple[1]->type_name(), "String");
        dora::assert_equal(__LINE__, test_tuple[2]->type_name(), "List");
        dora::assert_equal(__LINE__, test_tuple[3]->type_name(), "Complex");
    };

    test_case.all();
}

int main()
{
    test_constructor();
    test_element_retrieve();
}
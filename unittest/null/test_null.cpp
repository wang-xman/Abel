/* Unittest: null */
#include <iostream>
#include "null.hpp"
#include "dora.hpp"

using namespace abel;

void test_type_method()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Null test_null;
        dora::assert_equal(__LINE__, test_null.type_name(), "Null");
    };
    test_case.all();
}

int main()
{
    test_type_method();
}
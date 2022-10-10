/* Unittest: object */
#include "dora.hpp"
#include "object.hpp"

using namespace abel;

class Person : public object {
    std::string type = "_person_";
public:
    std::string type_name() { return type; }
};

void test_new_object() {
    dora::TestCase test_case(__FILE__, __func__);
    
    // Instantiate a new instance
    test_case.pool = [](){
        Person test;
        dora::assert_equal(__LINE__, test.type_name(), "_person_");
    };

    // Shared pointer
    test_case.pool = [](){
        std::shared_ptr<Person> test_ptr (new Person());
        dora::assert_equal(__LINE__, test_ptr->type_name(), "_person_");
    };

    test_case.all();
}

int main() {
    test_new_object();
    return 0;
}
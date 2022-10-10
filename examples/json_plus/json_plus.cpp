/*
    Example - Parse and load JSON Plus format files
    
    In contrast to standard JSON, JSON+ format allows comments.
    Only need to include abel.hpp header, if the shared library is used.

    The preferred method to access data in containers is cnt::get<T>()
    method.
*/
#include <cassert>
#include "abel.hpp"

void non_enclosed_dictionary()
{
    // Parsing ...
    std::string test_file = "./non_enclosed_dictionary.abel";
    std::ifstream input_file_stream(test_file);
    abel::JsonPlusParser test_parser;
    test_parser.parse(input_file_stream);

    // Load ...
    std::shared_ptr<abel::Dict> global_dictionary ( new abel::Dict() );
    abel::JsonPlusLoader loader;
    loader.load_from_parser(test_parser, global_dictionary);
    // In this case, the content in the file is directly packed
    // into a dictionary. Now, acquire the target dict,
    abel::Dict target_dict = abel::cnt::get<abel::Dict>(
        global_dictionary, "ROOT_KEY_");
    
    // Let's get something from the dictionary.

    // Key "children" corresponds to a dictionary
    abel::Dict children = abel::cnt::get<abel::Dict>(target_dict, "children");
    // And children["key3"] is a list
    abel::List key3;
    key3 = abel::cnt::get<abel::List>(children, "key3");
    // List "key3" has how many elements? Okay 3
    assert (key3.size() == 3);

    // The last element is a dictionary
    abel::Dict key3_last_item = abel::cnt::get<abel::Dict>(key3, 2);
    // Key "int1" in this dictionary stores an integer
    abel::Integer int1;
    int1 = abel::cnt::get<abel::Integer>(key3_last_item, "int1");
    // ... its value is 100
    assert (int1 == 100);
    // ... and it can be assigned to a C++ primitive int type
    int int1_cpp = int1;
    assert (int1_cpp == 100);
    // Inside this dictionary, key "comp2" is a complex number
    abel::Complex comp2 = abel::cnt::get<abel::Complex>(key3_last_item, "comp2");
    assert (comp2.type_name() == "Complex");
}

int main()
{
    non_enclosed_dictionary();
}
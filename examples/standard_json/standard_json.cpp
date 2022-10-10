/*
    Example - Parse and load standard JSON files

    Only need to include abel.hpp header, if the shared library is used.
    The preferred method to access data in containers is cnt::get<T>()
    method.

    The codes in the following are avoid of `using namespace` and consist
    of comments that are rather verbose. They are here to help reader walk
    through a the simple "parsing-loading-getting" procedure. 
*/
#include <cassert>
#include "abel.hpp"

void single_dictionary()
/*
    The JSON file contains one list container.
*/
{
    // Create a input file stream and parse it.
    std::string test_file = "./single_dict.json";
    std::ifstream input_file_stream(test_file);
    abel::JsonParser json_parser;
    json_parser.parse(input_file_stream);
        
    // By default, the content in any JSON file is stored
    // in a dictionary, we create a global dictionary to accept it.
    // Now, use loader to load the parsed dictionary
    std::shared_ptr<abel::Dict> global_dictionary ( new abel::Dict() );
    abel::JsonLoader json_loader;
    json_loader.load_from_parser(json_parser, global_dictionary);

    // The actual content in the JSON file is parsed and
    // stored as an element in the list under the key "ROOT_KEY_"
    // in the global dictionary. Let's check
    assert (abel::cnt::get(global_dictionary, "ROOT_KEY_")->type_name() == "List");

    // Now, acquire the target dictionary from root container
    abel::List root_container;
    root_container = abel::cnt::get<abel::List>(global_dictionary, "ROOT_KEY_");
    abel::Dict target_dict = abel::cnt::get<abel::Dict>(root_container, 0);
    // display the top-level keys the dictionary has
    for (size_t i = 0; i < target_dict.keys().size(); i++) {
        std::cout << target_dict.keys()[i] << std::endl;    
    }

    // Explore the entries in the target dictionary
    std::string firstname = abel::cnt::get<abel::Text>(target_dict, "Firstname")->value();
    std::string surname = abel::cnt::get<abel::Text>(target_dict, "Surname")->value();
    assert (firstname == "Zaphod");
    assert (surname == "Beeblebrox");
    
    // One entry is a list under key "Array"
    abel::List array;
    array = abel::cnt::get<abel::List>(target_dict, "Array");
    // and this list has 3 elements.
    assert (array.size() == 3);
    // the 0th element is a number 2
    assert( 2 == abel::cnt::get<abel::Double>(array, 0)->value() );
    // the 1st element is a dictionary
    assert( "Dict" == abel::cnt::get(array, 1)->type_name() );
    // the 2nd element is a list
    assert( "List" == abel::cnt::get(array, 2)->type_name() );

    // Now, we are interested in the last list
    abel::List sublist;
    sublist = abel::cnt::get<abel::List>(array, 2);
    // which has 2 elements
    assert (sublist.size() == 2);
    // and the last element is "Prefect"
    assert (abel::cnt::get<abel::Text>(sublist, 1)->value() == "Prefect");

}

void single_list()
/*
    The JSON file contains one list container.
*/
{
    // Create a input file stream and parse it.
    std::string test_file = "./single_list.json";
    std::ifstream input_file_stream(test_file);
    abel::JsonParser json_parser;
    json_parser.parse(input_file_stream);
        
    // By default, the content in any JSON file is stored
    // in a dictionary, we create a global dictionary to accept it.
    // Now, use loader to load the parsed dictionary
    std::shared_ptr<abel::Dict> global_dictionary ( new abel::Dict() );
    abel::JsonLoader json_loader;
    json_loader.load_from_parser(json_parser, global_dictionary);

    // The actual content in the JSON file is parsed and
    // stored as an element in the list under the key "ROOT_KEY_"
    // in the global dictionary. Let's check
    assert (abel::cnt::get(global_dictionary, "ROOT_KEY_")->type_name() == "List");

    abel::List root_container;
    root_container = abel::cnt::get<abel::List>(global_dictionary, "ROOT_KEY_");
    // Now, acquire the target lsit from root container
    abel::List target_list;
    target_list = abel::cnt::get<abel::List>(root_container, 0);
    // this list has 2 items
    assert (target_list.size() == 2);

    // Let's dig into the second element of the list, a dictionary
    abel::Dict dict = abel::cnt::get<abel::Dict>(target_list, 1);
    // Key "Country" points to "Germany"
    assert (abel::cnt::get<abel::Text>(dict, "Country")->value() == "Germany");
    // Key "States" of this dictionary points to a number, 16
    assert (abel::cnt::get<abel::Double>(dict, "States")->value() == 16);
}

int main()
{
    single_dictionary();
    single_list();
}
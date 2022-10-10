/* unittest: json_loader */
#include "json_loader.hpp"
#include "dora.hpp"

// As this is a JSON loader, the test is focusing on loading
// the JSON format.

void test_json_loader_single_dict()
/*
    Standard JSON format. One enclosed dictionary in the file.
    The enclosed dictionary is loaded into a global dictionary
    as the first element of the root (container) list, i.e.
        {
            "ROOT_KEY_" : [ { dict in file } ]
        }
*/
{
    dora::TestCase test_case(__FILE__, __func__);
    std::cout << "Testing function: " << __func__ << "\n";

    test_case.pool = []() { // begin test case.

        std::string test_file_name = "./text_files/json/single_dict.json";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
    
        // Root container in this case is a list.
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
    
        /// Load global dictionary
        std::shared_ptr<abel::Dict> global_dict ( new abel::Dict() );
        abel::JsonLoader loader;
        loader.load_from_parser(test_parser, global_dict);
    
        /// Root container is a list
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::List>(global_dict, "ROOT_KEY_")->type_name(),
            "List");

        // First item in the list is the target dictionary.
        abel::Dict target_dict = abel::cnt::get<abel::Dict>(
                abel::cnt::get<abel::List>(global_dict, "ROOT_KEY_"), 0);
        
        dora::assert_equal(__LINE__, target_dict.type_name(), "Dict");

        // Target dictionary looks like this
        // {
        //     "name" : "Foo",
        //     "sublist" : [ "Bar", 0.5e+10, [ false, null ] ]
        // }
        // Read entries in the dictionary.
        // key "name" -> "Foo"
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Text>(target_dict, "name")->type_name(),
                "Text");
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Text>(target_dict, "name")->value(),
                "Foo");
        // key "sublist" -> []
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::List>(target_dict, "sublist")->type_name(),
                "List");

        /// Dive into sublist
        // NOTE: No implicit copy constructor from sptr to List.
        abel::List sublist;
        sublist = abel::cnt::get<abel::List>(target_dict, "sublist");
        dora::assert_equal(__LINE__, sublist.size(), 3);
        // first element is Text
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::Text>(sublist, 0)->value(),
            "Bar");
        // second element is Double
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::Double>(sublist, 1)->value(),
            0.5e+10);
        // third element is a list
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::List>(sublist, 2)->type_name(),
            "List");
    }; // end test case

    test_case.all();
}


void test_jason_loader_single_list()
/*
    JSON file container a list. It is loaded as
    {
        "ROOT_KEY_" : [ [...] ]
    }
*/
{
    dora::TestCase test_case(__FILE__, __func__);
    std::cout << "\n Testing function: " << __func__ << "\n";
    
    test_case.pool = []() {
        std::string test_file_name = "./text_files/json/single_list.json";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
    
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        // acquire the global dictionary
        std::shared_ptr<abel::Dict> global_dict ( new abel::Dict() );
        abel::JsonLoader loader;
        loader.load_from_parser(test_parser, global_dict);

        // acquire target list
        abel::List target_list;
        target_list = abel::cnt::get<abel::List>(
            abel::cnt::get<abel::List>(global_dict, "ROOT_KEY_"), 0);
        
        // target list has 2 elements.
        dora::assert_equal(__LINE__, target_list.size(), 2);

        // first element is a dict
        abel::Dict el1 = abel::cnt::get<abel::Dict>(target_list, 0);
        dora::assert_equal(__LINE__,
           abel::cnt::get<abel::Text>(el1, "Achtnaam")->value(), "Beeblebrox");
        dora::assert_equal(__LINE__,
           abel::cnt::get<abel::Text>(el1, "Voornaam")->value(), "Zaphod");
        // one key in el1 is a list
        dora::assert_equal(__LINE__,
           abel::cnt::get<abel::List>(el1, "Geboortedatum")->type_name(), "List");
        dora::assert_equal(__LINE__,
           abel::cnt::get<abel::List>(el1, "Geboortedatum")->size(), 3);
        
        // second element is a list
        abel::List el2;
        el2 = abel::cnt::get<abel::List>(target_list, 1);
        // list has 3 elements
        dora::assert_equal(__LINE__, el2.size(), 3);
        // last element in list is a list
        dora::assert_equal(__LINE__,
           abel::cnt::get<abel::List>(el2, 2)->size(), 3);
    
    };

    test_case.all();
}

int main()
{
    // JSON
    test_json_loader_single_dict();
    test_jason_loader_single_list();
}
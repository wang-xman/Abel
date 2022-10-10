/* unittest: json_plus_loader */
#include "json_plus_loader.hpp"
#include "dora.hpp"

void test_non_enclosed_dict()
/*
    Non-enclosed dictionary is a dictionary written directly in file
    without outmost layer of braces.
    
    In this test, containers are nested and all JSON+ allowed data
    types are present.

    Caution. This may not be the format acceptable to vanilla JSON.
*/
{
    dora::TestCase test_case(__FILE__, __func__);
    std::cout << "\n Testing function: " << __func__ << "\n";
    
    test_case.pool = []() {
    
        std::string test_file_name = "./text_files/non_enclosed_dict.txt";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonPlusParser test_parser;
        test_parser.parse(input_file_stream);
    
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::Dict);
        // load global dictionary
        std::shared_ptr<abel::Dict> global_dict_sptr ( new abel::Dict() );
        abel::JsonPlusLoader loader;
        loader.load_from_parser(test_parser, global_dict_sptr);

        // Root container is a dictionary
        // type name can be enquired via object
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::object>(global_dict_sptr, "ROOT_KEY_")->type_name(),
            "Dict");
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::Dict>(global_dict_sptr, "ROOT_KEY_")->type_name(),
            "Dict");
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::Dict>(global_dict_sptr, "ROOT_KEY_")->type_name(),
            "Dict");

        // Acquire the target dict
        abel::Dict target_dict
                = abel::cnt::get<abel::Dict>(global_dict_sptr, "ROOT_KEY_");
        
        // Access value in target dict

        // key "name" has value "Fool", type can be enquired via
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::object>(target_dict, "name")->type_name(),
            "Text");
        dora::assert_equal(__LINE__,
            abel::cnt::get<abel::Text>(target_dict, "name")->value(),
            "Fool");
        
        // a subdict is named "children"
        abel::Dict children = abel::cnt::get<abel::Dict>(target_dict, "children");
        // this subdict has a key "key3" that is a list
        abel::List key3_list;
        key3_list = abel::cnt::get<abel::List>(children, "key3");
        // the 3rd element in this list is a dictionary of various
        // data types acceptable to JSON+
        abel::Dict data_types = abel::cnt::get<abel::Dict>(key3_list, 2);
        // inside this data type dictionary, we have
        dora::assert_equal(__LINE__, data_types["double1"]->type_name(), "Double");
        // need to convert, though
        dora::assert_equal(__LINE__, (abel::Double)data_types["double1"], 1.0);
        // a double entry
        dora::assert_equal(__LINE__, data_types["double2"]->type_name(), "Double");
        dora::assert_equal(__LINE__, (abel::Double)data_types["double2"], 1e-10);
        // a boolean entry
        dora::assert_equal(__LINE__, data_types["bool"]->type_name(), "Bool");
        dora::assert_equal(__LINE__, (abel::Bool)data_types["bool"], true);

        // Complex
        dora::assert_equal(__LINE__, data_types["comp1"]->type_name(), "Complex");
        dora::assert_equal(__LINE__,
            (abel::Complex)data_types["comp1"],
            abel::Complex(0.0, 0.5e-10));
        dora::assert_equal(__LINE__,
            (abel::Complex)data_types["comp2"],
            abel::Complex(1.0, -0.1));
        
        dora::assert_equal(__LINE__, data_types["bin2"]->type_name(), "Binary");
        dora::assert_equal(__LINE__,
            (abel::Binary)data_types["bin2"], // calls copy-constructor on object
            abel::Binary("0b00"));
        dora::assert_equal(__LINE__,
            (abel::Binary)data_types["bin1"], // calls copy-constructor on object
            abel::Binary("0b01000"));

        dora::assert_equal(__LINE__, data_types["bstr1"]->type_name(), "Bitstring");
        dora::assert_equal(__LINE__,
            (abel::Bitstring)data_types["bstr1"],
            abel::Bitstring("_b0110"));

        dora::assert_equal(__LINE__, data_types["bstr2"]->type_name(), "Bitstring");
        dora::assert_equal(__LINE__,
            (abel::Bitstring)data_types["bstr2"],
            abel::Bitstring("_b0.11"));
    };

    test_case.all();
}


/*
    Enclosed dictionary is a dictionary packed in a pair of braces.
    Inside the root dictionary, it is stored as an element of a list
    associated with key ROOT_KEY_.
    In general, delimited text block appearing in the highest level in
    the text file is considered as an element of a list.
*/
void test_enclosed_dict()
{
    dora::TestCase test_case(__FILE__, __func__);
    std::cout << "\n Testing function: " << __func__ << "\n";

    test_case.pool = []() { // begin test case.
        std::string test_file_name = "./text_files/enclosed_dict.txt";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonPlusParser test_parser;
        test_parser.parse(input_file_stream);
        //test_parser.display();
    
        // Root object in this case is a list.
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(), abel::JsonContainerType::List);
    
        /// Load root dictionary
        std::shared_ptr<abel::Dict> root_dict_sptr ( new abel::Dict() );
        abel::JsonPlusLoader loader;
        loader.load_from_parser(test_parser, root_dict_sptr);
    
        /// Root object ///
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::List>(root_dict_sptr, "ROOT_KEY_")->type_name(),
                "List");
        
        /// First item in the list is a dict, which is desired one. ///
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Dict>(
                    abel::cnt::get<abel::List>(root_dict_sptr, "ROOT_KEY_"),
                    0)->type_name(),
                "Dict");
    
        /// Read the desired dict, call it first dict.///
        abel::Dict first_dict = abel::cnt::get<abel::Dict>(
                abel::cnt::get<abel::List>(root_dict_sptr, "ROOT_KEY_"), 0);
    
        /// Read items in the first dict
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Text>(first_dict, "name")->type_name(),
                "Text");
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Text>(first_dict, "name")->value(),
                "Foo");
        /// Read the list in the first dict
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::List>(first_dict, "sublist")->type_name(),
                "List");
        /// Dive into sublist ///
        abel::List sublist;
        sublist = abel::cnt::get<abel::List>(first_dict, "sublist");
    
        dora::assert_equal(__LINE__, sublist.size(), 9);
        // first element is String
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Text>(sublist, 0)->value(), "Bar");
        // second element is Double
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Double>(sublist, 1)->value(), 0.5e+10);
        // third element is Bool
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Bool>(sublist, 2)->value(), false);
        // fourth element is Null
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Null>(sublist, 3)->type_name(), "Null");
        // fifth element is integer
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Integer>(sublist, 4)->value(), 2101);
        // sixth element is Double
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::Double>(sublist, 5)->value(), 0.005);
        // 7th element is Complex
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::object>(sublist, 6)->type_name(), "Complex");
        // 8th element is Binary
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::object>(sublist, 7)->type_name(), "Binary");
        // 9th element is Bitstring
        dora::assert_equal(__LINE__,
                abel::cnt::get<abel::object>(sublist, 8)->type_name(), "Bitstring");

        // Test complex number
        abel::Complex comp = abel::cnt::get<abel::Complex>(sublist, 6);
        dora::assert_equal(__LINE__, comp.real(), 0.5e-10);
        dora::assert_equal(__LINE__, comp.imag(), 1.0e-7);

        /// Dive into key "vector" ///
        abel::List veclist;
        veclist = abel::cnt::get<abel::List>(first_dict, "vector");
        for (int i = 0; i < 4; i++) {
            std::cout << abel::cnt::get<abel::object>(veclist, i)->type_name();
        }
        // assigned to a std::vector
        std::vector<double> vec = veclist.as_vector_double();
        // compare elements
        dora::assert_equal(__LINE__, vec[0], 0.5e+10);
        dora::assert_equal(__LINE__, vec[1], 2101);
        dora::assert_equal(__LINE__, vec[2], 0.005);
        dora::assert_equal(__LINE__, vec[3], 700);
    
        /// Dive into key "vector2" ///
        abel::List vec2;
        vec2 = abel::cnt::get<abel::List>(first_dict, "vector2");
        vec = vec2.as_vector_double();
        dora::assert_equal(__LINE__, vec[0], 1.2);
        dora::assert_equal(__LINE__, vec[1], 10.5);
        dora::assert_equal(__LINE__, vec[2], 0.7);
        // Force conversion to int, then loss of precision.
        std::vector<int> vec_int = vec2.as_vector_int();
        dora::assert_equal(__LINE__, vec_int[0], 1);
        dora::assert_equal(__LINE__, vec_int[1], 10);
        dora::assert_equal(__LINE__, vec_int[2], 0);
    
        /// Dive into key "vecstr" ///
        abel::List vecstr;
        vecstr = abel::cnt::get<abel::List>(first_dict, "vecstr");
        std::vector<std::string>stdvecstr = vecstr.as_vector_string();
        dora::assert_equal(__LINE__, stdvecstr[0], "Europe");
        dora::assert_equal(__LINE__, stdvecstr[1], "105");
        dora::assert_equal(__LINE__, stdvecstr[2], "Quote\"ha");
    }; // end test case

    test_case.all();
}

int main()
{
/// Non-enclosed objects are stored in a dictionary
    test_non_enclosed_dict();

/// Enclosed object is stored as an item in list.
    test_enclosed_dict();
}
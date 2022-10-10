/* unittest: parser_json */
#include "json_parser.hpp"
#include "dora.hpp"

void test_parse_string()
/*
    JSON parser can parse a JSON format packed into a string.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    // a simple dictionary with line breaking symbol
    test_case.pool = []() {
        std::string test_string = "{ \
            \"MOV\": \"REGISTER\", \
            \"ADD\": 5, \
            \"SUB\": \"hello\" \
        }";
        abel::JsonParser test_parser;
        test_parser.parse(test_string);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };
    
    // a simple dictionary without explicit line breaking.
    // result is indentical to the above.
    test_case.pool = []() {
        std::string test_string = "{ "
            "\"MOV\": \"REGISTER\", "
            "\"ADD\": 5, "
            "\"SUB\": \"hello\" "
        "}";
        abel::JsonParser test_parser;
        test_parser.parse(test_string);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };
    
    // should throw error
    test_case.pool = []() {
        std::string test_string = " ";
        abel::JsonParser test_parser;
        test_parser.parse(test_string);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        //test_parser.display();
    };

    // with nested containers
    test_case.pool = []() {
        std::string test_string = "{ \
            \"MOV\": \"REGISTER\", \
            \"ADD\": [5, 10, 100], \
            \"SUB\": { \
                \"numbers\": [0.1, 1e-10], \
                \"ops\": [\"Subtract\", \"Sub\"] \
            } \
        }";
        abel::JsonParser test_parser;
        test_parser.parse(test_string);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };

    test_case.all();
}

void test_json_simple_dict()
/*
    JSON format. Entire dictionary is stored as an element of a list
    associated with key `ROOT_KEY_`.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_file_name = "./text_files/json/simple_dict.json";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };

    test_case.all();
}

void test_json_nested_lists()
/*
    JSON format. Entire dictionary is stored as an element of a list
    associated with key `ROOT_KEY_`.

    Testing file is a deeply nested container.
    Lists consist of inhomogeneous types, too.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_file_name = "./text_files/json/nested_lists.json";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };

    test_case.all();
}

// Liberal JSON-like format. Comments are allowed.

void test_simple_dict_with_comments()
/*
    Enclosed dictionary is a dictionary with braces.

    Entire dictionary is sotred inside a global dictionary and given
    a key `"ROOT_KEY_"`.

    Comments are allowed.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_file_name
                = "./text_files/liberal/simple_dict_with_comments.txt";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };

    test_case.all();
}


void test_nonembraced_dict()
/*
    Dictionary in file is without opening and closing embraces.

    Entire file is stored inside a global dictionary and given
    a key `"ROOT_KEY_"`, i.e.
    {
        "ROOT_KEY_" : {
            Content from input file
        }
    }

    Comments are allowed.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_file_name = "./text_files/liberal/nonembraced_dict.txt";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(), abel::JsonContainerType::Dict);
        test_parser.display();
    };

    test_case.all();
}

void test_mixed_containers_terminals()
/*
    Mixture of container and terminal types in one file. All items in
    the file are stored in a list, i.e.,
    {
        "ROOT_KEY_" : [
            Items in the file
        ]
    }

    At the file level, each item separated by comma will be
    considered as an element of the list.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_file_name = "./text_files/liberal/mixed_containers_terminals.txt";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonParser test_parser;
        test_parser.parse(input_file_stream);
        dora::assert_equal(__LINE__,
            test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };

    test_case.all();
}

int main()
{
    // Parsing strings directly
    test_parse_string();

    // Parses JSON files 
    test_json_simple_dict();
    test_json_nested_lists();
    
    // Parse liberal JSON-like format
    test_simple_dict_with_comments();
    test_nonembraced_dict();
    test_mixed_containers_terminals();
}
/* unittest: json_plus_parser */
#include "json_plus_parser.hpp"
#include "dora.hpp"

void test_extended_data_types()
/*
    Test extended datatype recognition.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_file_name = "./text_files/extended_datatypes.txt";
        std::ifstream input_file_stream(test_file_name);
        abel::JsonPlusParser test_parser;
        test_parser.parse(input_file_stream);
        dora::assert_equal(__LINE__, test_parser.get_root_container_type(),
            abel::JsonContainerType::List);
        test_parser.display();
    };

    test_case.all();
}

/*
* Test Abel parser on JSON style.
*/
void test_mixed_containers_terminals()
/*
    Parses a file contains containers and terminals.
*/
{
    std::cout << "\n\n" << __func__ << "\n";
    dora::TestCase test_case(__FILE__, __func__);

    std::string test_file_name = "./text_files/mixed_containers_terminals.txt";
    std::ifstream input_file_stream(test_file_name);
    abel::JsonPlusParser test_parser;
    test_parser.parse(input_file_stream);
    dora::assert_equal(__LINE__, test_parser.get_root_container_type(),
        abel::JsonContainerType::List);
    test_parser.display();
}

int main()
{
    // extended data types
    test_extended_data_types();   
    test_mixed_containers_terminals();
}
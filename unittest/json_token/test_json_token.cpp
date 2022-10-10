/* Unittest: json_token */
#include "json_token.hpp"
#include "dora.hpp"

void test_tokenizers()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    // non iter-key token
    test_case.pool = [](){
        abel::JsonToken test_token = abel::tokenize_key(
            "Alpha", abel::JsonTokenType::Key,
            "ROOT",
            1,
            100,
            abel::JsonContainerType::List,
            abel::LiteralScheme::Liberal);
        dora::assert_equal(__LINE__, test_token.literal, "Alpha");
        dora::assert_equal(__LINE__, test_token.type, abel::JsonTokenType::Key);
        dora::assert_equal(__LINE__, test_token.parent_key, "ROOT");
        dora::assert_equal(__LINE__, test_token.level, 1);
        dora::assert_equal(__LINE__, test_token.line, 100);
        // raises error if use it for iter_key
        //abel::Token test_iter_token = abel::tokenize("Alpha", "Iter_Key", "ROOT", 1, 100);
    };
    
    // iter-key token
    test_case.pool = [](){
        abel::JsonToken test_token = abel::tokenize_iter_key(
                "Alpha",
                abel::JsonTokenType::IterKey,
                "ROOT", 1, 100,
                abel::JsonContainerType::Dict,
                9);
        dora::assert_equal(__LINE__, test_token.literal, "Alpha");
        dora::assert_equal(__LINE__, test_token.type, abel::JsonTokenType::IterKey);
        dora::assert_equal(__LINE__, test_token.parent_key, "ROOT");
        dora::assert_equal(__LINE__, test_token.level, 1);
        dora::assert_equal(__LINE__, test_token.line, 100);
        dora::assert_equal(__LINE__, test_token.iter_index, 9);
    };

    test_case.all();
}

void test_get_token_type()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        dora::assert_equal(__LINE__,
            abel::JsonTokenType::DictOpening,
            abel::get_token_type_by_symbol(abel::symbol::L_BRACE));
        
        dora::assert_equal(__LINE__,
            abel::JsonTokenType::DictClosing,
            abel::get_token_type_by_symbol(abel::symbol::R_BRACE));

        dora::assert_equal(__LINE__,
            abel::JsonTokenType::ListOpening,
            abel::get_token_type_by_symbol(abel::symbol::L_BRACKET));
        
        dora::assert_equal(__LINE__,
            abel::JsonTokenType::ListClosing,
            abel::get_token_type_by_symbol(abel::symbol::R_BRACKET));
    };
    test_case.all();
}

void test_get_container_type()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        dora::assert_equal(__LINE__,
            abel::JsonContainerType::Dict,
            abel::get_container_type_by_symbol(abel::symbol::L_BRACE));
        
        dora::assert_equal(__LINE__,
            abel::JsonContainerType::List,
            abel::get_container_type_by_symbol(abel::symbol::L_BRACKET));
    };
    test_case.all();
}

void test_iterable_container()
{
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        dora::assert_equal(__LINE__,
            true,
            abel::is_iterable_container(abel::JsonContainerType::List));
        
        dora::assert_equal(__LINE__,
            false,
            abel::is_iterable_container(abel::JsonContainerType::Dict));
    };
    test_case.all();
}

int main()
{
    test_tokenizers();
    test_get_token_type();
    test_get_container_type();
}
/* Unittest: symbol */
#include "symbol.hpp"
#include "dora.hpp"

void test_named_symbols() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        dora::assert_equal(__LINE__, abel::symbol::L_BRACE, "{");
        dora::assert_equal(__LINE__, abel::symbol::R_BRACE, "}");
        dora::assert_equal(__LINE__, abel::symbol::L_BRACKET, "[");
        dora::assert_equal(__LINE__, abel::symbol::R_BRACKET, "]");
        dora::assert_equal(__LINE__, abel::symbol::L_PARENTHESIS, "(");
        dora::assert_equal(__LINE__, abel::symbol::R_PARENTHESIS, ")");
        dora::assert_equal(__LINE__, abel::symbol::L_CHEVRON, "<");
        dora::assert_equal(__LINE__, abel::symbol::R_CHEVRON, ">");
    };

    test_case.all();
}

int main() {
    test_named_symbols();
}
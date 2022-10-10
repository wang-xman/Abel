/* Unittest: util */
#include "util.hpp"
#include "dora.hpp"

void test_remove_space()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_string = "a b   cd    e  f";
        std::string result = "abcdef";
        abel::util::remove_space(test_string); 
        dora::assert_equal(__LINE__, test_string, result);
    };

    test_case.pool = []() {
        std::string test_string = "10 \\ * \"";
        std::string result = "10\\*\"";
        abel::util::remove_space(test_string); 
        dora::assert_equal(__LINE__, test_string, result);
    };

    test_case.all();
}

void test_has_letter()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_string = "a b   cd    e  f";
        dora::assert_true(__LINE__, abel::util::has_letter(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "10 \\ * \""; // no
        dora::assert_false(__LINE__, abel::util::has_letter(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "18&094$?"; // no
        dora::assert_false(__LINE__, abel::util::has_letter(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "1809x4$?"; // yes
        dora::assert_true(__LINE__, abel::util::has_letter(test_string));
    };

    test_case.all();
}

void test_begins_with_letter()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_string = "a b   cd    e  f";
        dora::assert_true(__LINE__, abel::util::begins_with_letter(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "10 \\ * \""; // no
        dora::assert_false(__LINE__, abel::util::begins_with_letter(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "18&094$?"; // no
        dora::assert_false(__LINE__, abel::util::begins_with_letter(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "   a1809x4$?"; // no
        dora::assert_false(__LINE__, abel::util::begins_with_letter(test_string));
    };

    test_case.all();
}

void test_begins_with_sign()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_string = "+a b   cd    e  f"; // yes
        dora::assert_true(__LINE__, abel::util::begins_with_sign(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "- 10 \\ * \""; // yes
        dora::assert_true(__LINE__, abel::util::begins_with_sign(test_string));
    };

    test_case.pool = []() {
        std::string test_string = " - 18&094$?"; // no
        dora::assert_false(__LINE__, abel::util::begins_with_sign(test_string));
    };

    test_case.pool = []() {
        std::string test_string = "  + a1809x4$?"; // no
        dora::assert_false(__LINE__, abel::util::begins_with_sign(test_string));
    };

    test_case.all();
}

void test_is_string_algebraic_operator()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        std::string test_string = "+"; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = "-"; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = "*"; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = "/"; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = "+/"; // no
        dora::assert_false(__LINE__, abel::util::is_algebraic_operator(test_string));
    };

    test_case.all();
}

void test_is_char_algebraic_operator()
{
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        char test_string = '+'; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = '-'; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = '*'; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = '/'; // yes
        dora::assert_true(__LINE__, abel::util::is_algebraic_operator(test_string));
        test_string = '&'; // no
        dora::assert_false(__LINE__, abel::util::is_algebraic_operator(test_string));
    };

    test_case.all();
}

void test_static_symbols()
{
    dora::TestCase test_case(__FILE__, __func__);

    // dict symbols
    test_case.pool = []() {
        std::string sym;
        sym = "{";
        dora::assert_true(__LINE__, abel::util::is_opening_symbol(sym));
        dora::assert_false(__LINE__, abel::util::is_closing_symbol(sym));
        sym = "}";
        dora::assert_false(__LINE__, abel::util::is_opening_symbol(sym));
        dora::assert_true(__LINE__, abel::util::is_closing_symbol(sym));
    };

    // list symbols
    test_case.pool = []() {
        std::string sym;
        sym = "[";
        dora::assert_true(__LINE__, abel::util::is_opening_symbol(sym));
        dora::assert_false(__LINE__, abel::util::is_closing_symbol(sym));
        sym = "]";
        dora::assert_false(__LINE__, abel::util::is_opening_symbol(sym));
        dora::assert_true(__LINE__, abel::util::is_closing_symbol(sym));
    };

    test_case.pool = []() {};
    test_case.all();
}

void test_container_type_string() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        std::string type_str;
        type_str = "Dict";
        dora::assert_false(__LINE__, abel::util::is_iterable_container(type_str));
        type_str = "List";
        dora::assert_true(__LINE__, abel::util::is_iterable_container(type_str));
    };

    test_case.all();
}

void test_getters() {
    dora::TestCase test_case(__FILE__, __func__);
    
    // get closing symbol
    test_case.pool = []() {
        dora::assert_equal(__LINE__, "}", abel::util::get_closing_symbol_by_opening("{"));
        dora::assert_equal(__LINE__, "]", abel::util::get_closing_symbol_by_opening("["));
    };
    test_case.all();
}

int main() {
    test_remove_space();
    test_has_letter();
    test_begins_with_letter();
    test_begins_with_sign();
    test_is_string_algebraic_operator();
    test_is_char_algebraic_operator();

    test_static_symbols();
    test_container_type_string();
    test_getters();
}
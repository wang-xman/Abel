/* unittest: delimiter */
#include "delimiter.hpp"
#include "dora.hpp"

void test_same_pairs() {
    dora::TestCase test_case(__FILE__, __func__);
    
    // same opneing-closing pair. all matched.
    test_case.pool = [](){
        std::string test_string = "{0x{1a}2b{3c{4d}5}6z}";
        // declare a match maker
        abel::DelimiterMatch match_maker;
        match_maker.scan(test_string);
        dora::assert_true(__LINE__, match_maker.are_all_matched());
        // total number of matched pairs
        dora::assert_equal(__LINE__, match_maker.number_of_matched_pairs(), 4);
    };

    // same opneing-closing pair. partially matched.
    test_case.pool = [](){
        // only last two pairs are matched
        std::string test_string = "{0x{1a2b{3c{4d}5}6z";
        // declare a match maker
        abel::DelimiterMatch match_maker;
        match_maker.scan(test_string);
        dora::assert_false(__LINE__, match_maker.are_all_matched());
        // total number of matched pairs
        dora::assert_equal(__LINE__, match_maker.number_of_matched_pairs(), 2);
    };

    test_case.all();
}

void test_mixed_pairs() {
    dora::TestCase test_case(__FILE__, __func__);
    
    // same opneing-closing pair. all matched.
    test_case.pool = [](){
        std::string test_string = "(0x[1a]2b{3c[4d]5}6z)";
        // declare a match maker
        abel::DelimiterMatch match_maker;
        match_maker.scan(test_string);
        dora::assert_true(__LINE__, match_maker.are_all_matched());
        // total number of matched pairs
        dora::assert_equal(__LINE__, match_maker.number_of_matched_pairs(), 4);
    };

    // same opneing-closing pair. partially matched.
    test_case.pool = [](){
        // only last two pairs are matched
        std::string test_string = "{0x{1a2b[3c(4d)5]6z";
        // declare a match maker
        abel::DelimiterMatch match_maker;
        match_maker.scan(test_string);
        dora::assert_false(__LINE__, match_maker.are_all_matched());
        // total number of matched pairs
        dora::assert_equal(__LINE__, match_maker.number_of_matched_pairs(), 2);
    };

    test_case.all();
}

int main(){
    test_same_pairs();
    test_mixed_pairs();
}
/* Unittest: container */
#include <iostream>
#include "dora.hpp"
#include "container.hpp"

using namespace abel;

// Test List method `insert`
void test_list_insert() {
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        List test_list; // empty
        dora::assert_equal(__LINE__, test_list.size(), 0); // size 0
        test_list.insert(0, 100); // insert at index 0
        dora::assert_equal(__LINE__, test_list.size(), 1); // size 1
        test_list.insert(0, "World"); // insert at index 0
        dora::assert_equal(__LINE__, test_list.size(), 2); // size 2
        Dict test_dict;
        test_list.insert(0, test_dict); // insert a dict
        dora::assert_equal(__LINE__, test_list.size(), 3); // size 3
        std::shared_ptr<Dict> dict_sptr = std::make_shared<Dict>();
        test_list.insert(0, dict_sptr); // insert a shared pointer of dict
        dora::assert_equal(__LINE__, test_list.size(), 4); // size 3
    };

    test_case.all();
}

// Test container get function on list
void test_get_on_list() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Dict test_dict {"d1", 200.0}; // element
        List sublist {test_dict, "Hello"}; // [test_dict, "Hello"]
        List test_list {sublist, 1000}; // [[test_dict, "Hello"], 1000]
        test_list.insert(2, "World");
        test_list.insert(3, 1e-10); // [[test_dict, "Hello"], 1000, "World", 1e-10]

        dora::assert_equal(__LINE__,
            cnt::get(test_list, 0)->type_name(), // get into default type abel::object
            "List");
        dora::assert_equal(__LINE__,
            cnt::get<List>(test_list, 0)->type_name(),
            "List");

        dora::assert_equal(__LINE__,
            cnt::get(test_list, 1)->type_name(), // get into default type
            "Integer");
         dora::assert_equal(__LINE__,
            (Integer)cnt::get(test_list, 1), // get into default type and convert
            1000);
        dora::assert_equal(__LINE__,
            cnt::get<Integer>(test_list, 1)->type_name(),
            "Integer");

        dora::assert_equal(__LINE__,
            cnt::get<Text>(test_list, 2)->type_name(),
            "Text");
        dora::assert_equal(__LINE__,
            (Text)cnt::get(test_list, 2), // get into default, then converted
            "World");
        dora::assert_equal(__LINE__,
            (Double)cnt::get(test_list, 3),
            1e-10);

        List acq_sublist { cnt::get<List>(test_list, 0) }; // sublist
        dora::assert_equal(__LINE__,
            cnt::get(acq_sublist, 0)->type_name(),
            "Dict");
        dora::assert_equal(__LINE__,
            ((Dict)cnt::get(acq_sublist, 0)).type_name(),
            "Dict");
        dora::assert_equal(__LINE__,
            cnt::get<Dict>(acq_sublist, 0)->type_name(),
            "Dict");
        
        dora::assert_equal(__LINE__, cnt::get<Text>(acq_sublist, 1)->type_name(), "Text");
    };

    test_case.all();
}

void test_set_on_list() {
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        List test_list; // empty list
        Integer inte {100};
        cnt::set(test_list, 0, inte); // sets an integer at index 0
        dora::assert_equal(__LINE__, test_list.size(), 1);
        dora::assert_equal(__LINE__, Integer(cnt::get<Integer>(test_list, 0)), 100);

        cnt::set(test_list, 0, "World"); // set a rvalue at index 0
        dora::assert_equal(__LINE__, test_list.size(), 2); // size becomes 2
        dora::assert_equal(__LINE__, Text(cnt::get<Text>(test_list, 0)), "World");
        // integer is down-pushed to 1
        dora::assert_equal(__LINE__, Integer(cnt::get<Integer>(test_list,1)), 100);

        Dict test_dict;
        cnt::set(test_list, 0, test_dict); // sets a dictionary at 0.
        dora::assert_equal(__LINE__, test_list.size(), 3); // size becomes 3
        dora::assert_equal( // dict is at 0
            __LINE__, cnt::get<Dict>(test_list, 0)->type_name(), "Dict");
        dora::assert_equal( // text is down-pushed to 1
            __LINE__, Text(cnt::get<Text>(test_list, 1)), "World");
        dora::assert_equal( // integer is down-pushed to 2
            __LINE__, Integer(cnt::get<Integer>(test_list, 2)), 100);

        std::shared_ptr<Bool> bool_ptr = std::make_shared<Bool>(false);
        cnt::set(test_list, 1, bool_ptr); // sets a Bool at 1.
        dora::assert_equal( // dict stays at 0
            __LINE__, cnt::get<Dict>(test_list, 0)->type_name(), "Dict");
        dora::assert_equal( // bool at 1
            __LINE__, cnt::get<Bool>(test_list, 1)->type_name(), "Bool");
        dora::assert_equal( // text is down-pushed to 2
            __LINE__, Text(cnt::get<Text>(test_list, 2)), "World");
        dora::assert_equal( // integer is down-pushed to 3
            __LINE__, Integer(cnt::get<Integer>(test_list, 3)), 100);
    };

    test_case.all();
}

// Tuple
void test_set_on_tuple() {
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        Tuple test_tuple; // empty tuple
        dora::assert_equal(__LINE__, test_tuple.size(), 0);

        Integer inte {100};
        cnt::set(test_tuple, 0, inte); // sets at index 0
        dora::assert_equal(__LINE__, test_tuple.size(), 1);
        
        cnt::set(test_tuple, 0, "World"); // sets at index 0
        dora::assert_equal(__LINE__, test_tuple.size(), 2); // size 2
        dora::assert_equal(__LINE__, Text(cnt::get<Text>(test_tuple, 0)), "World");
        // integer is pushed to index 1
        dora::assert_equal(__LINE__, Integer(cnt::get<Integer>(test_tuple, 1)), 100);

        Dict test_dict;
        cnt::set(test_tuple, 0, test_dict); // set a Dict at 0.
        dora::assert_equal(__LINE__, test_tuple.size(), 3); // size 3
        dora::assert_equal( // dict is at 0
            __LINE__, cnt::get<Dict>(test_tuple, 0)->type_name(), "Dict");
        dora::assert_equal( // text is pushed down to 1
            __LINE__, Text(cnt::get<Text>(test_tuple, 1)), "World");
        dora::assert_equal( // integer is pushed to 2
            __LINE__, Integer(cnt::get<Integer>(test_tuple, 2)), 100);
    };

    test_case.all();
}

void test_get_on_tuple() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Dict test_dict {"d1", 200.0};
        int int1 = 1000;
        Tuple subtuple {test_dict, "Hello"};
        Tuple test_tuple {subtuple, 1000};
        dora::assert_equal(
            __LINE__,
            cnt::get<Tuple>(test_tuple, 0)->type_name(), "Tuple");
        std::shared_ptr<Tuple> tuple_sptr = cnt::get<Tuple>(test_tuple, 0);
        // Caution! Type is double.
        dora::assert_equal(
            __LINE__,
            cnt::get<Double>(cnt::get<Dict>(tuple_sptr,0), "d1")->value(), 200.0);
        /// keyed access via get
        dora::assert_equal(
            __LINE__,
            cnt::get<Double>(cnt::get<Dict>(tuple_sptr,0), "d1")->value(), 200.0);
    };

    test_case.all();
}

void test_set_on_dict() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Dict root_dict; // empty dict
        Dict subdict; // an empty subdict
        cnt::set<Dict>(root_dict, "subdict", subdict); // set sub in root
        dora::assert_equal(__LINE__, root_dict.keys().size(), 1); // has 1 key
        cnt::set<std::string>(root_dict, "text", "hello, world"); // set text in root
        dora::assert_equal(__LINE__, root_dict.keys().size(), 2); // has 2 keys
        cnt::set<int>(root_dict, "int", 100); // set int in root
        dora::assert_equal(__LINE__, root_dict.keys().size(), 3); // has 3 keys
    };

    test_case.all();
}

// Dict
void test_get_on_dict() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = []() {
        Dict root_dict;
        Dict subdict;

        cnt::set<Dict>(root_dict, "subdict", subdict); // set sub in root
        dora::assert_equal(__LINE__, root_dict.keys().size(), 1); // has 1 key
        // get subdict as shared_ptr
        std::shared_ptr<Dict> subdict_ptr = cnt::get<Dict>(root_dict, "subdict");
    
        Dict sub2dict; // another subdict
        cnt::set(subdict_ptr, "sub2dict", sub2dict); // sets in subdict via ptr
        /*
            Now root = {
                "subdict" : {
                    "sub2dict" : sub2dict
                }
            }
        */

    /// Inner get is on a Dict object; outer is on a shared_ptr<Dict>
        std::shared_ptr<Dict> sub2dict_sptr = cnt::get<Dict>(subdict_ptr, "sub2dict");
        cnt::set(sub2dict_sptr, "int1", 1000);
        std::shared_ptr<Dict> sub2dict_sptr2 = cnt::get<Dict>(subdict_ptr, "sub2dict");
        cnt::set(sub2dict_sptr2, "int2", 2000);
        /*
            Now root = {
                "subdict" : {
                    "sub2dict" : {
                        "int1": 1000,
                        "int2": 2000
                    }
                }
            }
        */
    
        /// Access from root dict
        dora::assert_equal(
            __LINE__,
            Integer(cnt::get<Integer>(
                cnt::get<Dict>(cnt::get<Dict>(root_dict, "subdict"), "sub2dict"),
                "int1")),
            1000);
        dora::assert_equal(
            __LINE__,
            Integer(cnt::get<Integer>(
                cnt::get<Dict>(cnt::get<Dict>(root_dict, "subdict"), "sub2dict"),
                "int2")),
            2000);
    };

    test_case.all();
}

int main()
{
    // List
    test_list_insert();
    test_get_on_list();
    test_set_on_list();
    // Tuple
    test_set_on_tuple();
    test_get_on_tuple();
    // Dict
    test_set_on_dict();
    test_get_on_dict();
}
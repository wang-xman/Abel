/* Unit test: dict */
#include <iostream>
#include "dora.hpp"
#include "dict.hpp"

using namespace abel;


class TestObject : public object {
public:
    TestObject() {}
};

void test_constructor() {
    dora::TestCase test_case(__FILE__, __func__);
    
    // default ctor
    test_case.pool = [](){
        Dict test_dict;
        dora::assert_equal(__LINE__, test_dict.type_name(), "Dict");
    };

    // copy constructor
    test_case.pool = [](){
        Dict test_dict;
        Dict test2 (test_dict);
        dora::assert_equal(__LINE__, test2.type_name(), "Dict");
    };

    // copy constructor aggregate init
    test_case.pool = [](){
        Dict test_dict;
        Dict test2 {test_dict};
        dora::assert_equal(__LINE__, test2.type_name(), "Dict");
    };

    // copy constructor from shared ptr
    test_case.pool = [](){
        std::shared_ptr<Dict> test_dict (new Dict());
        Dict test2 {test_dict};
        dora::assert_equal(__LINE__, test2.type_name(), "Dict");
    };

    // copy constructor from non-dict object, raise error
    test_case.pool = [](){
        std::shared_ptr<TestObject> test_ptr (new TestObject());
        // Raise error.
        //Dict test2 {test_ptr};
        //dora::assert_equal(__LINE__, test2.type_name(), "Dict");
    };

    test_case.all();
};


void test_direct_init_with_primitive_types() {
    dora::TestCase test_case(__FILE__, __func__);

    // Init with parenthesis
    test_case.pool = [](){
        Dict test_dict ("k1", 1, "k2",2);
        Integer k1;
        k1 = test_dict["k1"];
        dora::assert_true(__LINE__, k1==1);
        dora::assert_false(__LINE__, k1!=1);
        dora::assert_equal(__LINE__, k1, 1);  
    };

    // Init with aggregate
    test_case.pool = [](){
        Dict test_dict {"k1", 1, "k2", 2};
        Integer k2;
        k2 = test_dict["k2"];
        dora::assert_true(__LINE__, k2 == 2);
    };

    // init with aggregate and boolean and null
    test_case.pool = [](){
        Bool b2 (false);
        Null n3;
        Dict test_dict {"b1", true, "b2", b2, "n3", n3};
        Bool bool_accept;
        bool_accept = test_dict["b1"];
        dora::assert_true(__LINE__, bool_accept == true);
        bool_accept = test_dict["b2"];
        dora::assert_true(__LINE__, bool_accept == false);
    };

    test_case.all();
}

void test_direct_init_with_numeric_objects() {
    dora::TestCase test_case(__FILE__, __func__);
    
    // Direct init with object as value
    test_case.pool = [](){
        Integer i1 (10);
        Double f2 (1e-10);
        Double d4 (0.5);
        Dict test_dict {"k1", i1, "k2", f2, "k4", d4};
        // key access
        Integer k1;
        k1 = test_dict["k1"];
        dora::assert_equal(__LINE__, k1, 10);
        dora::assert_true(__LINE__, k1==10);
        dora::assert_equal(__LINE__, k1, i1);
        dora::assert_true(__LINE__, k1==i1);
        // float
        Double k2;
        k2 = test_dict["k2"];
        // FIXME Assert equal fails, but assert true using == is okay.
        dora::assert_true(__LINE__, k2==f2);
        // double
        Double k4;
        k4 = test_dict["k4"];
        dora::assert_equal(__LINE__, k4, 0.5);
        dora::assert_true(__LINE__, k4==0.5);
        dora::assert_equal(__LINE__, k4, d4);
        dora::assert_true(__LINE__, k4==d4);
        
    };
    
    // Direct init with complex type
    test_case.pool = [](){
        Integer i1 (10);
        Double f2 (1e-10);
        Double d3 (0.5);
        Complex c4 {0.5, 1.0};
        std::complex<double> c5 {0.5, 1.0};
        Dict test_dict {"k1", i1, "k2", f2, "k3", d3, "k4", c4, "k5", c5};
        // key access
        Integer k1;
        k1 = test_dict["k1"];
        dora::assert_equal(__LINE__, k1, 10);
        dora::assert_true(__LINE__, k1==10);
        dora::assert_equal(__LINE__, k1, i1);
        dora::assert_true(__LINE__, k1==i1);
        // float
        Double k2;
        k2 = test_dict["k2"];
        // FIXME Assert equal fails, but assert true using == is okay.
        dora::assert_true(__LINE__, k2==f2);
        // double
        Double k3;
        k3 = test_dict["k3"];
        dora::assert_equal(__LINE__, k3, 0.5);
        dora::assert_true(__LINE__, k3==0.5);
        dora::assert_equal(__LINE__, k3, d3);
        dora::assert_true(__LINE__, k3==d3);

        // Complex
        Complex k4;
        k4 = test_dict["k4"];
        //Complex k4 = test_dict["k4"];
        // k5 is initialised with std::complex
        Complex k5;
        k5 = test_dict["k5"];
        dora::assert_equal(__LINE__, k4.value(), c4.value());
        dora::assert_true(__LINE__, k4 == c4);
        dora::assert_true(__LINE__, k4 == k5);
    };
    
    test_case.all();
}

void test_direct_init_with_dict() {
    dora::TestCase test_case(__FILE__, __func__);

    // Direct init with dict as value
    test_case.pool = [](){
        Dict dict1;
        Dict test_dict {"k1", dict1};
        dora::assert_true(__LINE__, test_dict["k1"]->type_name() == "Dict");
        // implicitly converted from a shared pointer to dict.
        Dict dict2 = test_dict["k1"];
        dora::assert_true(__LINE__, dict2.type_name()=="Dict");
    };
    
    test_case.all();
}


// Objects for testing.
class Child : public object {
public:
    Child() {}
    ~Child() {}
    void print() { std::cout << "Child" << "\n";}
    std::string type_name() const { return "Child";}
};

class GrandChild : public Child {
public:
    GrandChild() {}
    ~GrandChild() {}
    void print() { std::cout << "GrandChild" << "\n";}
    std::string type_name() const { return "GrandChild";}
};

void test_direct_init_with_derived_object() {
    dora::TestCase test_case(__FILE__, __func__);

    // Direct init with dict as value
    test_case.pool = [](){
        std::shared_ptr<Child> child_sptr (new Child());
        std::shared_ptr<GrandChild> grand_child_sptr (new GrandChild());
        Dict test_dict {"k1", 1, "k2", child_sptr, "k3", grand_child_sptr};
        // Only object part is stored, for example, cannot call print method;
        // But override method survives, such as type
        dora::assert_equal(__LINE__, test_dict["k2"]->type_name(), "Child");
        dora::assert_equal(__LINE__, test_dict["k3"]->type_name(), "GrandChild");
        // must be dynamic_pointer_casted
        dora::assert_equal(
            __LINE__,
            std::dynamic_pointer_cast<Child>(test_dict["k2"])->type_name(),
            "Child");
        // same holds for the other shared pointer
        dora::assert_equal(
            __LINE__,
            std::dynamic_pointer_cast<GrandChild>(test_dict["k3"])->type_name(),
            "GrandChild");
    };
    test_case.all();
}


void test_keys() {
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        Integer int3 (10);
        Dict test_dict {"k1", 1, "k2", 2, "k3", int3};
        std::vector<std::string> keys;
        keys = test_dict.keys();
        dora::assert_equal(__LINE__, keys.size(), 3);
        dora::assert_equal(__LINE__, keys[0], "k1");
        dora::assert_equal(__LINE__, keys[1], "k2");
        dora::assert_equal(__LINE__, keys[2], "k3");
        // Key check
        dora::assert_true(__LINE__, test_dict.has_key("k1"));
        dora::assert_true(__LINE__, test_dict.has_key("k2"));
        dora::assert_true(__LINE__, test_dict.has_key("k3"));
        dora::assert_false(__LINE__, test_dict.has_key("k5"));
    };

    // Access an object
    test_case.pool = [](){
        Dict test_dict("k1", 1, "k2",2);
        Integer k1 {test_dict["k1"]};
        dora::assert_equal(__LINE__, k1, 1);
        //
        Integer k2 {test_dict["k2"]};
        dora::assert_equal(__LINE__, k2, 2);
        dora::assert_true(__LINE__, k1 < k2);
        dora::assert_true(__LINE__, k2 > k1);
    };

    test_case.pool = [](){ // Empty dict
        Dict test_dict;
        std::vector<std::string> keys;
        keys = test_dict.keys();
        dora::assert_equal(__LINE__, keys.size(), 0);
    };

    test_case.all();
}


void test_insert_via_key_value() {
    dora::TestCase test_case(__FILE__, __func__);
    
    test_case.pool = [](){
        Integer int3 (10);
        Dict item_dict {"key", 900};
        // init a dict
        Dict test_dict;
        // insert
        test_dict.insert("int3", int3);
        test_dict.insert("int2", int3);
        test_dict.insert("subdict", item_dict);
        // size
        dora::assert_equal(__LINE__, test_dict.keys().size(), 3);
        // key "subdict" should return a dict type.
        dora::assert_equal(__LINE__, test_dict["subdict"]->type_name(), "Dict");
        // via copy constructor, we may create a Dict object.
        Dict accept_dict = test_dict["subdict"];
        dora::assert_equal(__LINE__, accept_dict.type_name(), "Dict");
        dora::assert_true(__LINE__, Integer(accept_dict["key"]) == 900);
        
        // or, use assignment
        Dict dict_via_assignment;
        dict_via_assignment = test_dict["subdict"];
        dora::assert_equal(__LINE__, dict_via_assignment.type_name(), "Dict");
        dora::assert_true(__LINE__, Integer(dict_via_assignment["key"]) == 900);
        // insert one more
        dict_via_assignment.insert("extra", int3);
        dict_via_assignment.insert("extra_2", int3);
        dict_via_assignment.insert("extra_4", int3);
        // then dict_via_assignment has one more entry
        dora::assert_equal(__LINE__, dict_via_assignment.keys().size(), 4);

        // the other dict which shared the same original dict
        // doesn't change.
        dora::assert_equal(__LINE__, accept_dict.keys().size(), 1);
    };

    test_case.all();
}

void test_with_list_and_tuple() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        List lst {10, "Hello", 0.5};
        Dict dict {"int", 99, "list", lst};

        // read out list from dict
        List accept_list;  // can't copy construct implicitly
        accept_list = dict["list"]; // need to assign
        dora::assert_equal(__LINE__, Integer(accept_list[0]), 10);
        dora::assert_equal(__LINE__, Text(accept_list[1]), "Hello");
    };

    test_case.pool = [](){
        List lst {10, "Hello", 0.5};
        Tuple tpl {10, "Hello", 0.5};
        Dict dict {"int", 99, "list", lst, "tuple", tpl};

        // read out list from dict
        List accept_list;  // can't copy construct implicitly
        accept_list = dict["list"]; // need to assign
        Tuple accept_tuple;  // can't copy construct implicitly
        accept_tuple = dict["tuple"]; // need to assign
        dora::assert_equal(__LINE__, Integer(accept_list[0]), 10);
        dora::assert_equal(__LINE__, Text(accept_list[1]), "Hello");
        dora::assert_equal(__LINE__, Integer(accept_tuple[0]), 10);
        dora::assert_equal(__LINE__, Text(accept_tuple[1]), "Hello");
    };

    test_case.all();
}

/*
Insertion in sub-object.
This is an important operation if a container is to carry any type of
other containers.
*/
void test_insert_into_subdict() {
    dora::TestCase test_case(__FILE__, __func__);
/// An empty root dictionary
    Dict root_dict;
/// An empty subdict.
    Dict subdict;
/// Insert the empty subdict into root.
    root_dict.insert("subdict", subdict);

/// Check keys of empty dictionaries.
/// Test dict has one key.
    dora::assert_equal(__LINE__, root_dict.keys().size(), 1);

/// Create another empty sub2dict to be inserted into subdict
    Dict sub2dict;
/// To insert into sub-dict, need to cast the sub-dict
    std::dynamic_pointer_cast<Dict>(root_dict.get("subdict"))->insert("sub2dict", sub2dict);
    // root dict still has one key
    dora::assert_equal(__LINE__, root_dict.keys().size(), 1);

/// Access sub2dict
    std::shared_ptr<Dict> subdict_ptr = std::dynamic_pointer_cast<Dict>(root_dict["subdict"]);
/// Insert an item into sub2dict
    Integer int1 {1000};
    Integer int2 {2000};
    std::dynamic_pointer_cast<Dict>(subdict_ptr->get("sub2dict"))->insert("int1", int1);
    std::dynamic_pointer_cast<Dict>(subdict_ptr->get("sub2dict"))->insert("int2", int2);

/// Access from root dict
    dora::assert_equal(
        __LINE__,
        Integer(std::dynamic_pointer_cast<Dict>(subdict_ptr->get("sub2dict"))->get("int1")),
        1000);
    dora::assert_equal(
        __LINE__,
        Integer(std::dynamic_pointer_cast<Dict>(subdict_ptr->get("sub2dict"))->get("int2")),
        2000);

    test_case.all();
}


int main() {

/// constructors
    test_constructor();
/// direct init
    test_direct_init_with_primitive_types();
    test_direct_init_with_numeric_objects();
    test_direct_init_with_derived_object();
/// keys
    test_keys();
/// insert
    test_insert_via_key_value();
/// with list
    test_with_list_and_tuple();

/// Insertion into sub-containers.
    test_insert_into_subdict();
    return 0;
}
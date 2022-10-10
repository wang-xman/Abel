#ifndef _ABEL_LIST_HPP_
#define _ABEL_LIST_HPP_

#include "intrinsic.hpp"

namespace abel {

class List : public object {
private:
    std::string type_name_string = "List";

protected:
    std::vector<std::shared_ptr<object> > internal;

    void push() {} // base case
    
    template <
        typename... Args,
        typename T,
        typename std::enable_if<
            std::is_same<T, Null>::value || std::is_same<T, Bool>::value
            || std::is_same<T, Text>::value || std::is_same<T, Integer>::value
            || std::is_same<T, Double>::value || std::is_same<T, Complex>::value
            || std::is_same<T, Binary>::value || std::is_same<T, Bitstring>::value,
        bool>::type=true>
    void push(const T& ref, Args... args)
    {
        internal.push_back( std::make_shared<T>(ref) );
        push(args...);
    }
    
    // Push C++ primitive

    template <typename... Args> void push(const bool c_bool, Args... args)
    {
        internal.push_back( std::make_shared<Bool>(c_bool) );
        push(args...);
    }

    template <typename... Args> void push(const int c_int, Args... args)
    {
        internal.push_back( std::make_shared<Integer>(c_int) );
        push(args...);
    }

    template <typename... Args> void push(const double c_double, Args... args)
    /*
        CAUTION! Initialise with 0.5 triggers this method, but with 0.5f
        triggers float.
    */
    {
        internal.push_back( std::make_shared<Double>(c_double) );
        push(args...);
    }

    template <typename... Args> void push(const float c_float, Args... args)
    {
        internal.push_back( std::make_shared<Double>(c_float) );
        push(args...);
    }

    template <typename... Args> void push(const std::string& str, Args... args)
    {
        internal.push_back( std::make_shared<Text>(str) );
        push(args...);
    }

    template <typename... Args> void push(const char* chars, Args... args)
    /*
        Push C++ chars. It is first converted into a string, then
        a shared pointer of `Text`
    */
    {
        internal.push_back( std::make_shared<Text>(std::string(chars)) );
        push(args...);
    }

    template <typename... Args> void push(const List& list, Args... args)
    /*
        Push a reference to `List` is to copy-construct it into
        shared pointer.
    */
    {
        internal.push_back( std::make_shared<List>(list) ); // copy ctor called
        push(args...);
    }

    template <typename... Args>
    void push(const std::shared_ptr<List> sptr, Args... args)
    /*
        Push a shared pointer of `List` is to copy and store it.
    */
    {
        internal.push_back(sptr);
        push(args...);
    }

    // First argument is an shared pointer, transfer the ownership.
    template <typename... Args>
    void push(const std::shared_ptr<object> sptr, Args... args)
    {
        internal.push_back(sptr);
        push(args...);
    }

    // To be implemented in `container.hpp`
    template <typename... Args> void push(const Tuple&, Args...);
    template <typename... Args> void push(const std::shared_ptr<Tuple>, Args...);
    template <typename... Args> void push(const Dict&, Args...);
    template <typename... Args> void push(const std::shared_ptr<Dict>, Args...);

public:
    List();
    List(const List&);

    explicit List(const std::shared_ptr<List>);
    explicit List(const std::shared_ptr<object>);

    template <typename... Args> explicit List(Args... args) { push(args...); }
    
    template <typename T> explicit List(const std::vector<T>);

    ~List();

    List& operator=(const List&);
    List& operator=(const std::shared_ptr<List>);
    List& operator=(const std::shared_ptr<object>);

    int size() const;

    bool is_valid_index(int) const;

    bool is_empty() const;

    std::shared_ptr<object> get(const int); // TODO Not tested

    std::shared_ptr<object> operator[](const int);

    template <typename T> void push_back(T& val) { push(val); }

    // Insertion
    void insert_check(const int);

    template <
        typename T,
        typename std::enable_if<
            std::is_same<T, Null>::value || std::is_same<T, Bool>::value
            || std::is_same<T, Text>::value || std::is_same<T, Integer>::value
            || std::is_same<T, Double>::value || std::is_same<T, Complex>::value
            || std::is_same<T, Binary>::value || std::is_same<T, Bitstring>::value,
        bool>::type=true>
    void insert(const int index, const T& ref)
    /*
        Inserts Abel intrinsics
    */
    {
        insert_check(index);
        internal.insert( internal.begin() + index, std::make_shared<T>(ref) );
    }

    void insert(const int, const bool&);
 
    void insert(const int, const int&);

    void insert(const int, const double&);

    void insert(const int, const std::string&);

    void insert(const int, const char*); // insert `const char*`

    // Implemented in container.hpp header
    void insert(const int, const Dict&);
    template <typename T> void insert(const int, const std::shared_ptr<T>);

    std::string type_name() const override;

    // Vectorise into C++ primitive types
    std::vector<double> as_vector_double();
    std::vector<int> as_vector_int();
    std::vector<std::string> as_vector_string();
};

} // end abel
#endif
/*
    HEADER tuple.hpp
    UPDATE 30-June-2022
    
    TODO
    1. Not fully documented.
*/
#ifndef ABEL_TUPLE_HPP
#define ABEL_TUPLE_HPP

#include "list.hpp"

namespace abel {

class Tuple : public object {
private:
    std::string type_name_string = "Tuple";

protected:
    std::vector<std::shared_ptr<object> > internal;

/// Base case of push method
    void push() {}

/// First argument is primitive numeric type or string
/// Copy of the value is converted into corresponding object.

    // Null type. Different from C/C++ NULL.
    template <typename... Args> void push(const Null& ref, Args... args)
    { // Null
        internal.push_back(std::shared_ptr<Null>( new Null() ));
        push(args...);
    }
    // bool & Bool
    template <typename... Args> void push(const bool c_bool, Args... args)
    { // C++ bool
        internal.push_back(std::shared_ptr<Bool>( new Bool(c_bool) ));
        push(args...);
    }

    template <typename... Args> void push(const Bool& ref, Args... args)
    { // Bool
        internal.push_back(std::shared_ptr<Bool>( new Bool(ref) ));
        push(args...);
    }

    // int & Integer
    template <typename... Args> void push(const int c_int, Args... args)
    { // int
        internal.push_back(std::shared_ptr<Integer>( new Integer(c_int) ));
        push(args...);
    }

    template <typename... Args> void push(const Integer& ref, Args... args)
    { // Integer
        internal.push_back(std::shared_ptr<Integer>( new Integer(ref) ));
        push(args...);
    }
    
    // double & Double
    // For example, initialise with 0.5 triggers this method, but with 0.5f
    // triggers float.
    template <typename... Args> void push(const double c_double, Args... args)
    { // double
        internal.push_back(std::shared_ptr<Double>( new Double(c_double) ));
        push(args...);
    }

    template <typename... Args> void push(const Double& ref, Args... args)
    { // double
        internal.push_back(std::shared_ptr<Double>( new Double(ref) ));
        push(args...);
    }

    // float & Float
    template <typename... Args> void push(const float c_float, Args... args)
    { // float to Double
        internal.push_back(std::shared_ptr<Double>( new Double(c_float) ));
        push(args...);
    }
    
    // complex
    //template <typename T, typename... Args,
    //    typename std::enable_if<std::is_same<T, double>::value, bool>::type=true
    //>
    template <typename... Args> void push(const Complex& c, Args... args)
    { // abel::Complex
        internal.push_back(std::shared_ptr<Complex>( new Complex(c) ));
        push(args...);
    }
    // string & Text
    template <typename... Args> void push(const std::string& str, Args... args)
    { // string
        internal.push_back(std::shared_ptr<Text>( new Text(str) ));
        push(args...);
    }

    template <typename... Args> void push(const Text& str, Args... args)
    { // string
        internal.push_back(std::shared_ptr<Text>( new Text(str) ));
        push(args...);
    }

    template <typename... Args> void push(const char* chars, Args... args)
    { // const char
        internal.push_back(
                std::shared_ptr<Text>( new Text(std::string(chars)) ));
        push(args...);
    }
    // First argument is a reference to List
    // Use make_shared and reference to avoid dangling pointer.
    template <typename... Args> void push(const List& list, Args... args)
    {
        internal.push_back( std::make_shared<List>(list) ); // copy ctor called
        push(args...);
    }

    // First argument is a shared pointer of List,
    template <typename... Args>
    void push(const std::shared_ptr<List> sptr, Args... args)
    {
        internal.push_back(sptr);
        push(args...);
    }

    // First argument is a reference to Tuple
    // Use make_shared and reference to avoid dangling pointer.
    template <typename... Args>
    void push(const Tuple& tuple, Args... args)
    {
        internal.push_back( std::make_shared<Tuple>(tuple) ); // copy ctor called
        push(args...);
    }

    // First argument is a shared pointer of Tuple,
    template <typename... Args>
    void push(const std::shared_ptr<Tuple> sptr, Args... args)
    {
        internal.push_back(sptr);
        push(args...);
    }

    // At this point, a complete Dict class is absent.
    // To be implemented in container (patch) header.
    template <typename... Args> void push(const Dict&, Args...);
    template <typename... Args> void push(const std::shared_ptr<Dict>, Args...);

    // First argument is an shared pointer, transfer the ownership.
    template <typename... Args>
    void push(const std::shared_ptr<object> sptr, Args... args)
    {
        internal.push_back(sptr);
        push(args...);
    }

public:
/// Constructors
    Tuple();
    Tuple(const Tuple&);
    explicit Tuple(const std::shared_ptr<Tuple>);
    explicit Tuple(const std::shared_ptr<object>);
/// Recursive constructor
    template <typename... Args>
    explicit Tuple(Args... args) { push(args...); }

    template <typename T>
    explicit Tuple(const std::vector<T>);

/// Destructor
    ~Tuple();

/// Copy assignment operators.
    Tuple& operator=(const Tuple&);
    Tuple& operator=(const std::shared_ptr<Tuple>);
    Tuple& operator=(const std::shared_ptr<object>);

/// Element-wise operations
    int size() const;                        // size

    bool is_valid_index(int) const;

    bool is_empty() const;

    std::shared_ptr<object> get(const int); // TODO Not tested/ Not documented.
    
    std::shared_ptr<object> operator[](int); // element retrieve
    
    template <typename T>                    // push back element
    void push_back(T& val) { push(val); }

/// Insertion
    // Check index before insertion. Index for insertion is allowed
    // to be the same as the length of the tuple, i.e. push back.
    void insert_check(const int);

    // insert int or Integer
    template <typename T, typename std::enable_if<
            std::is_same<T, int>::value || std::is_same<T, Integer>::value, bool
        >::type=true
    >
    void insert(const int index, const T& ref)
    {
        try {
            insert_check(index);
            internal.insert( internal.begin() + index,
                              std::make_shared<Integer>(ref) );
        } catch (error::IndexOutOfRange& err) { err.make_show(); }
    }

    // insert double or Double
    template <typename T, typename std::enable_if<
            std::is_same<T, double>::value || std::is_same<T, Double>::value, bool
        >::type=true
    >
    void insert(const int index, const T& ref)
    {
        try {
            insert_check(index);
            internal.insert( internal.begin() + index,
                              std::make_shared<Double>(ref) );
        } catch (error::IndexOutOfRange& err) { err.make_show(); }
    }
    
    // insert Complex
    template <typename T,
              typename std::enable_if<std::is_same<T, Complex>::value,
                                      bool>::type=true
    >
    void insert(const int index, const T& ref)
    {
        try {
            insert_check(index);
            internal.insert(internal.begin() + index,
                             std::make_shared<Complex>(ref));
        } catch (error::IndexOutOfRange& err) { err.make_show(); }
    }

    // insert string or Text
    template <
        typename T,
        typename std::enable_if<
            std::is_same<T, std::string>::value || std::is_same<T, Text>::value,
        bool>::type=true>
    void insert(const int index, const T& ref)
    {
        try {
            insert_check(index);
            internal.insert( internal.begin() + index,
                              std::make_shared<Text>(ref) );
        } catch (error::IndexOutOfRange& err) { err.make_show(); }   
    }
    
    // insert a const char into a tuple
    void insert(const int, const char*);
    // insert Dict is implemented in patch source (patch.cpp) file.
    void insert(const int, const Dict&);

    // insert shared pointer, implemented in patch header.
    template <typename T>
    void insert(const int, const std::shared_ptr<T>);

/// Type info
    std::string type_name() const override;
};

}
#endif
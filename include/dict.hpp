#ifndef ABEL_DICT_HPP
#define ABEL_DICT_HPP

#include "tuple.hpp"

namespace abel {

class Dict : public object {
private:
    std::string type_name_string = "Dict";
    
protected:
    std::map<std::string, std::shared_ptr<object> > internal;

    void init() {}

    template <
        typename... Args,
        typename T,
        typename std::enable_if<
            std::is_same<T, Null>::value || std::is_same<T, Bool>::value
            || std::is_same<T, Text>::value || std::is_same<T, Integer>::value
            || std::is_same<T, Double>::value || std::is_same<T, Complex>::value
            || std::is_same<T, Binary>::value || std::is_same<T, Bitstring>::value,
        bool>::type=true>
    void init(std::string key, T& ref, Args... args)
    {
        internal.insert( std::pair<std::string, std::shared_ptr<T>>
                         (key, std::make_shared<T>(ref)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, bool c_bool, Args... args)
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Bool> >
                         (key, std::make_shared<Bool>(c_bool)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, std::string c_string, Args... args)
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Text> >
                         (key, std::make_shared<Text>(c_string)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, const char* chars, Args... args)
    {
        init(key, std::string(chars), args...);
    }

    template <typename... Args>
    void init(std::string key, int c_int, Args... args)
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Integer> >
                         (key, std::make_shared<Integer>(c_int)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, double c_double, Args... args)
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Double> >
                         (key, std::make_shared<Double>(c_double)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, float c_float, Args... args)
    /*
        C++ primitive `float`.
        CAUTION! Coerced into double then wrapped as `Double`.
    */
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Double> >
                         (key, std::make_shared<Double>((double)c_float)) );
        init(args...);
    }

    // TODO Not correct.
    template <typename T, typename... Args>
    void init(std::string key, std::complex<T>& ref, Args... args) {
        internal.insert(
            std::pair<std::string, std::shared_ptr<Complex> >
            (key, std::shared_ptr<Complex>( new Complex(ref) )));
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, List& list, Args... args)
    /*
        Reference to Abel `List`
        THINK! Shall I use move semantics?
    */
    {
        internal.insert( std::pair<std::string, std::shared_ptr<List> >
                         (key, std::make_shared<List>(list)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, Tuple& tuple, Args... args)
    /*
        Reference to Abel `Tuple`
        THINK! Not sure if tuple if meaningful here.
    */
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Tuple> >
                         (key, std::make_shared<Tuple>(tuple)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, Dict& dict, Args... args)
    /*
        Reference to Abel `Dict`.
        A shared pointer of `Dict` object is stored.
        THINK! Shall I use move semantics?
    */
    {
        internal.insert( std::pair<std::string, std::shared_ptr<Dict> >
                         (key, std::make_shared<Dict>(dict)) );
        init(args...);
    }

    template <typename... Args>
    void init(std::string key, std::shared_ptr<object> sptr, Args... args)
    /*
        Shared pointer of Abel `object`
        This method is a generic solution to initialise with any
        type that inherits from `object`.
    */
    {
        internal.insert( std::pair<std::string, std::shared_ptr<object> >
                         (key, sptr) );
        init(args...);
    }

public:
    Dict();
    Dict(const Dict&);
    Dict(const std::shared_ptr<Dict>);
    Dict(const std::shared_ptr<object>);

    // Recursive constructor
    template <typename... Args>
    explicit Dict(std::string key, Args... args) { init(key, args...); }

    ~Dict();

    Dict& operator=(const Dict&);
    Dict& operator=(const std::shared_ptr<Dict>);
    Dict& operator=(const std::shared_ptr<object>);

    std::string type_name() const override;

    std::vector<std::string> keys();

    bool has_key(const std::string) const;

    std::shared_ptr<object> get(const std::string);

    std::shared_ptr<object> operator[](std::string);

    void insert(std::pair<std::string, std::shared_ptr<object> >);

    template <typename T>
    void insert(const std::string key, T& ref)
    {
        try {
            if ( has_key(key) ) {
                std::string msg = "Key '" + key + "' already exists";
                throw error::DuplicateKey(msg);
            }
        } catch (error::KeyNotFound& err) { err.make_show(); }
        init(key, ref);
    }

    template <typename T>
    void insert(const std::string key, std::shared_ptr<T> sptr)
    {
        try {
            if ( has_key(key) ) {
                std::string msg = "Key '" + key + "' already exists";
                throw error::DuplicateKey(msg);
            }
        } catch (error::KeyNotFound& err) { err.make_show(); }
        init(key, sptr); 
    }
};

}
#endif
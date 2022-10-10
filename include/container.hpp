#ifndef _ABEL_CONTAINER_HPP_
#define _ABEL_CONTAINER_HPP_

#include "dict.hpp"

namespace abel {

// List related methods

template <typename... Args>
void List::push(const Tuple& ref, Args... args)
/*
    List : Pushes a tuple into list. Declared in header list.hpp
*/
{
    try {
        internal.push_back( std::make_shared<Tuple>(ref) );
        push(args...);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename... Args>
void List::push(const std::shared_ptr<Tuple> sptr, Args... args)
/*
    List : Push a shared ptr of Tuple into list. Declared in `list.hpp`
*/
{
    try {
        internal.push_back(sptr);
        push(args...);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename... Args>
void List::push(const Dict& ref, Args... args)
/*
    List : Pushes a Dict into list. Declared in `list.hpp`
*/
{
    try {
        internal.push_back( std::make_shared<Dict>(ref) );
        push(args...);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename... Args>
void List::push(const std::shared_ptr<Dict> sptr, Args... args)
/*
    List : Pushes a shared ptr of Dict into List. Declared in `list.hpp`
*/
{
    try {
        internal.push_back(sptr);
        push(args...);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void List::insert(const int index, const std::shared_ptr<T> sptr)
/*
    List : Inserts a shared ptr into list. Declared in `list.hpp`
*/
{
    try {
        insert_check(index);
        internal.insert(internal.begin() + index, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

// Tuple related methods

template <typename... Args>
void Tuple::push(const Dict& ref, Args... args)
/*
    Tuple : Push a Dict into tuple. Declared in `tuple.hpp`
*/
{
    try {
        internal.push_back( std::make_shared<Dict>(ref) );
        push(args...);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename... Args>
void Tuple::push(const std::shared_ptr<Dict> sptr, Args... args)
/*
    Tuple : Pushes a shared ptr of Dict into tuple. Declared in `tuple.hpp`
*/
{
    try {
        internal.push_back(sptr);
        push(args...);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

// Getter and setter function templates for containers are collected
// in namespace `abel::cnt`.
namespace cnt {

// In getters, generic parameter `T` is the type of object to be accessed.
template <typename T = object>
std::shared_ptr<T> get(List& list, int index)
/*
    List : Gets object from reference to List.
*/
{
    return std::dynamic_pointer_cast<T>( list.get(index) );
}

template <typename T = object>
std::shared_ptr<T> get(Tuple& tuple, int index)
/*
    Tuple : Gets object from reference to tuple
*/
{
    return std::dynamic_pointer_cast<T>( tuple.get(index) );
}

template <typename T = object>
std::shared_ptr<T> get(Dict& dict, const std::string key)
/*
    Dict : Gets object from reference to Dict
*/
{
    return std::dynamic_pointer_cast<T>( dict.get(key) );
}

// Gets objects from shared pointer of container
template <typename T = object>
std::shared_ptr<T> get(std::shared_ptr<List>&& list_sptr, int index)
/*
    List : Gets object from a shared pointer of List.
*/
{
    return std::dynamic_pointer_cast<T>( list_sptr->get(index) );
}

template <typename T = object>
std::shared_ptr<T> get(std::shared_ptr<Tuple>& tuple_sptr, int index)
/*
    Tuple : Gets object from shared pointer of tuple
*/
{
    return std::dynamic_pointer_cast<T>( tuple_sptr->get(index) );
}

template <typename T = object>
std::shared_ptr<T> get(std::shared_ptr<Dict> sptr, const std::string key)
/*
    Dict : Gets object from a shared pointer to Dict
*/
{
    return std::dynamic_pointer_cast<T>( sptr->get(key) );
}

// Setters. Parameter `T` in setters is the type of the object to be
// settled in the container.
template <typename T>
void set(List& list, const int index, T& ref)
/*
    List : Sets an object in List at given index.
    Equivalent to `insert` method of List
*/
{
    try {
        list.insert(index, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(List& list, const int index, const T&& rvalue)
/*
    List : Settles a rvalue into a list
*/
{
    try {
        T ref = rvalue;
        list.insert(index, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(List& list, const int index, const std::shared_ptr<T>& sptr)
/*
    List : Sets a shared pointer in a list
*/
{
    try {
        list.insert(index, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<List>& list_sptr, const int index, T& ref)
/*
    List : Sets an object in a shared ptr of list
*/
{
    try {
        list_sptr->insert(index, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }   
}

template <typename T>
void set(std::shared_ptr<List>& list_sptr, const int index, const T&& rvalue)
/*
    List : Sets a rvalue in a shared pointer of list
*/
{
    try {
       T ref = rvalue;
       list_sptr->insert(index, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<List>& list_sptr, const int index,
         const std::shared_ptr<T>& sptr)
/*
    List : Sets a shared ptr in a shared ptr of List
*/
{
    try {
        list_sptr->insert(index, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(Tuple& tuple, const int index, const T& ref)
/*
    Tuple: Sets an object in a Tuple
*/
{
    try {
        tuple.insert(index, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(Tuple& tuple, const int index, const std::shared_ptr<T>& sptr)
/*
    Tuple : Set a shared pointer in a tuple
*/
{
    try {
        tuple.insert(index, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<Tuple>& tuple_sptr, const int index, const T& ref)
{
    try {
        tuple_sptr->insert(index, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<Tuple>& tuple_sptr, const int index,
         const std::shared_ptr<T>& sptr)
{
    try {
        tuple_sptr->insert(index, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

// Dict related setters
template <typename T>
void set(Dict& dict, const std::string key, T& ref)
{
    try {
        dict.insert(key, ref);    
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(Dict&& dict, const std::string key, T& ref)
{
    try {
        dict.insert(key, ref);    
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(Dict& dict, const std::string key, const T&& rvalue)
{
    try {
        T ref = rvalue;
        dict.insert(key, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(Dict& dict, const std::string key, std::shared_ptr<T> sptr)
{
    try {
        dict.insert(key, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<Dict>&& sptr, const std::string key, T& ref)
{
    try {
        sptr->insert(key, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<Dict>& sptr, const std::string key, T& ref)
{
    try {
        sptr->insert(key, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<Dict>& sptr, const std::string key, const T&& rvalue)
{
    try {
        T ref = rvalue;
        sptr->insert(key, ref);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

template <typename T>
void set(std::shared_ptr<Dict>& dict_sptr, const std::string key,
         std::shared_ptr<T> sptr)
{
    try {
        dict_sptr->insert(key, sptr);
    } catch (error::BaseError& err) {
        err.make_show();
    }
}

} // end abel::cnt

}
#endif
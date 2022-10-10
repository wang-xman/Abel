/*
    SOURCE tuple.cpp
    UPDATE 30-June-2022
*/
#include "tuple.hpp"

namespace abel {

Tuple::Tuple() {}

Tuple::Tuple(const Tuple& list_ref) { internal = list_ref.internal;}

Tuple::Tuple(const std::shared_ptr<Tuple> sptr) { internal = sptr->internal; }

Tuple::Tuple(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Tuple") {
            std::string msg = "Cannot copy-construct a non-tuple type of "
                              "(object) shared pointer to a Tuple object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Tuple>(sptr)->internal;
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

/// Destructor
Tuple::~Tuple() {}

/// Copy assignment
Tuple& Tuple::operator=(const Tuple& ref)
{
    internal = ref.internal;
    return *this;
}

Tuple& Tuple::operator=(const std::shared_ptr<Tuple> sptr)
{
    internal = sptr->internal;
    return *this;
}

Tuple& Tuple::operator=(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Tuple") {
            std::string msg = "Cannot assign a non-tuple type shared "
                              "pointer of object to a Tuple object.";
            throw error::IncompatibleType(msg);
        }
        internal = std::dynamic_pointer_cast<Tuple>(sptr)->internal;
    }
    catch (error::IncompatibleType& err) { err.make_show(); }
    catch (std::exception& err) { /* TODO */ }
    return *this;
}

/// Element-wise operations
int Tuple::size() const { return internal.size(); }

bool Tuple::is_valid_index(int index) const
{
    return (index >= 0) && ( index < size() );
}

bool Tuple::is_empty() const {
    return (size() == 0);
}

std::shared_ptr<object> Tuple::get(int index)
{
    try {
        if ( !is_valid_index(index) ) {
            throw error::IndexOutOfRange("Tuple index out of range.");
        }
    } catch (error::IndexOutOfRange& err) { err.make_show(); }
    return internal[index];
}

std::shared_ptr<object> Tuple::operator[](int index) { return get(index); }

/// FIXME Can tuple have this method??
/// Insertion check
/// If list is empty, index for insertion must be 0; otherwise, index for
/// insertion must be between 0 and the size of list.
/// Note the difference between valid index for insertion and valid index
/// for indexing.
void Tuple::insert_check(const int index)
{
    if (size() == 0) { // empty list
        if (index != 0) {
            throw error::IndexOutOfRange("Tuple for insertion is empty."
                                  "Can only insert at 0.");
        }
    } else { // non-empty list
        // insertion allows index to be the same as vector size
        // then insertion become push back.
        if ( !( (index >= 0) && (index <= size()) ) ) {    
            throw error::IndexOutOfRange("Index for insertion is out of range.");
        }
    }
}

/// insert char
void Tuple::insert(const int index, const char* chars)
{
    try {
        insert_check(index);
        internal.insert( internal.begin() + index,
                          std::make_shared<Text>(std::string(chars)) );
    } catch (error::IndexOutOfRange& err) { err.make_show(); }   
}

/// Type info
std::string Tuple::type_name() const { return type_name_string; }

}
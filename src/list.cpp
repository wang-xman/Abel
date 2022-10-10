#include "list.hpp"

namespace abel {

List::List() {}

List::List(const List& list_ref) { internal = list_ref.internal;}

List::List(const std::shared_ptr<List> sptr) { internal= sptr->internal; }

List::List(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "List") {
            std::string msg = "Cannot copy-construct a non-list type of "
                              "(object) shared pointer to a List object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<List>(sptr)->internal;
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

List::~List() {}

List& List::operator=(const List& ref)
{
    internal = ref.internal;
    return *this;
}

List& List::operator=(const std::shared_ptr<List> sptr)
{
    internal = sptr->internal;
    return *this;
}

List& List::operator=(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "List") {
            std::string msg = "Cannot assign a non-list type shared "
                              "pointer of object to a List object.";
            throw error::IncompatibleType(msg);
        }
        internal = std::dynamic_pointer_cast<List>(sptr)->internal;
    }
    catch (error::IncompatibleType& err) { err.make_show(); }
    catch (std::exception& err) { /* TODO */ }
    return *this;
}

int List::size() const
{
    return internal.size();
}

bool List::is_valid_index(int index) const
{
    return (index >= 0) && (index < size());
}

bool List::is_empty() const
{
    return (size() == 0);
}

std::shared_ptr<object> List::get(const int index)
{
    try {
        if ( !is_valid_index(index) ) {
            throw error::IndexOutOfRange("List index out of range.");
        }
    } catch (error::IndexOutOfRange& err) { err.make_show(); }
    return internal[index];
}

std::shared_ptr<object> List::operator[](const int index) { return get(index); }

void List::insert_check(const int index)
/*
    Check index before insertion. Index for insertion is allowed
    to be the same as the length of the list, i.e. push back.
*/
{
    if (size() == 0) { // empty
        if (index != 0) {
            std::cout << "index is "<< index << "\n";
            throw error::IndexOutOfRange("List for insertion is empty."
                                  "Can only insert at 0.");
        }
    } else { // non-empty
        // insertion allows index to be the same as vector size
        // then insertion become push back.
        if ( !( (index >= 0) && (index <= size()) ) ) {    
            throw error::IndexOutOfRange("Index for insertion is out of range.");
        }
    }
}

void List::insert(const int index, const bool& ref)
{
    insert_check(index);
    internal.insert( internal.begin() + index, std::make_shared<Bool>(ref) );
}

void List::insert(const int index, const int& ref)
{
    insert_check(index);
    internal.insert( internal.begin() + index, std::make_shared<Integer>(ref) );
}

void List::insert(const int index, const double& ref)
{
    insert_check(index);
    internal.insert( internal.begin() + index, std::make_shared<Double>(ref) );
}

void List::insert(const int index, const std::string& ref)
/*
    Insert C++ string or `Text`
*/
{
    insert_check(index);
    internal.insert( internal.begin() + index, std::make_shared<Text>(ref) );
}

void List::insert(const int index, const char* chars)
/*
    Insert `const char*`
*/
{
    try {
        insert_check(index);
        internal.insert(internal.begin() + index,
                         std::make_shared<Text>(std::string(chars)));
    } catch (error::IndexOutOfRange& err) { err.make_show(); }   
}

std::string List::type_name() const { return type_name_string; }

// Vectorise

std::vector<double> List::as_vector_double()
/*
    TODO Need to send a warning in case a list consists of lists,
    i.e. multi-dimensional list, hence multi-dimensional vector.
*/
{
    std::vector<double> ret;
    for (int i = 0; i < size(); i++) {
        if (internal[i]->type_name() == "Integer") {
            ret.push_back(
                (double)std::dynamic_pointer_cast<Integer>(internal[i])->value()
            );
        } else if (internal[i]->type_name() == "Double") {
            ret.push_back(
                std::dynamic_pointer_cast<Double>(internal[i])->value());
        } else {
            throw error::DataTypeConversionError("Failed to create a vector "
                "due to data type conversion.");
        }
    }
    return ret;
}

std::vector<int> List::as_vector_int()
/* TODO */
{
    std::vector<int> ret;
    for (int i = 0; i < size(); i++) {
        if (internal[i]->type_name() == "Integer") {
            ret.push_back(
                (int)std::dynamic_pointer_cast<Integer>(internal[i])->value()
            );
        } else if (internal[i]->type_name() == "Double") {
        // converting double to int results in precision loss.
            ret.push_back(
                (int)std::dynamic_pointer_cast<Double>(internal[i])->value()
            );
        } else {
            throw error::DataTypeConversionError("Failed to create a vector "
                "due to data type conversion.");
        }
    }
    return ret;
}

std::vector<std::string> List::as_vector_string()
{
    std::vector<std::string> ret;
    for (int i = 0; i < size(); i++) {
        if (internal[i]->type_name() == "Text") {
            ret.push_back(
                std::dynamic_pointer_cast<Text>(internal[i])->value()
            );
        } else {
            throw error::DataTypeConversionError("Failed to create a vector "
                "due to data type conversion.");
        }
    }
    return ret;
}

}
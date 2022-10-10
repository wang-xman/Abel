#include "integer.hpp"

namespace abel {

Integer::Integer() {}

Integer::Integer(const Integer& integer) : numeric<int>::numeric(integer) {}

Integer::Integer(const int& number) : numeric<int>::numeric(number) {}

Integer::Integer(std::unique_ptr<Integer>& uptr)
{
    std::unique_ptr<Integer> temp = std::move(uptr);
    internal = temp->value();
}

Integer::Integer(std::unique_ptr<object>& uptr)
{
    try {
        if (uptr->type_name() != "Integer") {
            std::string msg = "Cannot copy-contruct an Integer object from "
                              "a non-Integer type unique pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            // cast it from `object` to `Text`
            internal = std::unique_ptr<Integer>(
                    static_cast<Integer*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Integer::Integer(const std::shared_ptr<Integer>& sptr)
{
    internal = sptr->value();
}

Integer::Integer(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Integer") {
            std::string msg = "Cannot copy-contruct a non-integer type shared"
                              "pointer of Object to an Integer object.";
            throw error::IncompatibleType(msg);
        } else {
            this->internal = std::dynamic_pointer_cast<Integer>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Integer::~Integer() {}

Integer& Integer::operator=(const int& number)
{
    numeric<int>::operator=(number);
    return *this;
}

Integer& Integer::operator=(std::unique_ptr<Integer>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Integer> temp = std::move(uptr);
    internal = temp->value();
    return *this;
}

Integer& Integer::operator=(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Integer") {
            std::string msg = "Cannot assign to an Integer object a "
                              "non-Integer type unique pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::unique_ptr<Integer>(
                    static_cast<Integer*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Integer& Integer::operator=(const std::shared_ptr<Integer>& sptr)
{
    internal = sptr->value();
    return *this;
}

Integer& Integer::operator=(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Integer") { // Only Integer type.
            std::string msg = "Cannot assign a non-integer type shared "
                              "pointer of Object to an Integer object.";
            throw error::IncompatibleType(msg);
        }
        this->internal = std::dynamic_pointer_cast<Integer>(sptr)->value();

    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Integer::operator int() { return internal; }

Integer::operator double() { return (double)internal; }

Integer::operator float() { return (float)internal; }

std::string Integer::type_name() const { return type_name_string; }

}
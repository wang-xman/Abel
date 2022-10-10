#include "double.hpp"

namespace abel {

Double::Double() {}

Double::Double(const Double& d_ref) : numeric<double>::numeric(d_ref) {}

Double::Double(const double& number) : numeric<double>::numeric(number) {}

Double::Double(std::unique_ptr<Double>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Double> temp = std::move(uptr);
    internal = temp->value();
}

Double::Double(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Double") {
            std::string msg = "Cannot copy-contruct a Double object from "
                              "a non-Double type unique pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            // cast it from `object` to `Text`
            internal = std::unique_ptr<Double>(
                    static_cast<Double*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Double::Double(const std::shared_ptr<Double>& sptr) { internal = sptr->value(); }

Double::Double(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Double") {
            std::string msg = "Cannot copy-contruct a non-Double type shared"
                              "pointer of Object to an Double object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Double>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Double::~Double() {}

Double& Double::operator=(const double& number)
{
    numeric<double>::operator=(number);
    return *this;
}

Double& Double::operator=(std::unique_ptr<Double>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Double> temp = std::move(uptr);
    internal = temp->value();
    return *this;
}

Double& Double::operator=(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Double") {
            std::string msg = "Cannot assign to a Double object a "
                              "non-Double type unique pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::unique_ptr<Double>(
                    static_cast<Double*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Double& Double::operator=(const std::shared_ptr<Double>& ptr)
{
    internal = ptr->value();
    return *this;
}

Double& Double::operator=(const std::shared_ptr<object>& sptr)
/*
    FIXME! Shall I accept also Integer, etc, as type-widening casting?
*/
{
    try {
        if (sptr->type_name() != "Double") {
            std::string msg = "Cannot assign a non-Double type shared"
                              "pointer of Object to a Double object.";
            throw error::IncompatibleType(msg);
        }
        internal = std::dynamic_pointer_cast<Double>(sptr)->value();
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Double::operator double() { return internal; }

std::string Double::type_name() const { return type_name_string; }

}
#include "bool.hpp"

namespace abel {

Bool::Bool() {}

Bool::Bool(const bool& bool_ref) : internal(bool_ref) {}

Bool::Bool(std::unique_ptr<Bool>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Bool> temp = std::move(uptr);
    internal = temp->value();
}

Bool::Bool(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Bool") {
            std::string msg = "Cannot copy-contruct a Bool object from "
                              "a non-Boolean-type unique pointer.";
            throw error::IncompatibleType(msg);
        } else {
            // cast it from `object` to `Bool`
            internal = std::unique_ptr<Bool>(
                    static_cast<Bool*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Bool::Bool(const std::shared_ptr<Bool>& sptr) : internal( sptr->value() ) {}

Bool::Bool(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Bool") {
            std::string msg = "Cannot copy-contruct a Bool object from "
                              "a non-Boolean-type shared pointer.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Bool>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Bool::~Bool() {}

Bool& Bool::operator=(const bool& c_bool_ref)
{
    internal = c_bool_ref;
    return *this;
}

Bool& Bool::operator=(std::unique_ptr<Bool>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Bool> temp = std::move(uptr);
    internal = temp->value();
    return *this;
}

Bool& Bool::operator=(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Bool") {
            std::string msg = "Cannot assign a non-Boolean type shared"
                              "pointer of object to a Bool object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::unique_ptr<Bool>(
                    static_cast<Bool*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Bool& Bool::operator=(const std::shared_ptr<Bool>& sptr)
{
    internal = sptr->value();
    return *this;
}

Bool& Bool::operator=(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Bool") {
            std::string msg = "Cannot assign a non-boolean type shared"
                              "pointer of object to a Bool object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Bool>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Bool::operator bool() { return internal; }

std::string Bool::type_name() const { return type_name_string; }

bool Bool::value() const { return internal; }

//// Compare Bool with Bool/bool
bool operator==(const Bool& l_Bool_ref, const Bool& r_Bool_ref)
{
    return l_Bool_ref.value() == r_Bool_ref.value();
}

bool operator!=(const Bool& l_Bool_ref, const Bool& r_Bool_ref)
{
    return !(l_Bool_ref == r_Bool_ref);
}

bool operator==(const Bool& l_Bool_ref, const bool& r_cbool_ref) {
    return l_Bool_ref.value() == r_cbool_ref;
};

bool operator!=(const Bool& l_Bool_ref, const bool& r_cbool_ref)
{
    return !(l_Bool_ref == r_cbool_ref);
}

bool operator==(const bool& l_cbool_ref, const Bool& r_Bool_ref)
{
    return l_cbool_ref == r_Bool_ref.value();
}

bool operator!=(const bool& l_cbool_ref, const Bool& r_Bool_ref)
{
    return !(l_cbool_ref == r_Bool_ref);
}

std::ostream& operator<<(std::ostream& output, const Bool& ref)
{
    output << ref.value();
    return output;
}

std::ostream& operator<<(std::ostream& output, const std::unique_ptr<Bool>& uptr) 
{
    output << uptr->value();
    return output;
}

std::ostream& operator<<(std::ostream& output, const std::shared_ptr<Bool>& sptr) 
{
    output << sptr->value();
    return output;
}

}
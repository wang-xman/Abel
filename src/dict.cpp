#include "dict.hpp"

namespace abel {

Dict::Dict() {}

Dict::Dict(const Dict& ref) { internal = ref.internal; }

Dict::Dict(const std::shared_ptr<Dict> sptr) { internal = sptr->internal; }

Dict::Dict(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Dict") {
            std::string msg = "Cannot copy-construct a non-dict type of "
                              "(object) shared pointer to a Dict object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Dict>(sptr)->internal;
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Dict::~Dict() {}

Dict& Dict::operator=(const Dict& ref) { return *this; }

Dict& Dict::operator=(const std::shared_ptr<Dict> sptr)
{
    internal = sptr->internal;
    return *this;
}

Dict& Dict::operator=(const std::shared_ptr<object> sptr)
{
    try {
        if (sptr->type_name() != "Dict") {
            std::string msg = "Cannot assign a non-Dict type shared"
                              "pointer of object to a Dict object.";
            throw error::IncompatibleType(msg);
        }
        internal = std::dynamic_pointer_cast<Dict>(sptr)->internal;
    }
    catch (error::IncompatibleType& err) { err.make_show(); }
    catch (std::runtime_error& err) { /* TODO */ }
    return *this;
}

std::string Dict::type_name() const { return type_name_string; }

std::vector<std::string> Dict::keys()
/*
    Returns a list of available keys.
*/
{
    std::vector<std::string> key_vector;
    std::map<std::string, std::shared_ptr<object> >::iterator it;
    for(it = internal.begin(); it != internal.end(); ++it) {
        key_vector.push_back(it->first);
    }
    return key_vector;
}

bool Dict::has_key(const std::string key) const { return internal.count(key); }

std::shared_ptr<object> Dict::get(const std::string key)
/*
    Dict internal `get` method.
    Performs has-key-or-not check, throwing error if not.
*/
{
    try {
        if ( !has_key(key) ) {
            std::string msg = "Key '" + key + "' not found";
            throw error::KeyNotFound(msg);
        }
    } catch (error::KeyNotFound& err) { err.make_show(); }
    return internal[key];
}

std::shared_ptr<object> Dict::operator[](const std::string key)
/*
    Dict value retrieval via key in Python style
*/
{
    return get(key);
}

void Dict::insert(std::pair<std::string, std::shared_ptr<object> > key_value)
/*
    Directly insert a key-value pair
*/
{
    try {
        if ( has_key(key_value.first) ) {
                std::string msg = "Key '" + key_value.first
                                  + "' already exists";
                throw error::DuplicateKey(msg);
        } else {
            internal.insert(key_value);
        }
    } catch (error::DuplicateKey& err) { err.make_show(); }
}

}
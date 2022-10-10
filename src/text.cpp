#include "text.hpp"

namespace abel {

Text::Text() {}

Text::Text(const std::string& str) : internal(str) {}

Text::Text(std::unique_ptr<Text>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Text> temp = std::move(uptr);
    internal = temp->value();
}

Text::Text(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Text") {
            std::string msg = "Cannot copy-contruct a Text object from "
                              "a non-Text type unique pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            // cast it from `object` to `Text`
            internal = std::unique_ptr<Text>(
                    static_cast<Text*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Text::Text(const std::shared_ptr<Text>& sptr) : internal(sptr->value()) {}

Text::Text(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Text") {
            std::string msg = "Cannot copy-contruct a Text object from "
                              "a non-Text type shared pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Text>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
}

Text& Text::operator=(const std::string& c_string_ref)
{
    internal = c_string_ref;
    return *this;
}

Text& Text::operator=(std::unique_ptr<Text>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    std::unique_ptr<Text> temp = std::move(uptr);
    internal = temp->value();
    return *this;
}

Text& Text::operator=(std::unique_ptr<object>& uptr)
/*
    Original unique pointer is moved and is thus invalidated.
*/
{
    try {
        if (uptr->type_name() != "Text") {
            std::string msg = "Cannot assign to a Text object a non-Text "
                              "type unique pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::unique_ptr<Text>(
                    static_cast<Text*>(uptr.release()))->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Text& Text::operator=(const std::shared_ptr<Text>& sptr)
{
    internal = sptr->value();
    return *this;
}

Text& Text::operator=(const std::shared_ptr<object>& sptr)
{
    try {
        if (sptr->type_name() != "Text") {
            std::string msg = "Cannot assign to a Text object a non-Text"
                              " type of shared pointer of object.";
            throw error::IncompatibleType(msg);
        } else {
            internal = std::dynamic_pointer_cast<Text>(sptr)->value();
        }
    } catch (error::IncompatibleType& err) { err.make_show(); }
    return *this;
}

Text::~Text() {}

Text::operator std::string() { return internal; }

std::string Text::type_name() const { return type_name_string; }

std::string Text::value() const { return internal; }

bool operator==(const Text& l_str_ref, const Text& r_str_ref)
{
    return l_str_ref.value() == r_str_ref.value();
};

bool operator!=(const Text& l_str_ref, const Text& r_str_ref)
{
    return !(l_str_ref == r_str_ref);
};

bool operator==(const Text& l_str_ref, const std::string& r_str_ref)
{
    return l_str_ref.value() == r_str_ref;
};

bool operator!=(const Text& l_str_ref, const std::string& r_str_ref)
{
    return !(l_str_ref == r_str_ref);
};

bool operator==(const std::string& l_str_ref, const Text& r_str_ref)
{
    return l_str_ref == r_str_ref.value();
};

bool operator!=(const std::string& l_str_ref, const Text& r_str_ref)
{
    return !(l_str_ref == r_str_ref);
};

std::ostream& operator<<(std::ostream& output, const Text& ref)
{
    output << ref.value();
    return output;
}

std::ostream& operator<<(std::ostream& output, const std::shared_ptr<Text> sptr) 
{
    output << sptr->value();
    return output;
}

}
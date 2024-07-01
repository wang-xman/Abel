#ifndef ABEL_BOOL_HPP
#define ABEL_BOOL_HPP

#include "object.hpp"

namespace abel {

class Bool : public object {
private:
    std::string type_name_string = "Bool";

protected:
    bool internal;

public:
    Bool();
    explicit Bool(const bool&);
    explicit Bool(std::unique_ptr<Bool>&);
    explicit Bool(std::unique_ptr<object>&);
    explicit Bool(const std::shared_ptr<Bool>&);
    explicit Bool(const std::shared_ptr<object>&);

    ~Bool();

    Bool& operator=(const bool&);
    Bool& operator=(std::unique_ptr<Bool>&);
    Bool& operator=(std::unique_ptr<object>&); // TODO not tested
    Bool& operator=(const std::shared_ptr<Bool>&);
    Bool& operator=(const std::shared_ptr<object>&);

    operator bool();

    std::string type_name() const override;
    virtual bool value() const;
};

bool operator==(const Bool&, const Bool&); // Bool == Bool
bool operator!=(const Bool&, const Bool&); // Bool != Bool
bool operator==(const Bool&, const bool&); // Bool == bool
bool operator!=(const Bool&, const bool&); // Bool != bool
bool operator==(const bool&, const Bool&); // bool == Bool
bool operator!=(const bool&, const Bool&); // bool != Bool

std::ostream& operator<<(std::ostream&, const Bool&);
std::ostream& operator<<(std::ostream&, const std::unique_ptr<Bool>&);
std::ostream& operator<<(std::ostream&, const std::shared_ptr<Bool>&);

}
#endif
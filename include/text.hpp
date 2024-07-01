#ifndef ABEL_TEXT_HPP
#define ABEL_TEXT_HPP

#include "object.hpp"

namespace abel {

class Text : public object {
private:
    std::string type_name_string = "Text";

protected:
    std::string internal;

public:
    Text();
    explicit Text(const std::string&);
    explicit Text(std::unique_ptr<Text>&);
    explicit Text(std::unique_ptr<object>&);
    explicit Text(const std::shared_ptr<Text>&);
    explicit Text(const std::shared_ptr<object>&);

    // Don't override the default.
    Text& operator=(const std::string&);
    Text& operator=(std::unique_ptr<Text>&);
    Text& operator=(std::unique_ptr<object>&);
    Text& operator=(const std::shared_ptr<Text>&);
    Text& operator=(const std::shared_ptr<object>&);

    ~Text();

    operator std::string();

    std::string type_name() const override;

    virtual std::string value() const;
};

bool operator==(const Text&, const Text&);        // Text == Text
bool operator!=(const Text&, const Text&);        // Text != Text
bool operator==(const Text&, const std::string&); // Text == std::string
bool operator!=(const Text&, const std::string&); // Text != std::string
bool operator==(const std::string&, const Text&); // std::string == Text
bool operator!=(const std::string&, const Text&); // std::string != Text

std::ostream& operator<<(std::ostream&, const Text&);
std::ostream& operator<<(std::ostream&, const std::shared_ptr<Text>);

}
#endif
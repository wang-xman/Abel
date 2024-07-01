#ifndef ABEL_CONTAINER_PARSER_HPP
#define ABEL_CONTAINER_PARSER_HPP

#include "parser.hpp"

namespace abel {

template <typename TokenT, typename ContainerT, typename SchemeT>
class container_parser : public parser<TokenT> {
protected:
    int current_level = 0;

    int deepest_level = 0;

    // must be initialised by subclass
    std::vector<ContainerT> current_container_type;

    std::vector<int> current_iter_index = {0};

    std::vector<std::string> parent_key = {"ROOT_KEY_"};

    std::vector<std::vector<TokenT> > keys_per_level = {{}};

    std::string latest_syntactic_operator = "";

    bool is_escaping = false;

    bool is_delimited_string_open = false;

    // must be initialised by subclass
    SchemeT current_literal_scheme;

    ContainerT get_current_container_type()
    {
        return current_container_type[current_level];
    }
    
    ContainerT get_parent_container_type()
    {
        return current_container_type[current_level - 1];
    }

    void enter_deeper_level() { current_level += 1; }

    void enter_higher_level() { current_level -= 1; }

    // Operational methods
    
    bool is_first_noncomment_character()
    {
        return (this->current_literal == "" && this->token_vector.size() == 0);
    }

    void illegal_first_noncomment_character(const std::string& first_char)
    {
        std::string msg = "Symbol " + first_char
                          + " cannot be the first character.";
        error::SyntaxError err = error::SyntaxError(msg);
        err.set_line(this->current_line);
        throw err;
    }

    // Workflow methods

    virtual void per_space()
    {
        if (is_delimited_string_open) {
            this->current_literal += symbol::SPACE;
        }
        this->current_column += 1;
    }
    
    virtual void per_back_slash()
    {
        if (is_delimited_string_open) {
            if (is_escaping) {
                this->current_literal += symbol::BACK_SLASH;
                // switch off escaping flag after appending the char.
                is_escaping = false;
            } else { 
                is_escaping = true;
            }
        } else { 
            this->current_literal += symbol::BACK_SLASH;
        }
        this->current_column += 1;
    }

public:
    ContainerT get_root_container_type() const
    {
        return current_container_type[0];
    }

    void display()
    {
        for (const TokenT& item : this->token_vector) {
            std::cout << item << ", " << std::endl;
        }
        std::cout << std::endl;
    }
};

}
#endif
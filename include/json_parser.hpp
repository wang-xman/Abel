#ifndef ABEL_JSON_PARSER_HPP
#define ABEL_JSON_PARSER_HPP

#include "json_token.hpp"
#include "container_parser.hpp"

namespace abel {

class JsonParser
    : public container_parser<JsonToken, JsonContainerType, LiteralScheme> {
protected:
    friend class JsonLoader;

    /// Utility objects ///
    DelimiterMatch bracket_match;

    void set_root_container_type(const JsonContainerType&);

    bool is_current_container_iterable();

    virtual JsonTerminalType get_terminal_type(
        const std::string&, const LiteralScheme&);

    /// Operational methods ///
    void report_duplicate_key(const JsonToken&);

    void make_and_push_key_token();

    void per_iterable_container();

    void per_pushing_terminal_token();

    void make_and_push_terminal_token();

    void per_pushing_container_opening_token(const std::string&);

    void make_and_push_container_opening_token(const std::string&);

    void make_and_push_container_closing_token(const std::string&);

    // Workflow methods
    void per_double_quotation();

    void per_colon();

    void per_comma();

    void per_container_opening(const std::string&);

    void per_container_closing(const std::string&);
    
    void per_end_of_line();

    void per_other_symbol(const std::string&);
    
    void per_end_of_file();

    // Controllers
    void parse_line(std::string);

    // Overrides the virtual method in `parser` template
    void parse_file(std::ifstream& /* input file stream */) override;

    void parse_string(std::string& /* input string */) override;

public:
    JsonParser();

    ~JsonParser();
};

}
#endif
#ifndef ABEL_PARSER_HPP
#define ABEL_PARSER_HPP

#include "delimiter.hpp"
#include "converter.hpp"

namespace abel {

template <typename T> class parser {
protected:
    std::vector<T> token_vector = {};

    int current_line = 0;

    int current_column = 0;

    std::string current_literal = "";

    std::string latest_symbol = "";

    size_t size() { return token_vector.size(); }

    void push(const T token) { token_vector.push_back(token); }

    void reset_current_literal() { current_literal = ""; }

    virtual void parse_file(std::ifstream& /* input_file_stream */) {};

    virtual void parse_string(std::string& /* input_string */) {};

public:
    parser() {}

    virtual ~parser() = default;

    virtual void parse(std::ifstream& input_file_stream)
    /*
        Parses a file stream. Errors are caught and thrown.
    */
    {
        try {
            if ( !input_file_stream.is_open() ) { // throw error if fails to
                                                  // open file
                throw error::InvalidInput("Invalid input file for parsing.");
            } else {
                parse_file(input_file_stream);
                input_file_stream.close();
            }
        } catch (error::BaseError& err) {
            err.make_show();
            throw;
        }
    }

    virtual void parse(std::string& input_string)
    /*
        Parses a string. Errors are caught and thrown.
    */
    {
        try {
            if ( input_string == "" ) {
                throw error::InvalidInput("Invalid input string for parsing.");
            } else {
                parse_string(input_string);
            }
        } catch (error::BaseError& err) {
            err.make_show();
            throw;
        }
    }

    const std::vector<T>& get_token_vector() const { return token_vector; }
};

}
#endif
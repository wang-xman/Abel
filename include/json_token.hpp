#ifndef _ABEL_JSON_TOKEN_HPP_
#define _ABEL_JSON_TOKEN_HPP_

#include "token.hpp"

namespace abel {

enum class JsonTokenType {
    Key, IterKey, Terminal, DictOpening, DictClosing,
    ListOpening, ListClosing };
extern const std::vector<std::string> JsonTokenTypeString;
std::string get_json_token_type_string(const JsonTokenType&);

enum class JsonContainerType { None, List, Dict };
extern const std::vector<std::string> JsonContainerTypeString;
std::string get_json_container_type_string(const JsonContainerType&);

enum class LiteralScheme { None, Delimited, Liberal };
extern const std::vector<std::string> LiteralSchemeString;
std::string get_literal_scheme_string(const LiteralScheme&);

// used in both JsonParser and JsonPlusParser
enum class JsonTerminalType {
    None, Null, Bool, Double, Text, Integer, Complex,
    Binary, Bitstring };
extern const std::vector<std::string> JsonTerminalTypeString;
std::string get_json_terminal_type_string(const JsonTerminalType&);

struct JsonToken : public Token<JsonTokenType> {
    std::string parent_key = "";
    int level = -99;
    int line  = -99;
    JsonContainerType container_type;
    int iter_index = -99;
    JsonTerminalType terminal_type; 
    LiteralScheme literal_scheme;
    std::string referenced_type = "";
};

JsonToken tokenize_iter_key(
    const std::string&       /* literal */,
    const JsonTokenType&     /* type */,
    const std::string&       /* parent_key */,
    const int&               /* level */,
    const int&               /* line */,
    const JsonContainerType& /* container_type */,
    const int&               /* iter_index */
);

JsonToken tokenize_terminal(
    const std::string&       /* literal */,
    const JsonTokenType&     /* type */,
    const std::string&       /* parent_key */,
    const int&               /* level */,
    const int&               /* line */,
    const JsonContainerType& /* container_type */,
    const JsonTerminalType&  /* terminal_type */,
    const LiteralScheme&     /* collection scheme */
);

JsonToken tokenize_key(
    const std::string&       /* literal */,
    const JsonTokenType&     /* type */,
    const std::string&       /* parent_key */,
    const int&               /* level */,
    const int&               /* line */,
    const JsonContainerType& /* container_type */,
    const LiteralScheme&     /* collection scheme */
);

JsonToken tokenize(
    const std::string&       /* literal */,
    const JsonTokenType&     /* type */,
    const std::string&       /* parent_key */,
    const int&               /* level */,
    const int&               /* line */,
    const JsonContainerType& /* container_type */
);

std::string token_to_string(const JsonToken&);

std::ostream& operator<<(std::ostream&, const JsonToken&);

JsonTokenType get_token_type_by_symbol(const std::string&);

JsonContainerType get_container_type_by_symbol(const std::string&);

bool is_iterable_container(const JsonContainerType&);

}
#endif
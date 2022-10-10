#include "json_token.hpp"

namespace abel {

const std::vector<std::string> JsonTokenTypeString {
    "Key", "IterKey", "Terminal", "DictOpening", "DictClosing",
    "ListOpening", "ListClosing" };

std::string get_json_token_type_string(const JsonTokenType& type)
{
    return JsonTokenTypeString[static_cast<int>(type)];
}

const std::vector<std::string> JsonContainerTypeString {
    "None", "List", "Dict" };
std::string get_json_container_type_string(const JsonContainerType& type)
{
    return JsonContainerTypeString[static_cast<int>(type)]; 
}

const std::vector<std::string> LiteralSchemeString {
    "None", "Delimited", "Liberal" };
std::string get_literal_scheme_string(const LiteralScheme& type)
{
    return LiteralSchemeString[static_cast<int>(type)];
}

const std::vector<std::string> JsonTerminalTypeString {
    "None", "Null", "Bool", "Double", "Text", "Integer", "Complex",
    "Binary", "Bitstring" };
std::string get_json_terminal_type_string(const JsonTerminalType& type)
{
    return JsonTerminalTypeString[static_cast<int>(type)];
}

JsonToken tokenize_iter_key(const std::string& literal, const JsonTokenType& type,
        const std::string& pk, const int& level, const int& line,
        const JsonContainerType& container_type, const int& iter_index)
{
    JsonToken iter_key_token;
    if (type == JsonTokenType::IterKey) {
        iter_key_token.literal    = literal;
        iter_key_token.type       = JsonTokenType::IterKey;
        iter_key_token.parent_key = pk;
        iter_key_token.level      = level;
        iter_key_token.line       = line;
        iter_key_token.container_type = container_type;
        iter_key_token.iter_index = iter_index;
    } else {
        std::string errmsg = "Member 'iter_index' is only "
                             "for token of type Iter_Key.";
        throw error::TokenizationError(errmsg);
    }
    return iter_key_token;
}

JsonToken tokenize_terminal(const std::string& literal,
        const JsonTokenType& type, const std::string& pk, const int& level,
        const int& line, const JsonContainerType& container_type,
        const JsonTerminalType& terminal_type, const LiteralScheme& scheme)
{
    JsonToken terminal_token;
    if (type == JsonTokenType::Terminal) {
        terminal_token.literal       = literal;
        terminal_token.type          = JsonTokenType::Terminal;
        terminal_token.parent_key    = pk;
        terminal_token.level         = level;
        terminal_token.line          = line;
        terminal_token.container_type= container_type;
        terminal_token.terminal_type = terminal_type;
        terminal_token.literal_scheme = scheme;
    } else {
        std::string errmsg = "Member 'terminal_type' is only "
                             "for token of type Terminal.";
        throw error::TokenizationError(errmsg);
    }
    return terminal_token;
}

JsonToken tokenize_key(const std::string& literal, const JsonTokenType& type,
        const std::string& pk, const int& level, const int& line,
        const JsonContainerType& container_type, const LiteralScheme& scheme)
{
    JsonToken key_token;
    if (type == JsonTokenType::Key) {
        key_token.literal        = literal;
        key_token.type           = JsonTokenType::Key;
        key_token.parent_key     = pk;
        key_token.level          = level;
        key_token.line           = line;
        key_token.container_type = container_type;
        key_token.literal_scheme = scheme;
    } else {
        std::string errmsg = "Member 'literal_collection_scheme' is only "
                             "for token of type Key or Terminal.";
        throw error::TokenizationError(errmsg);
    }
    return key_token;
}

JsonToken tokenize(const std::string& literal, const JsonTokenType& type,
                   const std::string& pk, const int& level, const int& line,
                   const JsonContainerType& container_type)
{
    JsonToken token;
    if (type == JsonTokenType::IterKey) {
        throw error::TokenizationError("Token of type 'IterKey' "
                "requires an iter_index.");
    } else if (type == JsonTokenType::Terminal) {
        throw error::TokenizationError("Token of 'Terminal' type must "
                "specify terminal_type and literal_collection_scheme");
    } else if (type == JsonTokenType::Key) {
        throw error::TokenizationError("Token of 'Key' type must "
                "specify a literal_collection_scheme.");
    } else {
        token.literal        = literal;
        token.type           = type;
        token.parent_key     = pk;
        token.level          = level;
        token.line           = line;
        token.container_type = container_type;
    }
    return token;
}

std::string token_to_string(const JsonToken& token)
/*
    Personalise string for each token type. Variable `stem` stringifies
    common fields, each token type has its own extra fields to be added
    Iterkey : has `iter_index` and `referenced_type`
    Terminal : has `terminal_type` and `literal_scheme`
    Key : has `literal_scheme` and `referenced_type`
*/
{
    std::string stem = "Line:" + std::to_string(token.line) + ", "
                       + "Literal:" + token.literal + ", "
                       + "Type:" + get_json_token_type_string(token.type) + ", "
                       + "PK:" + token.parent_key + ", "
                       + "Level:" + std::to_string(token.level) + ", "
                       + "ContainerType:"
                       + get_json_container_type_string(token.container_type);
    std::string full_string;
    if (token.type == JsonTokenType::IterKey) {
        full_string = "( " + stem + ", "
                      + "IterIndex:" + std::to_string(token.iter_index) + ", "
                      + "ReferencedType:" + token.referenced_type
                      + " )";
    } else if (token.type == JsonTokenType::Terminal) {
        full_string = "( " + stem + ", "
                      + "TerminalType:"
                      + get_json_terminal_type_string(token.terminal_type) + ", "
                      + "LiteralScheme:"
                      + get_literal_scheme_string(token.literal_scheme)
                      + " )";
    } else if (token.type == JsonTokenType::Key) {
        full_string = "( " + stem + ", "
                      + "ReferencedType:" + token.referenced_type + ", "
                      + "LiteralScheme:"
                      + get_literal_scheme_string(token.literal_scheme)
                      + " )";
    } else {
        full_string = "( " + stem + " )";
    }
    return full_string;
}

std::ostream& operator<<(std::ostream& output, const JsonToken& token)
{
    output << token_to_string(token);
    return output;
}

JsonTokenType get_token_type_by_symbol(const std::string& symbol_str)
/*
    Get container opening (clsoing) token type string by
    opening (closing) symbol. Not for all tokens
*/
{
    JsonTokenType token_type;
    if (symbol_str == symbol::L_BRACE) {
        token_type = JsonTokenType::DictOpening;
    } else if (symbol_str == symbol::R_BRACE) {
        token_type = JsonTokenType::DictClosing;
    } else if (symbol_str == symbol::L_BRACKET) {
        token_type = JsonTokenType::ListOpening;
    } else if (symbol_str == symbol::R_BRACKET) {
        token_type = JsonTokenType::ListClosing;
    } else {
        throw error::UnrecognizedSymbol(
            "Failed to determine JSON token type by symbol.");
    }
    return token_type;
}

JsonContainerType get_container_type_by_symbol(const std::string& opening_sym)
/*
    Returns container type, either Dict or List, by opening symbol.
    JSON format accepts only two types of containers
*/
{
    JsonContainerType container_type;
    if (opening_sym == symbol::L_BRACE) {
        container_type = JsonContainerType::Dict;
    } else if (opening_sym == symbol::L_BRACKET) {
        container_type = JsonContainerType::List;
    } else {
        throw error::UnrecognizedSymbol("Container type is determined "
                                        "only by an opening symbol.");
    }
    return container_type;
}

bool is_iterable_container(const JsonContainerType& type)
{
    return type == JsonContainerType::List;
}

}
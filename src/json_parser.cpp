#include "json_parser.hpp"

namespace abel {

JsonParser::JsonParser()
/*
    Must initialise the following two members.
*/
{
    current_container_type = {JsonContainerType::None};
    current_literal_scheme = LiteralScheme::None;
}

JsonParser::~JsonParser() {}

void JsonParser::set_root_container_type(const JsonContainerType& container_type)
{
    if (container_type != JsonContainerType::None) {
        if (current_container_type[0] == JsonContainerType::List
            || current_container_type[0] == JsonContainerType::Dict)
        {
            std::string msg = "Manually override the root container which "
                    "has already been set to "
                    + get_json_container_type_string(current_container_type[0])
                    + " .";
            error::SyntaxError err = error::SyntaxError(msg);
            throw err;
        } else {
            current_container_type[0] = container_type;
        }
    } else {
        std::string msg = "Unknown type for root container. "
                          "Root container type can be either List or Dict.";
        error::SyntaxError err = error::SyntaxError(msg);
        throw err;
    }
}

bool JsonParser::is_current_container_iterable()
{
    return get_current_container_type() == JsonContainerType::List;
}

JsonTerminalType JsonParser::get_terminal_type(
        const std::string& literal, const LiteralScheme& scheme)
/*
    Determines JSON terminal data type by literal and its
    collection scheme.
*/
{
    JsonTerminalType terminal_type;
    if (scheme == LiteralScheme::Liberal) {
        if ( converter::is_null(literal) ) {
            terminal_type = JsonTerminalType::Null;
        } else if ( converter::is_bool(literal) ) {
            terminal_type = JsonTerminalType::Bool;
        } else if ( converter::is_double(literal) ) {
            terminal_type = JsonTerminalType::Double;
        } else {
            std::string msg = "Type of unquoted string '" + literal
                              + "' cannot be recognised.";
            error::SyntaxError err = error::SyntaxError(msg);
            err.set_line(current_line);
            throw err;
        }
    } else if (scheme == LiteralScheme::None) {
        std::string msg = "Collection scheme of '" + literal + "' is not set.";
        error::SyntaxError err = error::SyntaxError(msg);
        err.set_line(current_line);
        throw err;
    } else {
        // delimited string is always considered as text
        terminal_type = JsonTerminalType::Text;
    }
    return terminal_type;
}

void JsonParser::report_duplicate_key(const JsonToken& token)
/*
    JSON forbids duplicate keys.
*/
{
    bool is_duplicate = false;
    std::string msg = "";
    if (keys_per_level.size() <= (size_t)current_level) {
    /// Keys at this level don't exist, so collect it.
        keys_per_level.push_back({token});
    } else {
        //bool is_duplicate = false;
        for (auto& token_in : keys_per_level[current_level]) {
            if (token_in.parent_key == token.parent_key
                    && token_in.literal == token.literal) {
                is_duplicate = true;
                msg = "Key '" + token.literal + "' is a duplicate.";
            }
        }
        if (is_duplicate == false) {
            // If no duplicate, collect the key.
            keys_per_level[current_level].push_back(token);
        } else {
            // Throw duplicate key error.
            error::DuplicateKey err = error::DuplicateKey(msg);
            err.set_line(current_line);
            throw err;
        }
    }
}

void JsonParser::make_and_push_key_token()
{
    std::string msg = "";
    error::SyntaxError err;
    if (get_current_container_type() != JsonContainerType::Dict) {
    /// current container must be dictionary
        msg = "Key is meaningful only in dictionary.";
    }
    /// previous token cannot be key
    if (token_vector.size() > 0 && token_vector.back().type == JsonTokenType::Key) {
        msg = "Key cannot follow a key immediately.";
    }
    // Important: JSON keys must be all in delimited scheme
    if (current_literal_scheme == LiteralScheme::Delimited) {
        JsonToken key_token = tokenize_key(
            current_literal,
            JsonTokenType::Key,
            parent_key[current_level],
            current_level,
            current_line,
            get_current_container_type(),
            current_literal_scheme);
        push(key_token);
        report_duplicate_key(key_token);
    } else {
        msg = "Key '" + current_literal + "' isn't quoted. "
              "Keys in JSON must be enclosed in double-quotation marks.";
    }
    if (msg != "") { // if error, throw.
        err.set_line(current_line);
        err = error::SyntaxError(msg);
        throw err;
    } else {
        /// Set parent key for the next level.
        if (parent_key.size() >= (size_t)current_level + 2) {
            parent_key[current_level + 1] = current_literal;
        } else {
            // This key becomes the parent key for the next level.
            parent_key.push_back(current_literal);
        }
    }
}

void JsonParser::per_iterable_container()
{
    if ( is_current_container_iterable() ) {
        if (current_iter_index.size() == 0) {
            current_iter_index.push_back(0);
        }
        std::string name_string = std::to_string(current_iter_index[current_level]);
        JsonToken iter_key_token = tokenize_iter_key(
            name_string,
            JsonTokenType::IterKey,
            parent_key[current_level],
            current_level,
            current_line,
            get_current_container_type(),
            current_iter_index[current_level]);
        push(iter_key_token);
        // update parent key
        if (parent_key.size() >= (size_t)current_level + 2) {
            parent_key[current_level + 1] = name_string;
        } else {
            parent_key.push_back(name_string);    
        }
    }
}

void JsonParser::per_pushing_terminal_token()
{
    int veclen = token_vector.size();
    if ( !(token_vector[veclen - 1].type == JsonTokenType::Key
            || token_vector[veclen - 1].type == JsonTokenType::IterKey) )
    {
        std::string msg = "A terminal value isn't preceeded by a key "
                          "or an iteration key.";
        error::SyntaxError err = error::SyntaxError(msg);
        err.set_line(current_line);
        throw err;
    } else {
        // update previous key's referenced type
        token_vector[veclen - 1].referenced_type = "Terminal";
    }
}

void JsonParser::make_and_push_terminal_token()
{
    per_iterable_container();
    JsonTerminalType terminal_type = get_terminal_type(
            current_literal, current_literal_scheme);
    JsonToken terminal_token = tokenize_terminal(
        current_literal,
        JsonTokenType::Terminal,
        parent_key[current_level + 1], // Note the level for PK
        current_level,
        current_line,
        get_current_container_type(),
        terminal_type,
        current_literal_scheme);
    per_pushing_terminal_token();
    push(terminal_token);
}

void JsonParser::per_pushing_container_opening_token(const std::string& opening_symbol)
/*
    In a dict container, any opening token must be preceeded
    by a key token. However, if the opening token is the first
    of the entire text, this is not required as an implicit
    key is assgined to it.

    TODO Merge the following logics, it is a bit messy!
*/
{
    if (token_vector.size() > 0) { // not the first char in text
        int veclen = token_vector.size();
        if (get_current_container_type() == JsonContainerType::Dict) {
            if (token_vector[veclen - 1].type != JsonTokenType::Key) {
                std::string errmsg = "In a dictionary, any object "
                                     "must be preceeded by a key.";
                error::SyntaxError err = error::SyntaxError(errmsg);
                err.set_line(current_line);
                throw err;
            } else {
            /// Update reference type according to the container to be created.    
                if (opening_symbol == symbol::L_BRACE) {
                    token_vector[veclen - 1].referenced_type = "Dict";
                } else if (opening_symbol == symbol::L_BRACKET) {
                    token_vector[veclen - 1].referenced_type = "List";
                }
            }
        }
        
        if ( is_current_container_iterable() ) {
            if (token_vector[veclen - 1].type != JsonTokenType::IterKey) {
                std::string errmsg = "In a iterable container, any object "
                                     "must be preceeded by an iter key.";
                error::SyntaxError err = error::SyntaxError(errmsg);
                err.set_line(current_line);
                throw err;
            } else {
                // TODO Make a function to update last token.
                if (opening_symbol == symbol::L_BRACE) {
                    token_vector[veclen - 1].referenced_type = "Dict";
                } else if (opening_symbol == symbol::L_BRACKET) {
                    token_vector[veclen - 1].referenced_type = "List";
                }
            }
        }
    }
}

void JsonParser::make_and_push_container_opening_token(const std::string& opening_symbol)
{
    per_iterable_container();
    per_pushing_container_opening_token(opening_symbol);
    JsonToken opening_token = tokenize(
        opening_symbol,
        get_token_type_by_symbol(opening_symbol),
        parent_key[current_level + 1], // Note the level
        current_level,
        current_line,
        get_current_container_type() );
    push(opening_token);
}

void JsonParser::make_and_push_container_closing_token(const std::string& closing_symbol)
{
    // Caution. Before pushing closing token, adjust the
    // iter-key at this level.
    if (get_current_container_type() == JsonContainerType::List) {
        current_iter_index[current_level] = 0;
    }
    JsonToken closing_token = tokenize(
        closing_symbol,
        get_token_type_by_symbol(closing_symbol),
        parent_key[current_level],
        current_level - 1,
        current_line,
        // Caution. Must use the container of the outer (higher) level, since
        // level switching is performed after pushing the closing token.
        current_container_type[current_level - 1]);
    push(closing_token);
}

/// Workflow method ///

void JsonParser::per_double_quotation()
/*
    JSON respects two-character escaping sequence
*/
{
    if (current_literal == "") { // current literal is empty
        if (!is_delimited_string_open) { // not in a delimited string
            is_delimited_string_open = true;
            current_literal_scheme = LiteralScheme::Delimited;
        } else { // already inside a delimited string
            is_delimited_string_open = false;
            latest_syntactic_operator = symbol::DOUBLE_QUOTE;
        }
    } else { // current literal is non-empty
        if (is_delimited_string_open) { // a delimited string has opened...
            if (is_escaping) { // previous char is escaping
                current_literal += symbol::DOUBLE_QUOTE;
                is_escaping = false; // turn off flag
            } else { // then double quote is a string-closing operator
                is_delimited_string_open = false;
                latest_syntactic_operator = symbol::DOUBLE_QUOTE;
            }
        } else { // delimited string is not open
            if (current_literal_scheme == LiteralScheme::Liberal) {
                current_literal += symbol::DOUBLE_QUOTE;
            } else {
                // If not LIBERAL scheme, the previous quoted string has been
                // closed; this quotation mark starts a new delimited string.
                // This algorithm allows a delimited string to be broken into
                // multiple lines.
                is_delimited_string_open = true;
            }
        }
    }
    current_column += 1;
}

void JsonParser::per_colon()
{
    if (is_delimited_string_open) {
        current_literal += symbol::COLON;
    } else {
        /// Pre-tokenization syntax checks
        std::string msg = "";
        error::SyntaxError err;
        if ( is_first_noncomment_character() ) {
            illegal_first_noncomment_character(symbol::COLON);
        }
        if ( is_current_container_iterable() ) {
            msg = "Colon operator is meaningless.";
        }
        if (current_literal.size() == 0) {
            msg = "Colon operator must appear after "
                  "a non-empty key token.";
        }
        if (latest_syntactic_operator == symbol::COLON) {
            msg = "Colon operator cannot appear immediately "
                  "after a colon operator.";
        }
        if (msg != "") {
            err = error::SyntaxError(msg);
            err.set_line(current_line);
            throw err;
        }
        if (current_literal.size() > 0) {
            if (current_container_type[0] == JsonContainerType::None) {
                set_root_container_type(JsonContainerType::Dict); 
            }
            make_and_push_key_token();
            reset_current_literal();
            latest_syntactic_operator = symbol::COLON;
        }
    }
    current_column += 1; // move on
}

void JsonParser::per_comma()
{
    if (is_delimited_string_open) {
        current_literal += symbol::COMMA;
    } else {
        // Syntax checks
        if ( is_first_noncomment_character() ) {
            illegal_first_noncomment_character(symbol::COMMA);
        }
        if (current_literal.size() == 0) {
            if ( !(latest_syntactic_operator == symbol::DOUBLE_QUOTE
                    || latest_syntactic_operator == symbol::R_BRACE
                    || latest_syntactic_operator == symbol::R_BRACKET) ) {
                std::string msg = "Comma can only appear after a terminal, "
                                  "a string, or a container closing operator.";
                error::SyntaxError err = error::SyntaxError(msg);
                err.set_line(current_line);
                throw err;    
            }
        }
        if ( current_literal.size() > 0
             || (current_literal.size() == 0
                 && latest_syntactic_operator == "\"") ) {
            if (current_container_type[0] == JsonContainerType::None) {
                set_root_container_type(JsonContainerType::List);
            }
            make_and_push_terminal_token();
            reset_current_literal();
            current_iter_index[current_level] += 1;
        }
        // Post-pushing check
        JsonTokenType last_token_type = token_vector.back().type;
        if ( !(last_token_type == JsonTokenType::Terminal
                || last_token_type == JsonTokenType::DictClosing
                || last_token_type == JsonTokenType::ListClosing) ) {
            std::string msg = "Comma is meaningless.";
            error::SyntaxError err = error::SyntaxError(msg);
            err.set_line(current_line);
            throw err;    
        }
        latest_syntactic_operator = symbol::COMMA;
    }
    current_column += 1;
}

void JsonParser::per_container_opening(const std::string& opening_symbol)
{
    JsonContainerType container_type = get_container_type_by_symbol(opening_symbol);
    if (is_delimited_string_open) {
        current_literal += opening_symbol;
    } else {
        if ( is_first_noncomment_character() ) {
            if (current_container_type[0] == JsonContainerType::None) { 
                set_root_container_type(JsonContainerType::List);
            }
            if (parent_key.size() == 1) {
                parent_key.push_back(parent_key[current_level]);
            }
        }
        bracket_match.match(opening_symbol, current_line, current_column);
        // Must update container type for the next level.
        if (current_container_type.size() >= (size_t)current_level + 2) {
            current_container_type[current_level + 1] = container_type;
        } else {
            current_container_type.push_back(container_type);
        }
        make_and_push_container_opening_token(opening_symbol);
        enter_deeper_level();
        current_iter_index.push_back(0);
        // update deepest level
        if (current_level > deepest_level) {
            deepest_level = current_level;
        }
        latest_syntactic_operator = opening_symbol;
    }
    current_column += 1;
}

void JsonParser::per_container_closing(const std::string& closing_symbol)
{
    if (is_delimited_string_open) {
        current_literal += closing_symbol;
    } else { // Liberal string
        if ( is_first_noncomment_character() ) {
            illegal_first_noncomment_character(closing_symbol);
        }
        bracket_match.match(closing_symbol, current_line, current_column);
        // Current literal is not empty
        if (current_literal.size() > 0) {
            make_and_push_terminal_token();
            reset_current_literal();
        }
        make_and_push_container_closing_token(closing_symbol);
        // FIXME The following iter-key adjustment doesn't seem to work.
        if ( is_iterable_container(current_container_type[current_level - 1]) ) {
            current_iter_index[current_level] = 0;
            current_iter_index[current_level - 1] += 1;
        }
        enter_higher_level();
        latest_syntactic_operator = closing_symbol;
    }
    current_column += 1;
}

// TODO Liberal string is very limited in JSON.
void JsonParser::per_other_symbol(const std::string& current_char)
{
    // Current literal is empty, new literal collection starts...
    if (current_literal.size() == 0) {
        // If inside delimited string is on, this is just after double
        // quotation mark, simply append the character
        if (is_delimited_string_open) {
            current_literal += current_char;
        } else {
            current_literal_scheme = LiteralScheme::Liberal;
            current_literal += current_char;
        }
    } else {
    // Current literal is non-empty
        if (is_delimited_string_open == false && current_literal_scheme == LiteralScheme::Delimited)
        {
            // A delimited string is before this character, for example
            // "first"name, i.e. appending a liberal string to a delimited
            // one is not allowed.
            std::string msg = "Appending a liberal string to a "
                              "delimited one is not allowed.";
            error::SyntaxError err = error::SyntaxError(msg);
            err.set_line(current_line);
            throw err; 
        } else {
            current_literal += current_char;
        }
    }
    current_column += 1;
}

void JsonParser::per_end_of_file()
/*
    TODO Better rename it since it can be used to parse a
    multiline string, not just file.
*/
{
    if (current_literal != "") {
        make_and_push_terminal_token();
    }
    reset_current_literal();
}

void JsonParser::parse_line(std::string line)
{
    while ( current_column < (int) line.length() ) {
        // convert char into string
        std::string current_char = std::string(1, line[current_column]);
        if (current_char == symbol::BACK_SLASH) {
            per_back_slash(); // use container_parser default
            continue;
        } else if (current_char == symbol::DOUBLE_QUOTE) {
            per_double_quotation();
            continue;
        } else if (current_char == symbol::SPACE) {
            per_space(); // use container_parser default
            continue;
        } else if (current_char == symbol::SHARP) { // at # symbol
            if (is_delimited_string_open) {
                current_literal += current_char;
            } else {
                break;
            }
            current_column += 1;
            continue;
        } else if (current_char == symbol::COLON) {
            per_colon();
            continue;
        } else if (current_char == symbol::COMMA) {
            per_comma();
            continue;
        } else if ( util::is_opening_symbol(current_char) ) {
        // at an opening symbol
            per_container_opening(current_char);
            continue;
        } else if ( util::is_closing_symbol(current_char) ) {
        // at a closing symbol
            per_container_closing(current_char);
            continue;
        } else {
        // none of the above
            per_other_symbol(current_char);
            continue;
        }
    }
}

void JsonParser::parse_string(std::string& src_string)
/*
    Parses a string that conforms to JSON format.
    Overrides virtual method in super class `parser::parse_string()`.
    Invoked by `parser::parse()`

    CAUTION! Entire string, regardless the presence of line breaking
    symbol, is regarded as one line.
*/
{
    current_line += 1;
    current_column = 0;
    parse_line(src_string);

    per_end_of_file();
    if ( !bracket_match.are_all_matched() ) { // unpaired brackets, throw error
        throw error::UnpairedBrackets("Unpaired brackets found.");
    }
}

void JsonParser::parse_file(std::ifstream& input_file_stream)
/*
    Parses an input file given in file stream.
    Overrides virtual method in super class `parser::parse_file()`.
    Invoked by `parser::parse()`
*/
{
    std::string line;
    // begin: inter-line iteration
    // Each line is considered a string
    while ( std::getline(input_file_stream, line) ) {
        current_line += 1;
        current_column = 0;
        // If an empty line, skip and continue to the next line
        if (line.length() == 0) continue; 
        parse_line(line);
    } // end: inter-line iteration
    
    // At the end of file, the last string must be tokenized.
    // This string can only be a terminal.
    per_end_of_file();
    if ( !bracket_match.are_all_matched() ) {
    /// Unpaired brackets found, throw error
        throw error::UnpairedBrackets("Unpaired brackets found.");
    }
}

}
#ifndef ABEL_JSON_PLUS_PARSER_HPP
#define ABEL_JSON_PLUS_PARSER_HPP

#include "json_parser.hpp"

namespace abel {

class JsonPlusParser : public JsonParser {
protected:
    friend class JsonPlusLoader;
    
    JsonTerminalType get_terminal_type(const std::string&,
                                       const LiteralScheme&) override;

public:
    JsonPlusParser();
    
    ~JsonPlusParser();
};

}
#endif
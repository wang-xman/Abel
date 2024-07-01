#ifndef ABEL_JSON_PLUS_LOADER_HPP
#define ABEL_JSON_PLUS_LOADER_HPP

#include "json_plus_parser.hpp"
#include "json_loader.hpp"

namespace abel {

class JsonPlusLoader : public JsonLoader {
protected:
    template <typename Tc, typename Tk, typename Tt>
    void set_json_plus_terminal(std::shared_ptr<Tc>& cnt_sptr_ref,
                                const Tk& key, const Tt& token)
    {
        std::string value = token.literal;
        if (token.terminal_type == JsonTerminalType::Null) {
            cnt::set( cnt_sptr_ref, key, converter::as_null(value) );
        } else if (token.terminal_type == JsonTerminalType::Bool) {
            cnt::set( cnt_sptr_ref, key, converter::as_bool(value) );
        } else if (token.terminal_type == JsonTerminalType::Integer) {
            cnt::set( cnt_sptr_ref, key, converter::as_integer(value) );
        } else if (token.terminal_type == JsonTerminalType::Double) {
            cnt::set( cnt_sptr_ref, key, converter::as_double(value) );
        } else if (token.terminal_type == JsonTerminalType::Complex) {
            cnt::set( cnt_sptr_ref, key, converter::as_complex(value) );
        } else if (token.terminal_type == JsonTerminalType::Binary) {
            cnt::set( cnt_sptr_ref, key, converter::as_binary(value) );
        } else if (token.terminal_type == JsonTerminalType::Bitstring) {
            cnt::set( cnt_sptr_ref, key, converter::as_bitstring(value) );
        }
        else {
            // set item as Text
            cnt::set(cnt_sptr_ref, key, value);
        }
    }

    void put_into(std::shared_ptr<Dict>&, const std::string&,
                  const JsonToken&) override;

    void put_into(std::shared_ptr<List>&, const int&,
                  const JsonToken&) override;

public:
    JsonPlusLoader();

    ~JsonPlusLoader();

    void load_from_parser(const JsonPlusParser&, const std::shared_ptr<Dict>&);

    void load_from_file(const std::string&, const std::shared_ptr<Dict>&);
};

}
#endif
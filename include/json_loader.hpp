#ifndef ABEL_JSON_LOADER_HPP
#define ABEL_JSON_LOADER_HPP

#include "container_loader.hpp"
#include "json_parser.hpp"

namespace abel {

class JsonLoader : public container_loader<JsonToken, JsonContainerType> {
protected:

    template <typename Tc, typename Tk, typename Tt>
    void set_json_terminal(std::shared_ptr<Tc>& cnt_sptr_ref,
                           const Tk& key, const Tt& token)
    /*
        Template method that sets an accepted JSON terminal type
        into the given container passsed in as the first argument
    */
    {
        std::string value = token.literal;
        if (token.terminal_type == JsonTerminalType::Null) {
            cnt::set( cnt_sptr_ref, key, converter::as_null(value) );
        } else if (token.terminal_type == JsonTerminalType::Bool) {
            cnt::set( cnt_sptr_ref, key, converter::as_bool(value) );
        } else if (token.terminal_type == JsonTerminalType::Double) {
            cnt::set( cnt_sptr_ref, key, converter::as_double(value) );
        } else {
            // otherwise, set as Text
            cnt::set(cnt_sptr_ref, key, value);
        }
    }

    void put_into(std::shared_ptr<Dict>&,
                  const std::string&, const JsonToken&) override;

    void put_into(std::shared_ptr<List>&,
                  const int&, const JsonToken&) override;

    template <typename Tc, typename Tk>
    void fill_container(std::shared_ptr<Tc>& cnt_sptr_ref, const Tk& key,
                        const std::vector<JsonToken>& token_vector)
    /*
        Inside a dictionary scope, only key-value pairs.
        This means the only possibilities are
            case 1, key : terminal
            case 2, key : {}
            case 3, key : []
            case 4, key : () not for JSON
        determine key and value
    */
    {
        /// Case 1, next token is a terminal
        if (token_vector[next_index()].type == JsonTokenType::Terminal) {
            // set terminal value
            put_into(cnt_sptr_ref, key, token_vector[next_index()]);
            // shift current index to point at next iter key token
            current_index += 2;
        /// Case 2, next token is dict opening.
        } else if (token_vector[next_index()].type == JsonTokenType::DictOpening) {
            // build a dict recursively
            std::shared_ptr<Dict> subdict_sptr;
            subdict_sptr = make_dict(next_index(), token_vector);
            cnt::set(cnt_sptr_ref, key, subdict_sptr);
        /// Case 3, next token is list opening.
        } else if (token_vector[next_index()].type == JsonTokenType::ListOpening) {
            // build a list
            std::shared_ptr<List> sublist_sptr;
            sublist_sptr = make_list(next_index(), token_vector);
            cnt::set(cnt_sptr_ref, key, sublist_sptr);
        } else { /* TODO */ }
    }

    void at_key(std::shared_ptr<Dict>&,
                const std::vector<JsonToken>&) override;

    void at_iter_key(std::shared_ptr<List>&,
                     const std::vector<JsonToken>&) override;
    
    std::shared_ptr<Dict> make_root_dict(const std::vector<JsonToken>&) override;

    std::shared_ptr<List> make_root_list(const std::vector<JsonToken>&) override;
    
    std::shared_ptr<Dict> make_dict(int, const std::vector<JsonToken>&) override;

    std::shared_ptr<List> make_list(int, const std::vector<JsonToken>&) override;

public:
     JsonLoader();

    ~JsonLoader();

    void load_from_parser(const JsonParser&, const std::shared_ptr<Dict>&);

    void load_from_file(const std::string&, const std::shared_ptr<Dict>&);
};

}
#endif
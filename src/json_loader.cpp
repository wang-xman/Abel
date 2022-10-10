#include "json_loader.hpp"

namespace abel {

JsonLoader::JsonLoader() {}

JsonLoader::~JsonLoader() {}

void JsonLoader::put_into(std::shared_ptr<Dict>& dict_sptr_ref,
                          const std::string& key, const JsonToken& token)
/*
    Settles JSON-accepted terminal in a dictionary.
    Invoked by method `fill_container`
*/
{
    set_json_terminal(dict_sptr_ref, key, token);
}

void JsonLoader::put_into(std::shared_ptr<List>& list_sptr_ref,
                          const int& iter_key, const JsonToken& token)
/*
    Settles JSON-accepted terminal in a list.
    Invoked by method `fill_container`
*/
{
    set_json_terminal(list_sptr_ref, iter_key, token);
}

void JsonLoader::at_key(std::shared_ptr<Dict>& dict_sptr_ref,
                        const std::vector<JsonToken>& token_vector)
/*
    Operations at a key token
*/
{
    std::string key = token_vector[current_index].literal;
    fill_container(dict_sptr_ref, key, token_vector);
}

void JsonLoader::at_iter_key(std::shared_ptr<List>& list_sptr_ref,
                             const std::vector<JsonToken>& token_vector)
/*
    Operations at an inter-key token
*/
{
    int iter_key = std::stoi(token_vector[current_index].literal);
    fill_container(list_sptr_ref, iter_key, token_vector);
}

std::shared_ptr<Dict> JsonLoader::make_root_dict(
        const std::vector<JsonToken>& token_vector)
{
    std::shared_ptr<Dict> root_object_dict_sptr (new Dict());
    while(current_index < (int) token_vector.size()) {
        // For this method, current index shall always point at a key token.
        if (token_vector[current_index].type == JsonTokenType::Key) {
            at_key(root_object_dict_sptr, token_vector);
            continue;
        }
    }
    return root_object_dict_sptr;
}

std::shared_ptr<List> JsonLoader::make_root_list(
        const std::vector<JsonToken>& token_vector)
/*
    For this method, current index must always point at an
    iter-key token
*/
{
    std::shared_ptr<List> root_object_list_sptr (new List());
    while(current_index < (int) token_vector.size()) {
        if (token_vector[current_index].type == JsonTokenType::IterKey) {
            at_iter_key(root_object_list_sptr, token_vector);
            continue;
        }
    }
    return root_object_list_sptr;
}

std::shared_ptr<Dict> JsonLoader::make_dict(int index_opening_token,
        const std::vector<JsonToken>& token_vector)
{
    std::shared_ptr<Dict> dict_sptr ( new Dict() );
    // Prepare current index for iteration. Iteration start from next index.
    current_index = index_opening_token + 1;
    while ( current_index < (int) token_vector.size()
            && !is_matched_closing(token_vector[current_index],
                                   token_vector[index_opening_token]) ) {
        if (token_vector[current_index].type == JsonTokenType::Key) {
            at_key(dict_sptr, token_vector);
            continue;
        }
    }
    // Since when current index is pointing at a dict closing symbole, while
    // loop terminates, must update current index for the next root-level run.
    current_index += 1;
    return dict_sptr;
}

std::shared_ptr<List> JsonLoader::make_list(int index_opening_token,
        const std::vector<JsonToken>& token_vector)
{
    std::shared_ptr<List> list_sptr ( new List() );
    current_index = index_opening_token + 1;
    while ( current_index < (int) token_vector.size()
            && !is_matched_closing(token_vector[current_index],
                                   token_vector[index_opening_token]) ) {
        if (token_vector[current_index].type == JsonTokenType::IterKey) {
            at_iter_key(list_sptr, token_vector);
            continue;
        }
    }
    current_index += 1;
    return list_sptr;
}

void JsonLoader::load_from_parser(const JsonParser& parser,
                                  const std::shared_ptr<Dict>& dict_sptr)
{
    global_dict_sptr = dict_sptr; // set dictionary pointer
    root_container_type = parser.get_root_container_type();
    if (root_container_type == JsonContainerType::Dict) {
    // root container is a dict
        std::shared_ptr<Dict> root_object_dict ( new Dict() );
        root_object_dict = make_root_dict( parser.get_token_vector() );
        cnt::set(global_dict_sptr, "ROOT_KEY_", root_object_dict);
    } else if (root_container_type == JsonContainerType::List) {
    // root container is a list
        std::shared_ptr<List> root_object_list
                = make_root_list( parser.get_token_vector() );
        cnt::set(global_dict_sptr, "ROOT_KEY_", root_object_list);
    } else {
        throw error::SyntaxError("Root object type is undetermined.");
    }
}

void JsonLoader::load_from_file(const std::string& input_file,
                                const std::shared_ptr<Dict>& dict_sptr)
{
    std::ifstream input_file_stream(input_file);
    abel::JsonParser json_parser;
    json_parser.parse(input_file_stream);
    load_from_parser(json_parser, dict_sptr);
}

}
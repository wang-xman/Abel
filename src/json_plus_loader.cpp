#include "json_plus_loader.hpp"

namespace abel {

JsonPlusLoader::JsonPlusLoader() {}

JsonPlusLoader::~JsonPlusLoader() {}

void JsonPlusLoader::put_into(std::shared_ptr<Dict>& dict_sptr_ref,
                              const std::string& key, const JsonToken& token)
{
    set_json_plus_terminal(dict_sptr_ref, key, token);
}

void JsonPlusLoader::put_into(std::shared_ptr<List>& list_sptr_ref,
                              const int& iter_key, const JsonToken& token)
{
    set_json_plus_terminal(list_sptr_ref, iter_key, token);
}

void JsonPlusLoader::load_from_parser(const JsonPlusParser& parser,
                                      const std::shared_ptr<Dict>& global_sptr)
{
    global_dict_sptr = global_sptr; // set dictionary pointer
    root_container_type = parser.get_root_container_type();
    if (root_container_type == JsonContainerType::Dict) {
    // root container is a dict
        std::shared_ptr<Dict> root_object_dict ( new Dict() );
        root_object_dict
                = make_root_dict( parser.get_token_vector() );
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

void JsonPlusLoader::load_from_file(const std::string& input_file,
                                    const std::shared_ptr<Dict>& global_sptr)
{
    std::ifstream input_file_stream(input_file);
    abel::JsonPlusParser json_plus_parser;
    json_plus_parser.parse(input_file_stream);
    load_from_parser(json_plus_parser, global_sptr);
}

}
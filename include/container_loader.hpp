#ifndef _ABEL_CONTAINER_LOADER_HPP_
#define _ABEL_CONTAINER_LOADER_HPP_

#include "container.hpp"
#include "util.hpp"

namespace abel {

template <typename T, typename ContainerT> class container_loader {
protected:
    ContainerT root_container_type;

    int current_index = 0;

    std::shared_ptr<Dict> global_dict_sptr;

    int next_index() { return current_index + 1; } // short-cut method

    bool is_matched_closing(const T& closing_token, const T& opening_token) {
        return (closing_token.literal
                    == util::get_closing_symbol_by_opening(opening_token.literal)
                && closing_token.level == opening_token.level
                && closing_token.parent_key == opening_token.parent_key);
    } 

    virtual void put_into(std::shared_ptr<Dict>&, const std::string&, const T&) = 0;
    virtual void put_into(std::shared_ptr<List>&, const int&, const T&) = 0;

    virtual void at_key(std::shared_ptr<Dict>&, const std::vector<T>&) = 0;
    virtual void at_iter_key(std::shared_ptr<List>&, const std::vector<T>&) = 0;

    // make root (container) dict or list
    virtual std::shared_ptr<Dict> make_root_dict(const std::vector<T>&) = 0;
    virtual std::shared_ptr<List> make_root_list(const std::vector<T>&) = 0;

    // make a dict or list
    virtual std::shared_ptr<Dict> make_dict(int, const std::vector<T>&) = 0;
    virtual std::shared_ptr<List> make_list(int, const std::vector<T>&) = 0;
    
public:
    container_loader() {}

    virtual ~container_loader() {}
};

}
#endif
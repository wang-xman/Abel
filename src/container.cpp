#include "container.hpp"

namespace abel {

void List::insert(const int index, const Dict& ref)
/*
    List : insert a Dict in list. Declared in header `list.hpp`
*/
{
    try {
        insert_check(index);
        internal.insert( internal.begin() + index, std::make_shared<Dict>(ref) );
    } catch (error::IndexOutOfRange& err) {
        err.make_show();
    }
}

void Tuple::insert(const int index, const Dict& ref)
/*
    Tuple : insert a Dict in tuple. Declared in header `tuple.hpp`
*/
{
    try {
        insert_check(index);
        internal.insert( internal.begin() + index, std::make_shared<Dict>(ref) );
    } catch (error::IndexOutOfRange& err) {
        err.make_show();
    }
}

}
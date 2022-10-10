#include "delimiter.hpp"

namespace abel {

bool util::is_matched(const DelimiterPair& pair)
/*
    NOTE Stored in namespace abel::util
*/
{
    return (pair.match_counter == 0
            && pair.position_closing[0] != -999
            && pair.position_closing[1] != -999);
}

DelimiterMatch::DelimiterMatch() {}

DelimiterMatch::~DelimiterMatch() {}

void DelimiterMatch::init_pair(const std::string& opening_sym,
                               const int& line, const int& column)
{
    DelimiterPair pair;
    pair.opening_symbol = opening_sym;
    pair.closing_symbol = util::get_closing_symbol_by_opening(opening_sym);
    pair.position_opening = {line, column};
    pair_register.push_back(pair);
}

/// Match opening and closing symbols.
void DelimiterMatch::match(const std::string curstr,
                           const int line, const int column)
{
    if ( util::is_opening_symbol(curstr) ) {
        // Update counters of existing opening symbol
        for (DelimiterPair& pair : pair_register) {
            // Pairs with the same opening symbol must be updated.
            // Matched pair needs NO update.
            if (!util::is_matched(pair) && pair.opening_symbol == curstr) {
                pair.match_counter += 1;
            }
        }
        // Initialise a delimiter pair object by opening symbol and store
        // it in regstser.
        init_pair(curstr, line, column);
    } else if ( util::is_closing_symbol(curstr) ) {
        for (DelimiterPair& pair : pair_register) {
            // Pairs with the same closing symbol must be updated.
            if (!util::is_matched(pair) && pair.closing_symbol == curstr) {
                pair.match_counter -= 1;
                // Match found. Store the position of closing symbol.
                if (pair.match_counter == 0) {
                    pair.position_closing = {line, column};
                    total_matched_pairs += 1;
                }
            }   
        }
    }
}

void DelimiterMatch::scan(const std::string target)
{
    for (size_t i = 0; i < target.size(); i++) {
        std::string current_char = std::string(1, target[i]);
        match(current_char, 0, (int)i);
    }
}

bool DelimiterMatch::are_all_matched()
{
    return (pair_register.size() == (size_t)total_matched_pairs);
}

int DelimiterMatch::number_of_matched_pairs()
{
    return total_matched_pairs;
}

}
#ifndef ABEL_DELIMITER_HPP
#define ABEL_DELIMITER_HPP

#include "util.hpp"

namespace abel {

/* Delimiter pair struct */

struct DelimiterPair {
    std::string opening_symbol = "";
    std::string closing_symbol = "";
    std::vector<int> position_opening = {-999, -999};
    std::vector<int> position_closing = {-999, -999};
    int match_counter = 1;
};

namespace util {

bool is_matched(const DelimiterPair&);

}

/* Delimiter match class */

class DelimiterMatch {
private:
    std::vector<DelimiterPair> pair_register = {};
    int total_matched_pairs = 0;

public:
    DelimiterMatch();
    ~DelimiterMatch();

    void init_pair(const std::string& /* opening symbol */,
                   const int& /* line */,
                   const int& /* column*/);

    virtual void match(const std::string, const int, const int);

    virtual void scan(const std::string);

    virtual bool are_all_matched();

    int number_of_matched_pairs();
};

}
#endif
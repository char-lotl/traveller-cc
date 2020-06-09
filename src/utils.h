#ifndef UTILS_H
#define UTILS_H

//#include <vector>
#include <string>
//#include "Roller.h"

namespace utils {

    std::string characteristic_abbrev(int ctype);
    bool isInt(std::string line);
    int char_modifier_from_score(int score);
    int get_int_response_in_range(std::string query_string, int min, int max);
    bool get_bool_response(std::string query_string);

    const int POW2S[] = {1, 2, 4, 8, 16, 32};

}

#endif

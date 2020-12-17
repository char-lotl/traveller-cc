#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace utils {
	extern const std::string characteristic_abbrev[6];
    //std::string characteristic_abbrev(const int& ctype);
    bool isInt(const std::string& line);
    int char_modifier_from_score(const int& score);
    int get_int_response_in_range(const std::string& query_string,
                                  const int& min,
                                  const int& max);
    char get_char_response_in_range(const std::string& query_string,
                                    const char& min,
                                    const char& max);
	int get_char_from_choices(const std::string& query_string,
							  const std::string& allowed_chars);
    bool get_bool_response(const std::string& query_string);

}

#endif

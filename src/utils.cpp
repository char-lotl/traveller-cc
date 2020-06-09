#include <iostream>
#include <string>
#include "utils.h"

std::string utils::characteristic_abbrev(int ctype) {
    switch (ctype) {
        case 0:
            return "STR";
        case 1:
            return "DEX";
        case 2:
            return "END";
        case 3:
            return "INT";
        case 4:
            return "EDU";
        case 5:
            return "SOC";
        default:
            return "???";
    }
}

bool utils::isInt(std::string line) {
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

int utils::char_modifier_from_score(int score) {
    if (score == 0) return 0;
    return (score / 3) - 2;
}

int utils::get_int_response_in_range(std::string query_string,
                                     int min,
                                     int max) {
    std::string response;
    int response_num;
    while (true) {
        std::cout << query_string;
        getline(std::cin, response);
        
        // check whether the response we got was an integer
        bool wasResponseInt = utils::isInt(response);
        if (!wasResponseInt) {
            std::cout << "Sorry, that wasn't an integer." << std::endl;
            continue;
        }
        
        response_num = stoi(response);
        if ((response_num < min) || (response_num > max)) {
            std::cout << "Sorry, that response was out of range." << std::endl;
            continue;
        }
        break;
    }
    return response_num;
}

bool utils::get_bool_response(std::string query_string) {
    std::string response;
    std::cout << query_string;
    getline(std::cin, response);
    return (std::tolower(response[0]) != 'n');
}

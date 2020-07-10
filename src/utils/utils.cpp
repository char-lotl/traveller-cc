#include <iostream>
#include <string>
#include "utils.h"
#include "utils/printing/printout.h"

using namespace utils::printing;

std::string utils::characteristic_abbrev(const int& ctype) {
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

bool utils::isInt(const std::string& line) {
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

int utils::char_modifier_from_score(const int& score) {
    if (score == 0) return 0;
    return (score / 3) - 2;
}

int utils::get_int_response_in_range(const std::string& query_string,
                                     const int& min,
                                     const int& max) {
    std::string response;
    int response_num;
    while (true) {
        printout() << query_string;
        getline(std::cin, response);
        
        // check whether the response we got was an integer
        bool wasResponseInt = utils::isInt(response);
        if (!wasResponseInt) {
            printout() << "Sorry, that wasn't an integer.\n";
            continue;
        }
        
        response_num = stoi(response);
        if ((response_num < min) || (response_num > max)) {
            printout() << "Sorry, that response was out of range.\n";
            continue;
        }
        break;
    }
    return response_num;
}

bool utils::get_bool_response(const std::string& query_string) {
    std::string response;
    printout() << query_string;
    getline(std::cin, response);
    return (std::tolower(response[0]) != 'n');
}

char utils::get_char_response_in_range(const std::string& query_string,
                                const char& min,
                                const char& max) {
    std::string response;
    char response_char;
    while (true) {
        printout() << query_string;
        getline(std::cin, response);
        response_char = response[0];
        if ((response_char < min) || (response_char > max)) {
            printout() << "Sorry, that response was out of range.\n";
            continue;
        }
        break;
    }
    return response_char;
}

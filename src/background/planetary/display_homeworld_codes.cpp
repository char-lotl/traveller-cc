#include <iterator>
#include <vector>
#include <string>
#include "Codes.h"
#include "display_homeworld_codes.h"
#include "utils/printing/printout.h"

using namespace utils::printing;

void display_homeworld_codes(const Codes& homeworld_trade_codes) {
    const std::vector<trade_code> tcv = homeworld_trade_codes.get_codes_as_vector();
    if (tcv.empty()) {
        printout() << "No trade codes apply to your homeworld.\n";
    } else {
        printout() << "Your homeworld has the following trade codes:\n";
        bool first = true;
        for (const trade_code& i : tcv) {
            std::string code_string = Codes::TC_STRINGS[i];
            if (first) first = false;
            else printout() << ", ";
            printout() << code_string;
        }
        printout() << ".\n";
    }
}


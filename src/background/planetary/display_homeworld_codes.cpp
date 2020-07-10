#include <iterator>
#include <list>
#include <string>
#include "Codes.h"
#include "display_homeworld_codes.h"
#include "utils/printing/printout.h"

using namespace utils::printing;

void display_homeworld_codes(const Codes& homeworld_trade_codes) {
    const std::list<trade_code> tcl = homeworld_trade_codes.get_codes_as_list();
    if (tcl.empty()) {
        printout() << "No trade codes apply to your homeworld.\n";
    } else {
        printout() << "Your homeworld has the following trade codes:\n";
        bool first = true;
        for (const trade_code& i : tcl) {
            std::string code_string = Codes::TC_STRINGS[i];
            if (first) first = false;
            else printout() << ", ";
            printout() << code_string;
        }
        printout() << ".\n";
    }
}


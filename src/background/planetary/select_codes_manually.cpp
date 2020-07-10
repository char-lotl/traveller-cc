#include <list>
#include <algorithm>
#include "Codes.h"
#include "config/Rules.h"
#include "utils/utils.h"

#include "utils/printing/printout.h"
#include "select_codes_manually.h"

constexpr long ALL_CODES = (1 << Codes::TOTAL_TRADE_CODES) - 1;

constexpr Codes CONFLICTS[Codes::TOTAL_TRADE_CODES] = {
    [AGRICULTURAL]      = Codes(Codes::FLAGS[GARDEN] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[RICH]),
    [ASTEROID]          = Codes(Codes::FLAGS[BARREN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_AGRICULTURAL] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[VACUUM]),
    [BARREN]            = Codes(Codes::FLAGS[ASTEROID] |
                                Codes::FLAGS[DESERT] |
                                Codes::FLAGS[FLUID_OCEANS] |
                                Codes::FLAGS[GARDEN] |
                                Codes::FLAGS[ICE_CAPPED] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[POOR] |
                                Codes::FLAGS[VACUUM] |
                                Codes::FLAGS[WATER_WORLD]),
    [DESERT]            = Codes(Codes::FLAGS[BARREN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_AGRICULTURAL] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[POOR]),
    [FLUID_OCEANS]      = Codes(Codes::FLAGS[BARREN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_INDUSTRIAL]),
    [GARDEN]            = Codes(Codes::FLAGS[AGRICULTURAL] |
                                Codes::FLAGS[BARREN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[RICH]),
    [HIGH_POPULATION]   = Codes(Codes::FLAGS[ASTEROID] |
                                Codes::FLAGS[DESERT] |
                                Codes::FLAGS[FLUID_OCEANS] |
                                Codes::FLAGS[GARDEN] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[ICE_CAPPED] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_AGRICULTURAL] |
                                Codes::FLAGS[POOR] |
                                Codes::FLAGS[VACUUM] |
                                Codes::FLAGS[WATER_WORLD]),
    [HIGH_TECHNOLOGY]   = Codes(ALL_CODES &
                                ~(Codes::FLAGS[BARREN]) &
                                ~(Codes::FLAGS[HIGH_TECHNOLOGY]) &
                                ~(Codes::FLAGS[LOW_TECHNOLOGY])),
    [ICE_CAPPED]        = Codes(Codes::FLAGS[BARREN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_AGRICULTURAL] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[VACUUM] |
                                Codes::FLAGS[WATER_WORLD]),
    [INDUSTRIAL]        = Codes(Codes::FLAGS[ASTEROID] |
                                Codes::FLAGS[DESERT] |
                                Codes::FLAGS[GARDEN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[ICE_CAPPED] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_AGRICULTURAL] |
                                Codes::FLAGS[POOR] |
                                Codes::FLAGS[VACUUM] |
                                Codes::FLAGS[WATER_WORLD]),
    [LOW_POPULATION]    = Codes(Codes::FLAGS[ASTEROID] |
                                Codes::FLAGS[DESERT] |
                                Codes::FLAGS[FLUID_OCEANS] |
                                Codes::FLAGS[GARDEN] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[ICE_CAPPED] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[POOR] |
                                Codes::FLAGS[VACUUM] |
                                Codes::FLAGS[WATER_WORLD]),
    [LOW_TECHNOLOGY]    = Codes(ALL_CODES &
                                ~(Codes::FLAGS[HIGH_TECHNOLOGY]) &
                                ~(Codes::FLAGS[LOW_TECHNOLOGY])),
    [NON_AGRICULTURAL]  = Codes(Codes::FLAGS[ASTEROID] |
                                Codes::FLAGS[DESERT] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[ICE_CAPPED] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[POOR] |
                                Codes::FLAGS[VACUUM]),
    [NON_INDUSTRIAL]    = Codes(ALL_CODES &
                                ~(Codes::FLAGS[BARREN]) &
                                ~(Codes::FLAGS[HIGH_POPULATION]) &
                                ~(Codes::FLAGS[INDUSTRIAL]) &
                                ~(Codes::FLAGS[LOW_POPULATION]) &
                                ~(Codes::FLAGS[NON_INDUSTRIAL])),
    [POOR]              = Codes(Codes::FLAGS[BARREN] |
                                Codes::FLAGS[DESERT] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_AGRICULTURAL] |
                                Codes::FLAGS[NON_INDUSTRIAL]),
    [RICH]              = Codes(Codes::FLAGS[AGRICULTURAL] |
                                Codes::FLAGS[GARDEN] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[WATER_WORLD]),
    [VACUUM]            = Codes(ALL_CODES &
                                ~(Codes::FLAGS[AGRICULTURAL]) &
                                ~(Codes::FLAGS[DESERT]) &
                                ~(Codes::FLAGS[FLUID_OCEANS]) &
                                ~(Codes::FLAGS[GARDEN]) &
                                ~(Codes::FLAGS[POOR]) &
                                ~(Codes::FLAGS[RICH]) &
                                ~(Codes::FLAGS[VACUUM]) &
                                ~(Codes::FLAGS[WATER_WORLD])),
    [WATER_WORLD]       = Codes(Codes::FLAGS[BARREN] |
                                Codes::FLAGS[HIGH_POPULATION] |
                                Codes::FLAGS[HIGH_TECHNOLOGY] |
                                Codes::FLAGS[ICE_CAPPED] |
                                Codes::FLAGS[INDUSTRIAL] |
                                Codes::FLAGS[LOW_POPULATION] |
                                Codes::FLAGS[LOW_TECHNOLOGY] |
                                Codes::FLAGS[NON_INDUSTRIAL] |
                                Codes::FLAGS[RICH])
};

constexpr Codes SPARSE_CONFLICTS[Codes::TOTAL_TRADE_CODES] = {
    [AGRICULTURAL]      = Codes(ALL_CODES &
                                ~(Codes::FLAGS[AGRICULTURAL]) &
                                ~(Codes::FLAGS[BARREN]) &
                                ~(Codes::FLAGS[NON_AGRICULTURAL])),
    [ASTEROID]          = Codes(ALL_CODES &
                                ~(Codes::FLAGS[ASTEROID]) &
                                ~(Codes::FLAGS[FLUID_OCEANS]) &
                                ~(Codes::FLAGS[WATER_WORLD])),
    [BARREN]            = Codes(ALL_CODES &
                                ~(Codes::FLAGS[AGRICULTURAL]) &
                                ~(Codes::FLAGS[BARREN]) &
                                ~(Codes::FLAGS[HIGH_POPULATION]) &
                                ~(Codes::FLAGS[INDUSTRIAL])),
    [DESERT]            = Codes(ALL_CODES &
                                ~(Codes::FLAGS[DESERT]) &
                                ~(Codes::FLAGS[INDUSTRIAL])),
    [FLUID_OCEANS]      = Codes(ALL_CODES &
                                ~(Codes::FLAGS[ASTEROID]) &
                                ~(Codes::FLAGS[FLUID_OCEANS]) &
                                ~(Codes::FLAGS[VACUUM]) &
                                ~(Codes::FLAGS[WATER_WORLD])),
    [GARDEN]            = Codes(ALL_CODES &
                                ~(Codes::FLAGS[GARDEN]) &
                                ~(Codes::FLAGS[POOR])),
    [HIGH_POPULATION]   = Codes(ALL_CODES &
                                ~(Codes::FLAGS[BARREN]) &
                                ~(Codes::FLAGS[HIGH_POPULATION]) &
                                ~(Codes::FLAGS[LOW_POPULATION])),
    [HIGH_TECHNOLOGY]   = Codes(ALL_CODES &
                                ~(Codes::FLAGS[HIGH_TECHNOLOGY]) &
                                ~(Codes::FLAGS[LOW_TECHNOLOGY])),
    [ICE_CAPPED]        = Codes(ALL_CODES &
                                ~(Codes::FLAGS[ICE_CAPPED])),
    [INDUSTRIAL]        = Codes(ALL_CODES &
                                ~(Codes::FLAGS[BARREN]) &
                                ~(Codes::FLAGS[INDUSTRIAL]) &
                                ~(Codes::FLAGS[NON_INDUSTRIAL])),
    [LOW_POPULATION]    = Codes(ALL_CODES &
                                ~(Codes::FLAGS[HIGH_POPULATION]) &
                                ~(Codes::FLAGS[LOW_POPULATION])),
    [LOW_TECHNOLOGY]    = Codes(ALL_CODES &
                                ~(Codes::FLAGS[HIGH_TECHNOLOGY]) &
                                ~(Codes::FLAGS[LOW_TECHNOLOGY])),
    [NON_AGRICULTURAL]  = Codes(ALL_CODES &
                                ~(Codes::FLAGS[AGRICULTURAL]) &
                                ~(Codes::FLAGS[NON_AGRICULTURAL]) &
                                ~(Codes::FLAGS[RICH])),
    [NON_INDUSTRIAL]    = Codes(ALL_CODES &
                                ~(Codes::FLAGS[INDUSTRIAL]) &
                                ~(Codes::FLAGS[NON_INDUSTRIAL])),
    [POOR]              = Codes(ALL_CODES &
                                ~(Codes::FLAGS[GARDEN]) &
                                ~(Codes::FLAGS[POOR]) &
                                ~(Codes::FLAGS[RICH])),
    [RICH]              = Codes(ALL_CODES &
                                ~(Codes::FLAGS[NON_AGRICULTURAL]) &
                                ~(Codes::FLAGS[POOR]) &
                                ~(Codes::FLAGS[RICH])),
    [VACUUM]            = Codes(ALL_CODES &
                                ~(Codes::FLAGS[FLUID_OCEANS]) &
                                ~(Codes::FLAGS[VACUUM]) &
                                ~(Codes::FLAGS[WATER_WORLD])),
    [WATER_WORLD]       = Codes(ALL_CODES &
                                ~(Codes::FLAGS[ASTEROID]) &
                                ~(Codes::FLAGS[DESERT]) &
                                ~(Codes::FLAGS[FLUID_OCEANS]) &
                                ~(Codes::FLAGS[VACUUM]) &
                                ~(Codes::FLAGS[WATER_WORLD]))
};


using namespace utils::printing;

void display_trade_codes_vertically(const std::list<trade_code>& tcl);
void display_trade_codes_inline(const std::list<trade_code>& tcl);

Codes select_codes_manually(const Rules& ru) {
    //return Codes(false);
    
    bool use_sparse_conflicts = ru.get_toggle_rule(rule_type::SPARSE_CODE_CONFLICTS);
    
    Codes available(true);
    std::list<trade_code> available_tcl;
    std::list<trade_code> selection_tcl;
    Codes selection(false);
    int response;
    std::string prompt;
    
    while (true) {
        
        std::list<trade_code> available_tcl = available.get_codes_as_list();
        std::list<trade_code> selection_tcl = selection.get_codes_as_list();
        
        if (selection.empty())
            prompt = "No codes selected. Enter 1 to add a new code, or 0 to confirm"
            " and exit: ";
        else if (available.empty()) {
            printout() << "Homeworld is now ";
            display_trade_codes_inline(selection_tcl);
            printout() << "No more trade codes consistent with current selection.\n";
            prompt = "Enter 2 to start over, or 0 to confirm and exit: ";
        } else {
            printout() << "Current selection: ";
            display_trade_codes_inline(selection_tcl);
            prompt = "Enter 1 to add a new code, 2 to start over, or 0 to confirm"
            " and exit: ";
        }
        
        response =
        utils::get_int_response_in_range(prompt, 0, 2);
        
        switch (response) {
            case 0:
                printout() << "Homeworld trade codes confirmed. Selection complete.\n";
                return selection;
            case 1: {
                printout() << available_tcl.size() <<
                " codes available.\n";
                display_trade_codes_vertically(available_tcl);
                char response_char =
                utils::get_char_response_in_range("Enter the letter corresponding to one"
                                                  " of the above\ncodes to add it to"
                                                  " your homeworld: ",
                                                  'a', 'r');
                response = response_char - 'a';
                trade_code response_tc = Codes::TCS[response];
                bool resp_is_available = (std::find(available_tcl.begin(),
                                                    available_tcl.end(),
                                                    response_tc) != available_tcl.end());
                if (resp_is_available) {
                    selection = selection.add_code(response_tc);
                    if (use_sparse_conflicts)
                        available = available.intersect(SPARSE_CONFLICTS[response]);
                    else available = available.intersect(CONFLICTS[response]);
                    printout() << "Added code " <<
                    Codes::TC_STRINGS[response_tc] << ".\n";
                } else {
                    printout() << "Code conflicts with existing codes, or has already been added.\n";
                    continue;
                }
                break;
            }
            case 2:
                available = Codes(true);
                selection = Codes(false);
        }
        
    }
    
}

void display_trade_codes_vertically(const std::list<trade_code>& tcl) {
    int i = 0;
    auto j = tcl.begin();
    char k;
    while (j != tcl.end()) {
        k = 'a' + (*j);
        printout() << k << ". " << Codes::TC_STRINGS[*j] << "\n";
        ++i;
        std::advance(j, 1);
    }
}

void display_trade_codes_inline(const std::list<trade_code>& tcl) {
    bool first = true;
    for (const trade_code& i : tcl) {
        std::string code_string = Codes::TC_STRINGS[i];
        if (first) first = false;
        else printout() << ", ";
        printout() << code_string;
    }
    printout() << ".\n";
}

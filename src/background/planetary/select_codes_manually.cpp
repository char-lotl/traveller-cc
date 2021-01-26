#include <vector>
#include <algorithm>
#include "Codes.h"
#include "config/get_rules.h"
#include "utils/utils.h"

#include "utils/printing/printout.h"
#include "utils/printing/Formatter.h"
#include "select_codes_manually.h"

using namespace config;

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

//void display_trade_codes_vertically(const std::vector<trade_code>& tcv);
void display_trade_codes_inline(const std::vector<trade_code>& tcv);
void display_trade_codes_tabular(const std::vector<trade_code>& tcv);
std::vector<bool> get_availability_bools(const std::vector<trade_code>& tcv);

Codes select_codes_manually() {
    //return Codes(false);
    
    bool use_sparse_conflicts = get_toggle_rule(rule_type::SPARSE_CODE_CONFLICTS);
    
    Codes available(true);
	Codes selection(false);
    std::vector<trade_code> available_tcv;
    std::vector<trade_code> selection_tcv;
    int response;
    std::string prompt;
    
    while (true) {
        
        std::vector<trade_code> available_tcv = available.get_codes_as_vector();
        std::vector<trade_code> selection_tcv = selection.get_codes_as_vector();
        
        if (selection.empty())
            prompt = "No codes selected. Add a [n]ew code, or [c]onfirm"
            " and exit: ";
        else if (available.empty()) {
            printout() << "Homeworld is now ";
            display_trade_codes_inline(selection_tcv);
            printout() << "No more trade codes consistent with current selection.\n";
            prompt = "[S]tart over, or [c]onfirm and exit: ";
        } else {
            printout() << "Current selection: ";
            display_trade_codes_inline(selection_tcv);
            prompt = "Add a [n]ew code, [s]tart over, or [c]onfirm"
            " and exit: ";
        }
        
        response = utils::get_char_from_choices(prompt, "cns");
        
        switch (response) {
            case 0:
                printout() << "Homeworld trade codes confirmed. Selection complete.\n";
                return selection;
            case 1: {
                printout() << available_tcv.size() <<
                " codes available.\n";
                display_trade_codes_tabular(available_tcv);
                char response_char =
                utils::get_char_response_in_range("Enter the letter corresponding to one"
                                                  " of the above codes to add it to"
                                                  " your\nhomeworld: ",
                                                  'a', 'r');
                response = response_char - 'a';
                trade_code response_tc = Codes::TCS[response];
                bool resp_is_available = (std::find(available_tcv.begin(),
                                                    available_tcv.end(),
                                                    response_tc) != available_tcv.end());
                if (resp_is_available) {
                    selection = selection.add_code(response_tc);
                    if (use_sparse_conflicts)
                        available = available.intersect(SPARSE_CONFLICTS[response]);
					else {
						available = available.intersect(CONFLICTS[response]);
						if (response_tc == ASTEROID) selection = selection.add_code(VACUUM);
						if (response_tc == INDUSTRIAL) selection = selection.add_code(HIGH_POPULATION);
						// very special edge-cases where one code implies another
						// but with sparse conflicts we can imagine a non-vacuum asteroid :)
						// (or industrial planets with low populations, for that matter)
					}
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

void display_trade_codes_inline(const std::vector<trade_code>& tcv) {
    std::vector<std::string> code_strings;
    for (const trade_code& i : tcv) {
        code_strings.push_back(Codes::TC_STRINGS[i]);
    }
	printout() << CommaList(code_strings);
}

void display_trade_codes_tabular(const std::vector<trade_code>& tcv) {
	std::vector<std::string> strv;
	std::vector<bool> availability_bool_vec = get_availability_bools(tcv);
	static const std::vector<std::string> all_code_strings_vector(std::begin(Codes::TC_STRINGS),
																  std::end(Codes::TC_STRINGS));
	for (trade_code const& t : tcv) {
		strv.push_back(std::string(1, 'a' + t) + ". " + Codes::TC_STRINGS[t]);
	}
	printout() << TabularList(strv);
}

std::vector<bool> get_availability_bools(const std::vector<trade_code>& tcv) {
	std::vector<bool> abv(Codes::TOTAL_TRADE_CODES, false);
	for (trade_code const& tc : tcv) abv[tc] = true;
	return abv;
}

#include <list>
#include <array>
#include "config/get_rules.h"
#include "planetary/Codes.h"
class Repertoire;
#include "planetary/GenerationVariant.h"

#include "skills/skill_type.h"
#include "utils/utils.h"
#include "utils/constants.h"

#include "pick_background_skills.h"
#include "planetary/generate_trade_codes.h"
#include "planetary/select_codes_manually.h"
#include "planetary/display_homeworld_codes.h"
#include "get_skills_from_codes.h"
#include "query_background_skills.h"

using namespace config;

int get_num_background_skills(const std::array<int,6>& characteristic_scores);

Codes get_world_codes();
GenerationVariant gen_variant_from_rules();

void pick_background_skills(const std::array<int,6>& characteristic_scores,
                            Repertoire& rep) {
    
    std::list<skill_type> homeworld_skills;
    
    Codes homeworld_trade_codes = get_world_codes();
    
    //display_homeworld_codes(homeworld_trade_codes);
    
    get_skills_from_codes(homeworld_skills, homeworld_trade_codes);
    
    int num_bg_skills = get_num_background_skills(characteristic_scores);
    query_background_skills(homeworld_skills, num_bg_skills, rep);
    
}

int get_num_background_skills(const std::array<int,6>& characteristic_scores) {
    int edu_score = characteristic_scores[constants::EDU];
    return utils::char_modifier_from_score(edu_score) + 3;
}

Codes get_world_codes() {
    int code_method = 0;
    
	if (get_toggle_rule(rule_type::TRADE_CODE_METHOD_QUERY)) {
        code_method =
        utils::get_char_from_choices("How would you like to determine"
                                         " your homeworld's trade codes:\n"
                                         "[r]olling / [m]anual entry? ",
                                         "rm");
	}
    else code_method = get_int_rule(rule_type::DEFAULT_CODE_METHOD);
    
	bool world_reroll = get_toggle_rule(rule_type::ALLOW_HOMEWORLD_REROLL);
	bool dissatisfied = true;
	
    switch (code_method) {
        case 0: {
            GenerationVariant gv = gen_variant_from_rules();
			while (dissatisfied) {
				Codes c = generate_trade_codes(gv);
				display_homeworld_codes(c);
				if (world_reroll) {
					dissatisfied = !utils::get_bool_response("Keep homeworld? (y/n) ");
					if (dissatisfied) continue;
				}
				return c;
			}
        }
        case 1:
            return select_codes_manually();
        default:
            return Codes(false);
    }
}

GenerationVariant gen_variant_from_rules() {
    int preferred_variant;
    if (get_toggle_rule(rule_type::GENERATION_VARIANT_QUERY))
        preferred_variant =
        utils::get_char_from_choices("Which homeworld generation rules"
                                         " would you like to use?\n"
                                         "[s]tandard / space [o]pera"
                                         " / [h]ard science) ",
                                         "soh");
    else preferred_variant = get_int_rule(rule_type::DEFAULT_GENERATION_VARIANT);
    
    switch (preferred_variant) {
        case 0:
            return GenerationVariant::STANDARD;
        case 1:
            return GenerationVariant::SPACE_OPERA;
        case 2:
            return GenerationVariant::REALISM;
        default:
            return GenerationVariant::STANDARD;
    }
}

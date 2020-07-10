#include <list>
#include <array>
#include "config/Rules.h"
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

int get_num_background_skills(const std::array<int,6>& characteristic_scores);

Codes get_world_codes(const Rules& ru);
GenerationVariant gen_variant_from_rules(const Rules& ru);

void pick_background_skills(const std::array<int,6>& characteristic_scores,
                            Repertoire& rep,
                            const Rules &ru) {
    
    std::list<skill_type> homeworld_skills;
    
    Codes homeworld_trade_codes = get_world_codes(ru);
    
    display_homeworld_codes(homeworld_trade_codes);
    
    get_skills_from_codes(homeworld_skills, homeworld_trade_codes);
    
    int num_bg_skills = get_num_background_skills(characteristic_scores);
    query_background_skills(homeworld_skills, num_bg_skills, rep);
    
}

int get_num_background_skills(const std::array<int,6>& characteristic_scores) {
    int edu_score = characteristic_scores[constants::EDU];
    return utils::char_modifier_from_score(edu_score) + 3;
}

Codes get_world_codes(const Rules& ru) {
    int code_method;
    
    if (ru.get_toggle_rule(rule_type::TRADE_CODE_METHOD_QUERY))
        code_method =
        utils::get_int_response_in_range("How would you like to determine"
                                         " your homeworld's trade codes?\n"
                                         "(0 for rolling, 1 for manual entry) ",
                                         0, 2);
    else code_method = ru.get_int_rule(rule_type::DEFAULT_CODE_METHOD);
    
    switch (code_method) {
        case 0: {
            GenerationVariant gv = gen_variant_from_rules(ru);
            return generate_trade_codes(gv);
        }
        case 1:
            return select_codes_manually(ru);
        default:
            return Codes(false);
    }
}

GenerationVariant gen_variant_from_rules(const Rules& ru) {
    int preferred_variant;
    if (ru.get_toggle_rule(rule_type::GENERATION_VARIANT_QUERY))
        preferred_variant =
        utils::get_int_response_in_range("Which homeworld generation rules"
                                         " would you like to use?\n"
                                         "(0 for standard, 1 for space opera"
                                         ", 2 for hard science) ",
                                         0, 2);
    else preferred_variant = ru.get_int_rule(rule_type::DEFAULT_GENERATION_VARIANT);
    
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

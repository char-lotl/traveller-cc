#include <vector>
#include "skills/skill_type.h"
#include "planetary/Codes.h"

#include "get_skills_from_codes.h"

const int NUM_HW_SKILLS = 9;

namespace hw_sk {
    enum homeworld_skill {
        ANIMALS,
        CAROUSE,
        COMPUTERS,
        SEAFARER,
        STREETWISE,
        SURVIVAL,
        TRADE,
        VACC_SUIT,
        ZERO_G
    };
};

const Codes SKILL_CODES[NUM_HW_SKILLS] = {
    [hw_sk::ANIMALS]    = Codes::FLAGS[AGRICULTURAL] | Codes::FLAGS[GARDEN] |
                            Codes::FLAGS[POOR],
    [hw_sk::CAROUSE]    = Codes::FLAGS[RICH],
    [hw_sk::COMPUTERS]  = Codes::FLAGS[HIGH_TECHNOLOGY],
    [hw_sk::SEAFARER]   = Codes::FLAGS[FLUID_OCEANS] | Codes::FLAGS[WATER_WORLD],
    [hw_sk::STREETWISE] = Codes::FLAGS[HIGH_POPULATION],
    [hw_sk::SURVIVAL]   = Codes::FLAGS[DESERT] | Codes::FLAGS[LOW_TECHNOLOGY],
    [hw_sk::TRADE]      = Codes::FLAGS[INDUSTRIAL],
    [hw_sk::VACC_SUIT]  = Codes::FLAGS[ICE_CAPPED] | Codes::FLAGS[VACUUM],
    [hw_sk::ZERO_G]     = Codes::FLAGS[ASTEROID]
};

const skill_type SKILL_TRANSLATE[NUM_HW_SKILLS] = {
    [hw_sk::ANIMALS]    = ANIMALS,
    [hw_sk::CAROUSE]    = CAROUSE,
    [hw_sk::COMPUTERS]  = COMPUTERS,
    [hw_sk::SEAFARER]   = SEAFARER,
    [hw_sk::STREETWISE] = STREETWISE,
    [hw_sk::SURVIVAL]   = SURVIVAL,
    [hw_sk::TRADE]      = TRADE,
    [hw_sk::VACC_SUIT]  = VACC_SUIT,
    [hw_sk::ZERO_G]     = ZERO_G
};

void get_skills_from_codes(std::vector<skill_type>& homeworld_skills,
                           const Codes& homeworld_trade_codes) {
    for (int i = 0; i < NUM_HW_SKILLS; i++) {
        if (homeworld_trade_codes.overlaps(SKILL_CODES[i]))
            homeworld_skills.push_back(SKILL_TRANSLATE[i]);
    }
}

#ifndef SKILL_TYPE_H
#define SKILL_TYPE_H

#include <string>

enum skill_type {
    ADMIN,
    ADVOCATE,
    ANIMALS,
    ATHLETICS,
    ART,
    ASTROGATION,
    BATTLE_DRESS,
    BROKER,
    CAROUSE,
    COMMS,
    COMPUTERS,
    DECEPTION,
    DIPLOMAT,
    DRIVE,
    ENGINEER,
    EXPLOSIVES,
    FLYER,
    GAMBLER,
    GUNNER,
    GUN_COMBAT,
    HEAVY_WEAPONS,
    INVESTIGATE,
    JACK_OF_ALL_TRADES,
    LANGUAGE,
    LEADERSHIP,
    MECHANIC,
    MEDIC,
    MELEE,
    NAVIGATION,
    PERSUADE,
    PILOT,
    RECON,
    REMOTE_OPERATIONS,
    SCIENCE_PHYSICAL,
    SCIENCE_LIFE,
    SCIENCE_SOCIAL,
    SCIENCE_SPACE,
    SEAFARER,
    SENSORS,
    STEALTH,
    STEWARD,
    STREETWISE,
    SURVIVAL,
    TACTICS,
    TRADE,
    VACC_SUIT,
    ZERO_G
};

namespace skills {
    const int NUM_UNSPECIALIZED_SKILLS = 28;
    const int NUM_SPECIALIZED_SKILLS = 19;
    const int NUM_SKILLS_OVERALL = 47;
    // must keep these consistent with the above!
    // no real easy way around this.

    extern const bool SKILL_HAS_SPECIALTIES[NUM_SKILLS_OVERALL];
    extern const std::string SK_STRINGS[NUM_SKILLS_OVERALL];
}

#endif

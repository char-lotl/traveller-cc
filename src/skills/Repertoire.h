#ifndef REPERTOIRE_H
#define REPERTOIRE_H

#include <optional>
#include <string>
#include <array>
#include <map>
#include "skill_type.h"

struct Skill;

namespace repertoire_storage {
    enum no_specialty_skills {
        ADMIN,
        ADVOCATE,
        ASTROGATION,
        BATTLE_DRESS,
        BROKER,
        CAROUSE,
        COMMS,
        COMPUTERS,
        DECEPTION,
        DIPLOMAT,
        GAMBLER,
        INVESTIGATE,
        JACK_OF_ALL_TRADES,
        LEADERSHIP,
        MECHANIC,
        MEDIC,
        NAVIGATION,
        PERSUADE,
        RECON,
        REMOTE_OPERATIONS,
        SENSORS,
        STEALTH,
        STEWARD,
        STREETWISE,
        SURVIVAL,
        VACC_SUIT,
        ZERO_G
    };

    enum specialty_skills {
        ANIMALS,
        ATHLETICS,
        ART,
        DRIVE,
        ENGINEER,
        FLYER,
        GUNNER,
        GUN_COMBAT,
        HEAVY_WEAPONS,
        LANGUAGE,
        MELEE,
        PILOT,
        SCIENCE_PHYSICAL,
        SCIENCE_LIFE,
        SCIENCE_SOCIAL,
        SCIENCE_SPACE,
        SEAFARER,
        TACTICS,
        TRADE
    };
};

const int SKILL_INDEX[skills::NUM_SKILLS_OVERALL] = {
    [ADMIN] = repertoire_storage::ADMIN,
    [ADVOCATE] = repertoire_storage::ADVOCATE,
    [ANIMALS] = repertoire_storage::ANIMALS,
    [ATHLETICS] = repertoire_storage::ATHLETICS,
    [ART] = repertoire_storage::ART,
    [ASTROGATION] = repertoire_storage::ASTROGATION,
    [BATTLE_DRESS] = repertoire_storage::BATTLE_DRESS,
    [BROKER] = repertoire_storage::BROKER,
    [CAROUSE] = repertoire_storage::CAROUSE,
    [COMMS] = repertoire_storage::COMMS,
    [COMPUTERS] = repertoire_storage::COMPUTERS,
    [DECEPTION] = repertoire_storage::DECEPTION,
    [DIPLOMAT] = repertoire_storage::DIPLOMAT,
    [DRIVE] = repertoire_storage::DRIVE,
    [ENGINEER] = repertoire_storage::ENGINEER,
    [FLYER] = repertoire_storage::FLYER,
    [GAMBLER] = repertoire_storage::GAMBLER,
    [GUNNER] = repertoire_storage::GUNNER,
    [GUN_COMBAT] = repertoire_storage::GUN_COMBAT,
    [HEAVY_WEAPONS] = repertoire_storage::HEAVY_WEAPONS,
    [INVESTIGATE] = repertoire_storage::INVESTIGATE,
    [JACK_OF_ALL_TRADES] = repertoire_storage::JACK_OF_ALL_TRADES,
    [LANGUAGE] = repertoire_storage::LANGUAGE,
    [LEADERSHIP] = repertoire_storage::LEADERSHIP,
    [MECHANIC] = repertoire_storage::MECHANIC,
    [MEDIC] = repertoire_storage::MEDIC,
    [MELEE] = repertoire_storage::MELEE,
    [NAVIGATION] = repertoire_storage::NAVIGATION,
    [PERSUADE] = repertoire_storage::PERSUADE,
    [PILOT] = repertoire_storage::PILOT,
    [RECON] = repertoire_storage::RECON,
    [REMOTE_OPERATIONS] = repertoire_storage::REMOTE_OPERATIONS,
    [SCIENCE_PHYSICAL] = repertoire_storage::SCIENCE_PHYSICAL,
    [SCIENCE_LIFE] = repertoire_storage::SCIENCE_LIFE,
    [SCIENCE_SOCIAL] = repertoire_storage::SCIENCE_SOCIAL,
    [SCIENCE_SPACE] = repertoire_storage::SCIENCE_SPACE,
    [SEAFARER] = repertoire_storage::SEAFARER,
    [SENSORS] = repertoire_storage::SENSORS,
    [STEALTH] = repertoire_storage::STEALTH,
    [STEWARD] = repertoire_storage::STEWARD,
    [STREETWISE] = repertoire_storage::STREETWISE,
    [SURVIVAL] = repertoire_storage::SURVIVAL,
    [TACTICS] = repertoire_storage::TACTICS,
    [TRADE] = repertoire_storage::TRADE,
    [VACC_SUIT] = repertoire_storage::VACC_SUIT,
    [ZERO_G] = repertoire_storage::ZERO_G
};

class Repertoire {
private:
    std::array<int,skills::NUM_UNSPECIALIZED_SKILLS> no_specialty_ranks;
    std::array<std::map<std::string,int>,skills::NUM_SPECIALIZED_SKILLS> specialty_ranks;
    std::array<bool,skills::NUM_SKILLS_OVERALL> has_skill;
    // 46 total skills, 27 unspecialized, 19 specialized
    int& get_rank_reference(const Skill& s);
public:
    Repertoire();
    std::optional<int> get_rank(const Skill& s) const;
    bool is_trained(const skill_type& s) const;
    void improve_skill_to_rank(const Skill& s, int r);
    void learn_skill(const skill_type& s);
    void increment_skill_rank(const Skill& s);
};

#endif

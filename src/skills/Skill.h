#ifndef SKILL_H
#define SKILL_H

#include <optional>
#include <string>
#include "skill_type.h"

// This is almost a POD type.
// It's only ever used for communication between classes and functions and such.
// So it's okay for the members to be public.

struct Skill {
public:
    static const std::string SK_STRINGS[skills::NUM_SKILLS_OVERALL];
    
    skill_type which_skill;
    std::optional<std::string> specialty;
    
    Skill(skill_type ws);
    Skill(skill_type ws, std::string subsk);
};

#endif

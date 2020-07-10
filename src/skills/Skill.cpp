#include <optional>
#include <string>
#include "Skill.h"

Skill::Skill(skill_type ws) : which_skill(ws) {
    // nothing required here
}

Skill::Skill(skill_type ws, std::string subsk) :
which_skill(ws), specialty(subsk) {
    // still nothing required here
}

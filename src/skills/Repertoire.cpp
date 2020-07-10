#include <optional>
#include <string>
#include "Skill.h"
#include "Repertoire.h"

Repertoire::Repertoire() {
    no_specialty_ranks = {};
    specialty_ranks = {};
    has_skill = {0};
}

int& Repertoire::get_rank_reference(const Skill& s) {
    skill_type sk_cat = s.which_skill;
    if (skills::SKILL_HAS_SPECIALTIES[sk_cat]) {
        return specialty_ranks[SKILL_INDEX[sk_cat]][s.specialty.value()];
    } else {
        return no_specialty_ranks[SKILL_INDEX[sk_cat]];
    }
}

// Contract: do not invoke this with nonzero r on a specialized
// skill type without indicating a specialty. Checking whether a
// specialized skill's skill category is untrained or rank 0
// is an allowed special case.
std::optional<int> Repertoire::get_rank(const Skill& s) const {
    skill_type sk_cat = s.which_skill;
    std::optional<int> r; // empty optional
    if (!has_skill[sk_cat]) return r; // returns empty. otherwise...
    else if (skills::SKILL_HAS_SPECIALTIES[sk_cat]) {
        if (s.specialty) {
            auto m = specialty_ranks[SKILL_INDEX[sk_cat]];
            auto v = s.specialty.value();
            if (m.find(v) != m.end())
                return m.at(v);
            else return 0;
            // this is a little rickety, but it should work.
            // checks whether the relevant map has the given subspecialty as a key
        } else return 0;
        // this is the case where we're asking
    } else {
        return no_specialty_ranks[SKILL_INDEX[sk_cat]];
    }
    // This looks like repeated code, but it's not exactly.
    // The operator[]s are being called in their const variants,
    // which is incompatible with what get_rank_reference does.
}

// Contract: do not invoke this with nonzero r on a specialized
// skill type without indicating a specialty. Raising a specialized
// skill to rank 0 without a specialty is an allowed special case.
void Repertoire::improve_skill_to_rank(const Skill& s, int r) {
    bool &b = has_skill[s.which_skill];
    if (!b) b = true; // any rank is 0+, so you possess the skill
    if (r > 0) { // IMPORTANT: do NOT try to edit specialized skill ranks
        int &t = get_rank_reference(s);
        if (t < r) t = r;
    }
}

// Contract: do not invoke this on a specialized Skill type
// without indicating a specialty.
void Repertoire::increment_skill_rank(const Skill& s) {
    bool &b = has_skill[s.which_skill];
    // the array entry for knowing this skill at rank 0 or more
    if (!b) {
        b = true; return; // acquire rank 0, don't increment
    } else {
        ++get_rank_reference(s); // already acquired, time to increment
    }
}

bool Repertoire::is_trained(const skill_type& s) const {
    return has_skill[s];
}

void Repertoire::learn_skill(const skill_type& s) {
    has_skill[s] = true;
}

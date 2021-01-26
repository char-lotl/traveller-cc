#include <vector>
#include "skills/skill_type.h"
#include "skills/Repertoire.h"
#include "utils/printing/printout.h"
#include "utils/printing/number_words.h"

#include "query_background_skills.h"
#include "utils/remove_overlap.h"
#include "display_skill_cats.h"
#include "pick_skills_from_list.h"

extern template void remove_overlap(std::vector<skill_type>&,
                                    const std::vector<skill_type>&);

void learn_skills(Repertoire& rep, std::vector<skill_type> const& sks);

using namespace utils::printing;

void query_background_skills(std::vector<skill_type> const& homeworld_skills,
                             int num_bg_skills,
                             Repertoire& rep) {
    
    int num_hw_skills = homeworld_skills.size();
    
    if (num_bg_skills < num_hw_skills) {
        printout() << "Your homeworld poses many challenges, and you"
        " have your hands more than full trying to learn what it has to"
        " offer you. Pick from among the following options:\n";
        
        std::vector<skill_type> selected_skills =
        pick_skills_from_list(homeworld_skills, num_bg_skills);
        
        learn_skills(rep, selected_skills);
    }
    if (num_bg_skills == num_hw_skills) {
        learn_skills(rep, homeworld_skills);
        
        printout() << "Your homeworld poses challenges, and you"
        " have your hands\nfull learning what it has to offer you.\n"
        "You learn the following skills:\n";
        display_skill_cats(homeworld_skills);
    }
    if (num_bg_skills > num_hw_skills) {
        std::vector<skill_type> education_skills{
            ADMIN, ADVOCATE, ART, CAROUSE, COMMS, COMPUTERS,
            DRIVE, ENGINEER, LANGUAGE, MEDIC, SCIENCE_PHYSICAL,
            SCIENCE_LIFE, SCIENCE_SOCIAL, SCIENCE_SPACE, TRADE
        };
        int num_edu_skills = num_bg_skills - num_hw_skills;
        remove_overlap<skill_type>(education_skills, homeworld_skills);
        
        if (num_hw_skills == 0) {
            printout() << "Your homeworld poses no specific challenges to you,\n"
            "growing up, leaving you free to pursue your education.\n"
            "Pick ";
        } else {
            learn_skills(rep, homeworld_skills);
            printout() << "While some of your attention growing up is"
            " directed towards\nthe unique challenges posed by your "
            "environment, you are also\nable to undergo some education.\n"
            "You learn the following skills:\n";
            display_skill_cats(homeworld_skills);
            printout() << "You may also learn ";
            
        }
        printout() << NUMBER_WORDS[num_edu_skills] << " skill" <<
        ((num_edu_skills > 1) ? "s" : "") <<
        " from among the following options:\n";
        
        std::vector<skill_type> selected_skills =
        pick_skills_from_list(education_skills, num_edu_skills);
        
        learn_skills(rep, selected_skills);
    }
    
}

void learn_skills(Repertoire& rep, std::vector<skill_type> const& sks) {
    for (skill_type const& s : sks) {
        rep.learn_skill(s);
    }
}

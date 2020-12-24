#include <list>
#include "skills/skill_type.h"
#include "skills/Repertoire.h"
#include "utils/printing/printout.h"
#include "utils/printing/number_words.h"

#include "query_background_skills.h"
#include "utils/remove_overlap.h"
#include "display_skill_cats_from_list.h"
#include "pick_skills_from_list.h"

extern template void remove_overlap(std::list<skill_type>&,
                                    const std::list<skill_type>&);

void learn_skill_list(Repertoire& rep, std::list<skill_type> sk_li);

using namespace utils::printing;

void query_background_skills(std::list<skill_type>& homeworld_skills,
                             const int& num_bg_skills,
                             Repertoire& rep) {
    
    int num_hw_skills = homeworld_skills.size();
    
    if (num_bg_skills < num_hw_skills) {
        printout() << "Your homeworld poses many challenges, and you"
        " have your hands more than full trying to learn what it has to"
        " offer you. Pick from among the following options:\n";
        
        std::list<skill_type> selected_skills =
        pick_skills_from_list(homeworld_skills, num_bg_skills);
        
        learn_skill_list(rep, selected_skills);
    }
    if (num_bg_skills == num_hw_skills) {
        learn_skill_list(rep, homeworld_skills);
        
        printout() << "Your homeworld poses challenges, and you"
        " have your hands\nfull learning what it has to offer you.\n"
        "You learn the following skills:\n";
        display_skill_cats_from_list(homeworld_skills);
    }
    if (num_bg_skills > num_hw_skills) {
        std::list<skill_type> education_skills{
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
            learn_skill_list(rep, homeworld_skills);
            printout() << "While some of your attention growing up is"
            " directed towards\nthe unique challenges posed by your "
            "environment, you are also\nable to undergo some education.\n"
            "You learn the following skills:\n";
            display_skill_cats_from_list(homeworld_skills);
            printout() << "You may also learn ";
            
        }
        printout() << NUMBER_WORDS[num_edu_skills] << " skill" <<
        ((num_edu_skills > 1) ? "s" : "") <<
        " from among the following options:\n";
        
        std::list<skill_type> selected_skills =
        pick_skills_from_list(education_skills, num_edu_skills);
        
        learn_skill_list(rep, selected_skills);
    }
    
}

void learn_skill_list(Repertoire& rep, std::list<skill_type> sk_li) {
    for (skill_type s : sk_li) {
        rep.learn_skill(s);
    }
}

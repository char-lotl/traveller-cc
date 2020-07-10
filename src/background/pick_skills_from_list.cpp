#include <list>
#include <vector>
#include "skills/skill_type.h"
#include "skills/Repertoire.h"
#include "utils/printing/printout.h"
#include "utils/utils.h"

#include "pick_skills_from_list.h"
#include "display_skill_cats_from_list.h"

using namespace utils::printing;

void display_skills_vertically(const std::vector<skill_type>& skill_list,
                               const std::vector<bool>& available);

std::list<skill_type> pick_skills_from_list(const std::list<skill_type>& skill_list,
                                            int num_skills) {
    int list_length = skill_list.size();
    char max_skill_letter = 'a' - 1 + list_length;
    std::vector<skill_type> skill_vector(skill_list.begin(), skill_list.end());
    
    std::list<skill_type> selected;
    std::vector<bool> available(list_length, true);
    
    char response_char;
    int response_num;
    
    bool first = true;
    while (num_skills > 0) {
        display_skills_vertically(skill_vector, available);
        if (first) first = false;
        else printout() << "Select " << NUMBER_WORDS[num_skills] <<
            " more skill" << ((num_skills > 1) ? "s" : "") << ".\n";
        response_char =
            utils::get_char_response_in_range("Enter the letter corresponding"
                                              " to a skill to select it: ",
                                              'a', max_skill_letter);
        response_num = response_char - 'a';
        if (available[response_num]) {
            available[response_num] = false;
            selected.push_back(skill_vector[response_num]);
            --num_skills;
        } else {
            printout() << "That skill has already been selected.\n";
            continue;
        }
    }
    
    selected.sort();
    
    printout() << "Selection complete. You learn the following skills:\n";
    display_skill_cats_from_list(selected);
    
    return selected;
    
}

void display_skills_vertically(const std::vector<skill_type>& skill_vector,
                               const std::vector<bool>& available) {
    for (unsigned int i = 0; i < skill_vector.size(); i++) if (available[i]) {
        printout() << (char)('a' + i) << ". " <<
        skills::SK_STRINGS[skill_vector[i]] << "\n";
    }
}

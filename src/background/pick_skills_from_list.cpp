#include <vector>
#include "skills/skill_type.h"
#include "skills/Repertoire.h"
#include "utils/printing/printout.h"
#include "utils/printing/number_words.h"
#include "utils/printing/Formatter.h"
#include "utils/utils.h"

#include "pick_skills_from_list.h"
#include "display_skill_cats.h"

using namespace utils::printing;

void display_skills_tabular(const std::vector<skill_type>& skill_vector,
							const std::vector<bool>& available);

std::vector<skill_type> pick_skills_from_list(const std::vector<skill_type>& stypes,
											  int num_skills) {
    int num_options = stypes.size();
    char max_skill_letter = 'a' - 1 + num_options;
    
    std::vector<skill_type> selected;
    std::vector<bool> available(num_options, true);
    
    char response_char;
    int response_num;
    
    bool first = true;
    while (num_skills > 0) {
        display_skills_tabular(stypes, available);
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
            selected.push_back(stypes[response_num]);
            --num_skills;
        } else {
            printout() << "That skill has already been selected.\n";
            continue;
        }
    }
    
    std::sort(selected.begin(), selected.end());
    
    printout() << "Selection complete. You learn the following skills:\n";
    display_skill_cats(selected);
    
    return selected;
    
}

void display_skills_tabular(const std::vector<skill_type>& skill_vector,
							const std::vector<bool>& available) {
	std::vector<std::string> available_skill_strings;
	
    for (unsigned int i = 0; i < skill_vector.size(); i++) if (available[i]) {
        available_skill_strings.push_back(std::string(1, (char)('a' + i)) +
										  ". " +
										  skills::SK_STRINGS[skill_vector[i]]);
    }
	
	printout() << TabularList(available_skill_strings);
	
}

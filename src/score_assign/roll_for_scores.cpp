#include <vector>
#include <algorithm>
#include <string>
#include "utils/utils.h"
#include "config/get_rules.h"
#include "utils/Roller.h"
#include "utils/printing/printout.h"
#include "utils/printing/Formatter.h"

#include "utils/integer_log2.h"
#include "roll_for_scores.h"
#include "display_scores.h"

enum yarb_type {
    NO_YARB = 1,
    LOW_MAX = 2,
    LOW_OVERALL = 3
};

using namespace utils::printing;
using namespace config;

yarb_type check_for_yarborough(const std::vector<int> &scores);

void roll_for_scores(std::vector<int> &characteristic_scores) {
    std::string response;
    std::vector<int> characteristic_rolls(6);
    
    while (true) {
        
        printout() << "Rolling characteristics...\n";
		
        for (int i = 0; i < 6; i++) {
            characteristic_rolls[i] = Roller::roll2d6();
        }
        std::sort(characteristic_rolls.begin(), characteristic_rolls.end());
        std::reverse(characteristic_rolls.begin(), characteristic_rolls.end());
        
		printout() << "Characteristic scores are: ";
		
		std::vector<std::string> score_strings;
		for (const int i : characteristic_rolls) {
			score_strings.push_back(std::to_string(i));
		}
		printout() << CommaListAnd(score_strings);
        
        yarb_type yarb = NO_YARB;
        
        if (get_toggle_rule(rule_type::YARBOROUGH_DETECTION)) {
        
            yarb = check_for_yarborough(characteristic_rolls);
            
            switch(yarb) {
                case NO_YARB: break;
                case LOW_MAX:
                    printout() <<
                        "Abnormally low scores: one or fewer scores exceeding 6. ";
                    break;
                case LOW_OVERALL:
                    printout() << "Abnormally low scores: total modifier -3 or worse. ";
                default: break;
            }
            
        }
        
        if (get_toggle_rule(rule_type::REROLL_QUERY) ||
            (get_toggle_rule(rule_type::YARBOROUGH_REROLL_OVERRIDE) &&
             (yarb != NO_YARB))) {
            
            if (utils::get_bool_response("Keep scores? (y/n) ")) break;
            else continue;
                
        } else break;
        
    }
    
    std::vector<bool> scores_assigned(6, false);
    int which_remain = 63;
    
    for (int i = 0; i < 5; i++) {
        
        std::string qstring = "Which characteristic should the " +
            std::to_string(characteristic_rolls[i]) + " go to? ";
        
		std::vector<std::string> tabular_prompt;
		std::string current_entry;
		
        bool first = true;
        for (int j = 0; j < 6; j++) {
			if (scores_assigned[j]) current_entry = "   ---";
			else current_entry = std::string(1, 'a' + j)
				+ ". " + utils::characteristic_abbrev[j];
			tabular_prompt.push_back(current_entry);
        }
		
		printout() << TabularList(tabular_prompt);
        
        int response_num;
        
        while (true) {
            
            response_num = utils::get_char_response_in_range(qstring, 'a', 'f') - 'a';
            
            if (scores_assigned[response_num]) {
                printout() << "That characteristic has already been assigned" <<
                " a score.\n";
                continue;
            } else break;
        }
            
        characteristic_scores[response_num] = characteristic_rolls[i];
        scores_assigned[response_num] = true;
        which_remain -= (1 << response_num); // 2 ^ response_num
        
        if (i != 4) {
            first = true;
			std::vector<std::string> score_report_strings;
            for (int j = 0; j < 6; j++) {
                if (scores_assigned[j])
					score_report_strings.push_back(utils::characteristic_abbrev[j]
												   + " is "
												   + std::to_string(characteristic_scores[j]));
            }
			printout() << CommaList(score_report_strings);
        }
        
    }
    
    int which_is_left = utils::integer_log2(which_remain);
    
    characteristic_scores[which_is_left] = characteristic_rolls[5];
    scores_assigned[which_is_left] = true;
    
    display_scores_inline(characteristic_scores);
}

yarb_type check_for_yarborough(const std::vector<int> &scores) {
    if (scores[1] <= 6) return LOW_MAX; // second-highest is 6 or smaller
    int overall_mod = 0;
    for (int i = 0; i < 6; i++) {
        overall_mod += utils::char_modifier_from_score(scores[i]);
    }
    if (overall_mod <= -3) return LOW_OVERALL;
    return NO_YARB;
}

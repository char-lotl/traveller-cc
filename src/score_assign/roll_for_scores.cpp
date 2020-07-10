#include <array>
#include <algorithm>
#include <string>
#include "utils/utils.h"
#include "config/Rules.h"
#include "utils/Roller.h"
#include "utils/printing/printout.h"

#include "utils/integer_log2.h"
#include "roll_for_scores.h"
#include "display_scores.h"

enum yarb_type {
    NO_YARB = 1,
    LOW_MAX = 2,
    LOW_OVERALL = 3
};

using namespace utils::printing;

yarb_type check_for_yarborough(const std::array<int,6> &scores);

void roll_for_scores(std::array<int,6> &characteristic_scores,
                     const Rules &ru) {
    std::string response;
    std::array<int,6> characteristic_rolls;
    
    while (true) {
        
        printout() << "Rolling characteristics...\n";
        
        for (int i = 0; i < 6; i++) {
            characteristic_rolls[i] = Roller::roll2d6();
        }
        std::sort(characteristic_rolls.begin(), characteristic_rolls.end());
        std::reverse(characteristic_rolls.begin(), characteristic_rolls.end());
        
        printout() << "Characteristic scores are: " << characteristic_rolls[0] <<
        ", " << characteristic_rolls[1] << ", " << characteristic_rolls[2] <<
        ", " << characteristic_rolls[3] << ", " << characteristic_rolls[4] <<
        ", and " << characteristic_rolls[5] << ".\n";
        
        yarb_type yarb = NO_YARB;
        
        if (ru.get_toggle_rule(rule_type::YARBOROUGH_DETECTION)) {
        
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
        
        if (ru.get_toggle_rule(rule_type::REROLL_QUERY) ||
            (ru.get_toggle_rule(rule_type::YARBOROUGH_REROLL_OVERRIDE) &&
             (yarb != NO_YARB))) {
            
            if (utils::get_bool_response("Keep scores? (y/n) ")) break;
            else continue;
                
        } else break;
        
    }
    
    std::array<bool,6> scores_assigned{};
    int which_remain = 63;
    
    for (int i = 0; i < 5; i++) {
        
        std::string qstring = "Which characteristic should the " +
            std::to_string(characteristic_rolls[i]) + " go to?\n(";
        
        bool first = true;
        for (int j = 0; j < 6; j++) {
            std::string supp = "";
            if (!scores_assigned[j]) {
                if (!first) qstring = qstring + ", ";
                qstring = qstring + std::to_string(j) + " for " +
                    utils::characteristic_abbrev(j);
                first = false;
            }
        }
        qstring = qstring + ") ";
        
        int response_num;
        
        while (true) {
            
            response_num = utils::get_int_response_in_range(qstring, 0, 5);
            
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
            for (int j = 0; j < 6; j++) {
                if (scores_assigned[j]) {
                    if (!first) printout() << ", ";
                    printout() << utils::characteristic_abbrev(j) << " is " <<
                    characteristic_scores[j];
                    first = false;
                }
            }
            printout() << ".\n";
        }
        
    }
    
    int which_is_left = utils::integer_log2(which_remain);
    
    characteristic_scores[which_is_left] = characteristic_rolls[5];
    scores_assigned[which_is_left] = true;
    
    display_scores_inline(characteristic_scores);
}

yarb_type check_for_yarborough(const std::array<int,6> &scores) {
    if (scores[1] <= 6) return LOW_MAX; // second-highest is 6 or smaller
    int overall_mod = 0;
    for (int i = 0; i < 6; i++) {
        overall_mod += utils::char_modifier_from_score(scores[i]);
    }
    if (overall_mod <= -3) return LOW_OVERALL;
    return NO_YARB;
}

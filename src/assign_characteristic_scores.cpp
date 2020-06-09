#include <iostream>
//#include <fstream>
#include <vector>
#include <string>
#include "assign_characteristic_scores.h"
#include "utils.h"
#include "Rules.h"

enum yarb_type {
    NO_YARB = 1,
    LOW_MAX = 2,
    LOW_OVERALL = 3
};

enum point_buy_state {
    START_BUY,
    CHANGING_SCORE,
    CONFIRM_BUY,
    EXIT_BUY
};

const std::string IN_TYPE_QSTRING = "How would you like to input your characteristic scores?\n(0 for rolling, 1 for manual entry, 2 for point-buy) ";
const std::string UNSPENT_POINTS = "Unspent points remaining. Continue anyway? (y/n) ";

const int MIN_POINT_BUY = 4;
const int MAX_POINT_BUY = 11;
const int SCORE_COSTS[] = {0, 1, 3, 5, 7, 10, 13, 17};


yarb_type check_for_yarborough(std::vector<int> &scores);
void roll_for_scores(Roller &r,
                     std::vector<int> &characteristic_scores,
                     Rules &ru);
score_input_method::input_type query_input_method();
void manually_input_scores(std::vector<int> &characteristic_scores);
void point_buy_scores(std::vector<int> &characteristic_scores);

void display_all_scores(std::vector<int> &characteristic_scores);
void display_scores_vertical(std::vector<int> &characteristic_scores);

void assign_characteristic_scores(Roller &r,
                                  std::vector<int> &characteristic_scores,
                                  Rules &ru){
    
    bool query_method = ru.get_toggle_rule(rule_type::ASSIGN_METHOD_QUERY);
    int in_type; // must use int because get_int_rule returns this
    
    if (query_method) in_type = query_input_method();
    else in_type = ru.get_int_rule(rule_type::DEFAULT_ASSIGN_METHOD);
    
    switch(in_type) {
        case score_input_method::ROLL_SCORES:
            roll_for_scores(r, characteristic_scores, ru);
            break;
        case score_input_method::MANUAL_ENTRY:
            manually_input_scores(characteristic_scores);
            break;
        case score_input_method::POINT_BUY:
            point_buy_scores(characteristic_scores);
            break;
    }
}

yarb_type check_for_yarborough(std::vector<int> &scores) {
    if (scores[1] <= 6) return LOW_MAX; // second-highest is 6 or smaller
    int overall_mod = 0;
    for (int i = 0; i < 6; i++) {
        overall_mod += utils::char_modifier_from_score(scores[i]);
    }
    if (overall_mod <= -3) return LOW_OVERALL;
    return NO_YARB;
}

void roll_for_scores(Roller &r,
                     std::vector<int> &characteristic_scores,
                     Rules &ru) {
    std::string response;
    std::vector<int> characteristic_rolls;
    
    while (true) {
        
        std::cout << "Rolling characteristics..." << std::endl;
        
        for (int i = 0; i < 6; i++) {
            characteristic_rolls.push_back(r.roll2d6());
        }
        std::sort(characteristic_rolls.begin(), characteristic_rolls.end());
        std::reverse(characteristic_rolls.begin(), characteristic_rolls.end());
        
        std::cout << "Characteristic scores are: " << characteristic_rolls[0] <<
            ", " << characteristic_rolls[1] << ", " << characteristic_rolls[2] <<
            ", " << characteristic_rolls[3] << ", " << characteristic_rolls[4] <<
            ", and " << characteristic_rolls[5] << "." << std::endl;
        
        yarb_type yarb = NO_YARB;
        
        if (ru.get_toggle_rule(rule_type::YARBOROUGH_DETECTION)) {
        
            yarb = check_for_yarborough(characteristic_rolls);
            
            switch(yarb) {
                case NO_YARB: break;
                case LOW_MAX:
                    std::cout <<
                        "Abnormally low scores: one or fewer scores exceeding 6. ";
                    break;
                case LOW_OVERALL:
                    std::cout << "Abnormally low scores: total modifier -3 or worse. ";
                default: break;
            }
            
        }
        
        if (ru.get_toggle_rule(rule_type::REROLL_QUERY) ||
            (ru.get_toggle_rule(rule_type::YARBOROUGH_REROLL_OVERRIDE) &&
             (yarb != NO_YARB))) {
            
            if (utils::get_bool_response("Keep scores? (y/n) ")) break;
            else characteristic_rolls.erase(characteristic_rolls.begin(),
                                            characteristic_rolls.end());
                
        } else break;
        
    }
    
    std::vector<bool> scores_assigned(6, false);
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
                std::cout << "That characteristic has already been assigned" <<
                " a score." << std::endl;
                continue;
            } else break;
        }
            
        characteristic_scores[response_num] = characteristic_rolls[i];
        scores_assigned[response_num] = true;
        which_remain -= utils::POW2S[response_num];
        
        if (i != 4) {
            first = true;
            for (int j = 0; j < 6; j++) {
                if (scores_assigned[j]) {
                    if (!first) std::cout << ", ";
                    std::cout << utils::characteristic_abbrev(j) << " is " <<
                    characteristic_scores[j];
                    first = false;
                }
            }
            std::cout << "." << std::endl;
        }
        
    }
    
    int which_is_left = 0;
    switch(which_remain) {
        case 1:
            which_is_left = 0; break;
        case 2:
            which_is_left = 1; break;
        case 4:
            which_is_left = 2; break;
        case 8:
            which_is_left = 3; break;
        case 16:
            which_is_left = 4; break;
        case 32:
            which_is_left = 5; break;
        default:
            break;
    }
    
    characteristic_scores[which_is_left] = characteristic_rolls[5];
    scores_assigned[which_is_left] = true;
    
    display_all_scores(characteristic_scores);
}

score_input_method::input_type query_input_method() {
    int response_num = utils::get_int_response_in_range(IN_TYPE_QSTRING, 0, 2);
    
    switch(response_num) {
        case 0: return score_input_method::ROLL_SCORES;
        case 1: return score_input_method::MANUAL_ENTRY;
        case 2: return score_input_method::POINT_BUY;
        default: return score_input_method::ROLL_SCORES;
    }
}

void manually_input_scores(std::vector<int> &characteristic_scores) {
    int response_num;
    for (int i = 0; i < 6; i++) {
        std::string qstring = "Enter the score for " +
        utils::characteristic_abbrev(i) + " (2 - 12): ";
        response_num = utils::get_int_response_in_range(qstring, 2, 12);
        characteristic_scores[i] = response_num;
    }
    display_all_scores(characteristic_scores);
}

void point_buy_scores(std::vector<int> &characteristic_scores) {
    characteristic_scores.assign(6, 6);
    int points_left = 12;
    int current_score_buying = 0;
    int current_value;
    int proposed_cost;
    std::string discard_string;
    std::string qstring;
    int response_num;
    point_buy_state pbs = START_BUY;
    
    while (pbs != EXIT_BUY) {
        switch(pbs) {
            case START_BUY:
                display_scores_vertical(characteristic_scores);
                if (points_left != 0)
                    discard_string = "discard any remaining points,\n";
                else discard_string = "";
                qstring = "You have " + std::to_string(points_left) +
                    " points remaining.\nEnter a number (1 - 6) to select\n" +
                    "a characteristic score to change,\nor 0 to " +
                    discard_string + "confirm your score allocation and proceed: ";
                response_num = utils::get_int_response_in_range(qstring, 0, 6);
                if (response_num == 0) pbs = CONFIRM_BUY;
                else {
                    pbs = CHANGING_SCORE;
                    current_score_buying = response_num - 1;
                }
                break;
            case CHANGING_SCORE:
                current_value = characteristic_scores[current_score_buying];
                qstring = utils::characteristic_abbrev(current_score_buying) +
                    "\'s current value is " + std::to_string(current_value) +
                    ". Enter a new value (" + std::to_string(MIN_POINT_BUY) +
                    " - " + std::to_string(MAX_POINT_BUY) + "): ";
                response_num = utils::get_int_response_in_range(qstring,
                                                                MIN_POINT_BUY,
                                                                MAX_POINT_BUY);
                proposed_cost = SCORE_COSTS[response_num - MIN_POINT_BUY] -
                    SCORE_COSTS[current_value - MIN_POINT_BUY];
                if (points_left >= proposed_cost) {
                    characteristic_scores[current_score_buying] = response_num;
                    points_left -= proposed_cost;
                } else {
                    std::cout << "Insufficient points for this operation." <<
                        std::endl;
                    std::cout << "Consider lowering another characteristic" <<
                        " score to free up points." << std::endl;
                }
                pbs = START_BUY;
                break;
            case CONFIRM_BUY:
                if ((points_left > 0) &&
                    !utils::get_bool_response(UNSPENT_POINTS)) {
                    pbs = START_BUY;
                    break;
                }
                std::cout << "Characteristic scores confirmed. Point buy complete."
                    << std::endl;
                pbs = EXIT_BUY;
                break;
            case EXIT_BUY:
                break;
            default:
                break;
        }
        
    }
    
}

void display_all_scores(std::vector<int> &characteristic_scores) {
    bool first = true;
    for (int j = 0; j < 6; j++) {
        if (!first) std::cout << ", ";
        std::cout << utils::characteristic_abbrev(j) << " is " <<
            characteristic_scores[j];
        first = false;
    }
    std::cout << "." << std::endl;
}

void display_scores_vertical(std::vector<int> &characteristic_scores) {
    for (int j = 0; j < 6; j++) {
        std::cout << std::to_string(j + 1) << ". ";
        std::cout << utils::characteristic_abbrev(j) << " is " <<
            characteristic_scores[j] << std::endl;
    }
}

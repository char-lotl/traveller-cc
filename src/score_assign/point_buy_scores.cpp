#include <array>
#include <string>
#include "utils/utils.h"
#include "utils/printing/printout.h"

#include "display_scores.h"
#include "point_buy_scores.h"

enum point_buy_state {
    START_BUY,
    CHANGING_SCORE,
    CONFIRM_BUY,
    EXIT_BUY
};

const int MIN_POINT_BUY = 4;
const int MAX_POINT_BUY = 11;
const int SCORE_COSTS[] = {0, 1, 3, 5, 7, 10, 13, 17};

using namespace utils::printing;

void point_buy_scores(std::array<int,6> &characteristic_scores) {
    characteristic_scores.fill(6);
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
                    discard_string = "discard any remaining points, ";
                else discard_string = "";
                qstring = "You have " + std::to_string(points_left) +
                    " points remaining.\nEnter a number (1 - 6) to select "
                    "a characteristic score to change, or 0 to " +
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
                qstring = utils::characteristic_abbrev[current_score_buying] +
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
                    printout() << "Insufficient points for this operation.\n";
                    printout() << "Consider lowering another characteristic" <<
                        " score to free up points.\n";
                }
                pbs = START_BUY;
                break;
            case CONFIRM_BUY:
                if ((points_left > 0) &&
                    !utils::get_bool_response("Unspent points remaining. "
                                              "Continue anyway? (y/n) ")) {
                    pbs = START_BUY;
                    break;
                }
                printout() << "Characteristic scores confirmed. Point buy complete.\n";
                pbs = EXIT_BUY;
                break;
            case EXIT_BUY:
                break;
            default:
                break;
        }
        
    }
    
}

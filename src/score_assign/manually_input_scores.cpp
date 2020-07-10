#include <array>
#include <string>
#include "utils/utils.h"

#include "manually_input_scores.h"
#include "display_scores.h"

void manually_input_scores(std::array<int,6> &characteristic_scores) {
    int response_num;
    for (int i = 0; i < 6; i++) {
        std::string qstring = "Enter the score for " +
        utils::characteristic_abbrev(i) + " (2 - 12): ";
        response_num = utils::get_int_response_in_range(qstring, 2, 12);
        characteristic_scores[i] = response_num;
    }
    display_scores_inline(characteristic_scores);
}

#include "utils/utils.h"
#include "query_input_method.h"

input_type query_input_method() {
    int response_num = utils::get_int_response_in_range("How would you like"
        " to input your characteristic scores?\n(0 for rolling, "
        "1 for manual entry, 2 for point-buy) ", 0, 2);
    
    switch(response_num) {
        case 0: return ROLL_SCORES;
        case 1: return MANUAL_ENTRY;
        case 2: return POINT_BUY;
        default: return ROLL_SCORES;
    }
}

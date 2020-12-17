#include "utils/utils.h"
#include "query_input_method.h"

input_type query_input_method() {
    int response = utils::get_char_from_choices("How would you like"
        " to input your characteristic scores:\n[r]olling / "
        "[m]anual entry / [p]oint-buy? ", "rmp");
    
    switch(response) {
        case 0: return ROLL_SCORES;
        case 1: return MANUAL_ENTRY;
        case 2: return POINT_BUY;
        default: return ROLL_SCORES;
    }
}

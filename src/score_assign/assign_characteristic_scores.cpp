#include <vector>
#include "config/get_rules.h"

#include "assign_characteristic_scores.h"
#include "query_input_method.h"
#include "roll_for_scores.h"
#include "manually_input_scores.h"
#include "point_buy_scores.h"

using namespace config;

void assign_characteristic_scores(std::vector<int>& characteristic_scores){
    
    bool query_method = get_toggle_rule(rule_type::ASSIGN_METHOD_QUERY);
    int in_type; // must use int because get_int_rule returns this
    
    if (query_method) in_type = query_input_method();
    else in_type = get_int_rule(rule_type::DEFAULT_ASSIGN_METHOD);
    
    switch(in_type) {
        case ROLL_SCORES:
            roll_for_scores(characteristic_scores);
            break;
        case MANUAL_ENTRY:
            manually_input_scores(characteristic_scores);
            break;
        case POINT_BUY:
            point_buy_scores(characteristic_scores);
            break;
    }
}

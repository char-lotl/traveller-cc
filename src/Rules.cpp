//#include <iostream>
//#include <random>
#include "Rules.h"

//using namespace std;

Rules::Rules(std::shared_ptr<std::vector<bool> > trp,
             std::shared_ptr<std::vector<int> > irp)
    : toggle_rules(*trp), int_rules(*irp) {
    // everything's handled by the initialization list
}

bool Rules::get_toggle_rule(rule_type::toggle_rule_type trt) {
    return toggle_rules[trt];
}

int Rules::get_int_rule(rule_type::int_rule_type irt) {
    return int_rules[irt];
}

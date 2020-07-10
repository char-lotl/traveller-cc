#include <array>
#include "Rules.h"

Rules::Rules(const std::array<bool,NUM_TOGGLE_RULES>& trp,
             const std::array<int,NUM_INT_RULES>& irp) :
             toggle_rules(trp), int_rules(irp) {
    // everything's handled by the initialization list
}

Rules::Rules(std::array<bool,NUM_TOGGLE_RULES>&& trp,
             std::array<int,NUM_INT_RULES>&& irp) :
             toggle_rules(trp), int_rules(irp) {
}

bool Rules::get_toggle_rule(const rule_type::toggle_rule_type& trt) const {
    return toggle_rules[trt];
}

int Rules::get_int_rule(const rule_type::int_rule_type& irt) const {
    return int_rules[irt];
}

#ifndef GET_RULES_H
#define GET_RULES_H

#include "rule_type.h"
class Rules;

namespace config {
    const Rules& get_rules();
	int get_int_rule(rule_type::int_rule_type irt);
	bool get_toggle_rule(rule_type::toggle_rule_type trt);
}

#endif


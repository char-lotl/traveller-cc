#include "Rules.h"
#include "read_in_preferences.h"
#include "get_rules.h"

const Rules& config::get_rules() {
    static const Rules r{read_in_preferences()};
    
    return r;
}

int config::get_int_rule(rule_type::int_rule_type irt) {
	return config::get_rules().get_int_rule(irt);
}

bool config::get_toggle_rule(rule_type::toggle_rule_type trt) {
	return config::get_rules().get_toggle_rule(trt);
}

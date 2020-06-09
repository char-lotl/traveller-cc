#ifndef RULES_H
#define RULES_H

#include <vector>
#include <memory>

namespace rule_type {
    enum toggle_rule_type {
        ASSIGN_METHOD_QUERY,
        REROLL_QUERY,
        YARBOROUGH_DETECTION,
        YARBOROUGH_REROLL_OVERRIDE,
        TOGGLE_END
    };

    enum int_rule_type {
        DEFAULT_ASSIGN_METHOD,
        INT_END
    };
}

namespace score_input_method {
    enum input_type {
        ROLL_SCORES,
        MANUAL_ENTRY,
        POINT_BUY
    };
};

class Rules {
private:
    std::vector<bool> toggle_rules;
    std::vector<int> int_rules;
public:
    Rules(std::shared_ptr<std::vector<bool> > trp,
          std::shared_ptr<std::vector<int> > irp);
    bool get_toggle_rule(rule_type::toggle_rule_type trt);
    int get_int_rule(rule_type::int_rule_type irt);
    //
};

#endif

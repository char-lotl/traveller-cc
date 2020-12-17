#ifndef RULES_H
#define RULES_H

#include <array>
#include "rule_type.h"

class Rules {
public:
    static const int NUM_TOGGLE_RULES = rule_type::TOGGLE_END;
    static const int NUM_INT_RULES = rule_type::INT_END;

    Rules(const std::array<bool,NUM_TOGGLE_RULES>& trp,
          const std::array<int,NUM_INT_RULES>& irp);
    Rules(std::array<bool,NUM_TOGGLE_RULES>&& trp,
          std::array<int,NUM_INT_RULES>&& irp);
    bool get_toggle_rule(const rule_type::toggle_rule_type& trt) const;
    int get_int_rule(const rule_type::int_rule_type& irt) const;
    //
private:
    std::array<bool,NUM_TOGGLE_RULES> toggle_rules;
    std::array<int,NUM_INT_RULES> int_rules;
};

#endif

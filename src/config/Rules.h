#ifndef RULES_H
#define RULES_H

#include <array>

namespace rule_type {
    enum toggle_rule_type {
        ASSIGN_METHOD_QUERY,
        REROLL_QUERY,
        YARBOROUGH_DETECTION,
        YARBOROUGH_REROLL_OVERRIDE,
        TRADE_CODE_METHOD_QUERY,
        SPARSE_CODE_CONFLICTS,
        GENERATION_VARIANT_QUERY,
        TOGGLE_END
    };

    enum int_rule_type {
        DEFAULT_ASSIGN_METHOD,
        DEFAULT_CODE_METHOD,
        DEFAULT_GENERATION_VARIANT,
        INT_END
    };
}

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

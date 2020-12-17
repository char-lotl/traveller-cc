#ifndef RULE_TYPE_H
#define RULE_TYPE_H

namespace rule_type {
    enum toggle_rule_type {
        ASSIGN_METHOD_QUERY,
        REROLL_QUERY,
        YARBOROUGH_DETECTION,
        YARBOROUGH_REROLL_OVERRIDE,
        TRADE_CODE_METHOD_QUERY,
        SPARSE_CODE_CONFLICTS,
        GENERATION_VARIANT_QUERY,
		ALLOW_HOMEWORLD_REROLL,
        TOGGLE_END
    };

    enum int_rule_type {
        DEFAULT_ASSIGN_METHOD,
        DEFAULT_CODE_METHOD,
        DEFAULT_GENERATION_VARIANT,
        INT_END
    };
}

#endif

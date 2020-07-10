#include <fstream>
#include <array>
#include <string>
#include "Rules.h"
#include "utils/printing/printout.h"

#include "read_in_preferences.h"

enum read_phase {
    INITIAL_PHASE,
    ASSIGN_METHOD_QUERY,
    REROLL_QUERY,
    YARBOROUGH_DETECTION,
    YARBOROUGH_REROLL_OVERRIDE,
    DEFAULT_ASSIGN_METHOD,
    END_ASSIGN_PHASE,
    BEGIN_BACKGROUND,
    TRADE_CODE_METHOD_QUERY,
    DEFAULT_CODE_METHOD,
    SPARSE_CODE_CONFLICTS,
    GENERATION_VARIANT_QUERY,
    DEFAULT_GENERATION_VARIANT,
    END_BACKGROUND_PHASE,
    END_PHASE,
    EXIT_ERROR
};

enum class LineType {
    LINE_COMMAND,
    LINE_TOGGLE_RULE,
    LINE_INT_RULE
};

const int NUM_PHASES = END_PHASE;

const std::string PROMPTS[NUM_PHASES] = {
    [INITIAL_PHASE] = "BEGIN ASSIGNSCORES",
    [ASSIGN_METHOD_QUERY] = "ASSIGN_METHOD_QUERY",
    [REROLL_QUERY] = "REROLL_QUERY",
    [YARBOROUGH_DETECTION] = "YARBOROUGH_DETECTION",
    [YARBOROUGH_REROLL_OVERRIDE] = "YARBOROUGH_REROLL_OVERRIDE",
    [DEFAULT_ASSIGN_METHOD] = "DEFAULT_ASSIGN_METHOD",
    [END_ASSIGN_PHASE] = "END",
    [BEGIN_BACKGROUND] = "BEGIN BACKGROUND",
    [TRADE_CODE_METHOD_QUERY] = "TRADE_CODE_METHOD_QUERY",
    [DEFAULT_CODE_METHOD] = "DEFAULT_CODE_METHOD",
    [SPARSE_CODE_CONFLICTS] = "SPARSE_CODE_CONFLICTS",
    [GENERATION_VARIANT_QUERY] = "GENERATION_VARIANT_QUERY",
    [DEFAULT_GENERATION_VARIANT] = "DEFAULT_GENERATION_VARIANT",
    [END_BACKGROUND_PHASE] = "END"
};

const int RULES_IN_ORDER[NUM_PHASES] = {
    [ASSIGN_METHOD_QUERY] = rule_type::ASSIGN_METHOD_QUERY,
    [REROLL_QUERY] = rule_type::REROLL_QUERY,
    [YARBOROUGH_DETECTION] = rule_type::YARBOROUGH_DETECTION,
    [YARBOROUGH_REROLL_OVERRIDE] = rule_type::YARBOROUGH_REROLL_OVERRIDE,
    [DEFAULT_ASSIGN_METHOD] = rule_type::DEFAULT_ASSIGN_METHOD,
    [TRADE_CODE_METHOD_QUERY] = rule_type::TRADE_CODE_METHOD_QUERY,
    [DEFAULT_CODE_METHOD] = rule_type::DEFAULT_CODE_METHOD,
    [SPARSE_CODE_CONFLICTS] = rule_type::SPARSE_CODE_CONFLICTS,
    [GENERATION_VARIANT_QUERY] = rule_type::GENERATION_VARIANT_QUERY
};

const LineType LINE_TYPES_IN_ORDER[NUM_PHASES] = {
    [INITIAL_PHASE] = LineType::LINE_COMMAND,
    [ASSIGN_METHOD_QUERY] = LineType::LINE_TOGGLE_RULE,
    [REROLL_QUERY] = LineType::LINE_TOGGLE_RULE,
    [YARBOROUGH_DETECTION] = LineType::LINE_TOGGLE_RULE,
    [YARBOROUGH_REROLL_OVERRIDE] = LineType::LINE_TOGGLE_RULE,
    [DEFAULT_ASSIGN_METHOD] = LineType::LINE_INT_RULE,
    [END_ASSIGN_PHASE] = LineType::LINE_COMMAND,
    [BEGIN_BACKGROUND] = LineType::LINE_COMMAND,
    [TRADE_CODE_METHOD_QUERY] = LineType::LINE_TOGGLE_RULE,
    [DEFAULT_CODE_METHOD] = LineType::LINE_INT_RULE,
    [SPARSE_CODE_CONFLICTS] = LineType::LINE_TOGGLE_RULE,
    [GENERATION_VARIANT_QUERY] = LineType::LINE_TOGGLE_RULE,
    [DEFAULT_GENERATION_VARIANT] = LineType::LINE_INT_RULE,
    [END_BACKGROUND_PHASE] = LineType::LINE_COMMAND
};

// MUST maintain consistency between read_phase enum, PROMPTS array,
// RULES_IN_ORDER array, LINE_TYPES_IN_ORDER array, and (from Rules.h)
// the toggle_rule_type and int_rule_type enums.



void read_command_phrase(const std::string& command_phrase,
                         const std::string& data_in,
                         int& r);

void read_toggle_phase(const std::string& phase_declare,
                       const std::string& data_in,
                       std::array<bool,Rules::NUM_TOGGLE_RULES>& rule_set,
                       const int& which_rule,
                       int& r);

void read_int_phase(const std::string& phase_declare,
                    const std::string& data_in,
                    std::array<int,Rules::NUM_INT_RULES>& rule_set,
                    const int& which_rule,
                    int& r);

using namespace utils::printing;

Rules read_in_preferences() {
    std::ifstream infile;
    std::string data_in;
    std::array<bool,Rules::NUM_TOGGLE_RULES> toggle_rules{};
    std::array<int,Rules::NUM_INT_RULES> int_rules{};
    
    infile.open("pref.cfg");
    int r = INITIAL_PHASE;
    
    while (true) {
        getline(infile, data_in);
        if (data_in[0] == '#') continue; // This is how I leave comments.
        
        // Lines in the config file either:
        // - contain a command-line phrase
        // designed to mark where certain pieces of the file begin and
        // end, for organizational purposes;
        // - specify the value for a toggleable rule;
        // - or specify the value for an integer-valued rule.
        
        switch (LINE_TYPES_IN_ORDER[r]) {
            case LineType::LINE_COMMAND: {
                read_command_phrase(PROMPTS[r], data_in, r);
                break;
            }
            case LineType::LINE_TOGGLE_RULE: {
                read_toggle_phase(PROMPTS[r], data_in, toggle_rules,
                                  RULES_IN_ORDER[r], r);
                break;
            }
            case LineType::LINE_INT_RULE: {
                read_int_phase(PROMPTS[r], data_in, int_rules,
                               RULES_IN_ORDER[r], r);
                break;
            }
        }
        if (r == EXIT_ERROR) {
            printout() << "Something has gone wrong.\n";
            break;
        }
        if (r == END_PHASE) break;
    }
    
    infile.close();
    
    Rules ru(std::move(toggle_rules), std::move(int_rules));
    
    return ru;
}

void read_command_phrase(const std::string& command_phrase,
                         const std::string& data_in,
                         int& r) {
    if (data_in == command_phrase) ++r;
    else r = EXIT_ERROR;
}

void read_toggle_phase(const std::string& phase_declare,
                       const std::string& data_in,
                       std::array<bool,Rules::NUM_TOGGLE_RULES>& rule_set,
                       const int& which_rule,
                       int& r) {
    if (data_in.substr(0, phase_declare.length()) == phase_declare) ++r;
    else r = EXIT_ERROR;
    if (data_in.substr(phase_declare.length() + 1) != "0"){
        rule_set[which_rule] = true;
    }
    // Look, I know it's not concise, but it's clearer, and it gets
    // optimized away by the compiler.
}

void read_int_phase(const std::string& phase_declare,
                    const std::string& data_in,
                    std::array<int,Rules::NUM_INT_RULES>& rule_set,
                    const int& which_rule,
                    int& r) {
    if (data_in.substr(0, phase_declare.length()) == phase_declare) ++r;
    else r = EXIT_ERROR;
    rule_set[which_rule] = data_in.substr(phase_declare.length() + 1)[0] - '0';
}

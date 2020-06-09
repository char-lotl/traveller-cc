#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "read_in_preferences.h"
#include "Rules.h"

enum class ReadPhase {
    INITIAL_PHASE,
    ASSIGN_METHOD_QUERY,
    REROLL_QUERY,
    YARBOROUGH_DETECTION,
    YARBOROUGH_REROLL_OVERRIDE,
    DEFAULT_ASSIGN_METHOD,
    END_PHASE,
    EXIT_ERROR
};

ReadPhase read_toggle_phase(std::string phase_declare_str,
                            std::string data_in_str,
                            std::vector<bool> &rule_set,
                            int which_rule,
                            ReadPhase next_phase);

Rules read_in_preferences() {
    std::ifstream infile;
    std::vector<std::string> data;
    std::string data_in;
    std::string phase_declare;
    infile.open("pref.cfg");
    ReadPhase r = ReadPhase::INITIAL_PHASE;
    std::shared_ptr<std::vector<bool> > toggle_rules_ptr(new std::vector<bool>(rule_type::TOGGLE_END, false));
    std::vector<bool> &toggle_rules = *toggle_rules_ptr;
    std::shared_ptr<std::vector<int> > int_rules_ptr(new
        std::vector<int>(rule_type::INT_END, 0));
    std::vector<int> &int_rules = *int_rules_ptr;
    
    while ((r != ReadPhase::END_PHASE) && (r != ReadPhase::EXIT_ERROR)) {
        getline(infile, data_in);
        if (data_in[0] == '#') continue; // This is how I leave comments.
        switch (r) {
            case ReadPhase::INITIAL_PHASE: {
                phase_declare = "BEGIN ASSIGNSCORES";
                if (data_in == phase_declare) r =
                    ReadPhase::ASSIGN_METHOD_QUERY;
                else r = ReadPhase::EXIT_ERROR;
                break;
            }
            case ReadPhase::ASSIGN_METHOD_QUERY: {
                r = read_toggle_phase("ASSIGN_METHOD_QUERY", data_in, toggle_rules,
                                      rule_type::ASSIGN_METHOD_QUERY,
                                      ReadPhase::REROLL_QUERY);
                break;
            }
            case ReadPhase::REROLL_QUERY: {
                r = read_toggle_phase("REROLL_QUERY", data_in, toggle_rules,
                                      rule_type::REROLL_QUERY,
                                      ReadPhase::YARBOROUGH_DETECTION);
                break;
            }
            case ReadPhase::YARBOROUGH_DETECTION: {
                r = read_toggle_phase("YARBOROUGH_DETECTION", data_in, toggle_rules,
                                      rule_type::YARBOROUGH_DETECTION,
                                      ReadPhase::YARBOROUGH_REROLL_OVERRIDE);
                break;
            }
            case ReadPhase::YARBOROUGH_REROLL_OVERRIDE: {
                r = read_toggle_phase("YARBOROUGH_REROLL_OVERRIDE", data_in,
                                      toggle_rules,
                                      rule_type::YARBOROUGH_REROLL_OVERRIDE,
                                      ReadPhase::DEFAULT_ASSIGN_METHOD);
                break;
            }
            case ReadPhase::DEFAULT_ASSIGN_METHOD: {
                phase_declare = "DEFAULT_ASSIGN_METHOD";
                if (data_in.substr(0, phase_declare.length()) != phase_declare) {
                    r = ReadPhase::EXIT_ERROR;
                    break;
                }
                if (data_in.substr(phase_declare.length() + 1) == "1"){
                    int_rules[rule_type::DEFAULT_ASSIGN_METHOD] =
                        score_input_method::MANUAL_ENTRY;
                } else if (data_in.substr(phase_declare.length() + 1) == "2"){
                    int_rules[rule_type::DEFAULT_ASSIGN_METHOD] =
                        score_input_method::POINT_BUY;
                }
                r = ReadPhase::END_PHASE;
                break;
            }
            case ReadPhase::END_PHASE: {
                break;
            }
            case ReadPhase::EXIT_ERROR: {
                std::cout << "Something has gone wrong." << std::endl;
            }
        }
    }
    
    infile.close();
    
    Rules ru(toggle_rules_ptr, int_rules_ptr);
    
    return ru;
}

ReadPhase read_toggle_phase(std::string phase_declare_str,
                            std::string data_in_str,
                            std::vector<bool> &rule_set,
                            int which_rule,
                            ReadPhase next_phase) {
    if (data_in_str.substr(0, phase_declare_str.length()) != phase_declare_str) {
        return ReadPhase::EXIT_ERROR;
    }
    if (data_in_str.substr(phase_declare_str.length() + 1) != "0"){
        rule_set[which_rule] = true;
    }
    // Look, I know it's not concise, but it's clearer, and it gets
    // optimized away by the compiler.
    return next_phase;
}

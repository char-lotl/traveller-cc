#include <list>
#include <string>
#include "skills/skill_type.h"
#include "utils/printing/printout.h"

#include "display_skill_cats_from_list.h"

using namespace utils::printing;

void display_skill_cats_from_list(const std::list<skill_type>& skill_list) {
    bool first = true;
    for (const skill_type& s : skill_list) {
        if (first) first = false;
        else printout() << ", ";
        printout() << skills::SK_STRINGS[s];
    }
    printout() << ".\n";
}

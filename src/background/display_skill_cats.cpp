#include <vector>
#include <string>
#include "skills/skill_type.h"
#include "utils/printing/printout.h"
#include "utils/printing/Formatter.h"

#include "display_skill_cats.h"

using namespace utils::printing;

void display_skill_cats(const std::vector<skill_type>& stypes) {
    std::vector<std::string> strv;
    for (const skill_type& s : stypes) {
        strv.push_back(skills::SK_STRINGS[s]);
    }
	printout() << CommaList(strv);
}

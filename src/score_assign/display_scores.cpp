#include <vector>
#include <string>
#include "utils/utils.h"
#include "display_scores.h"
#include "utils/printing/printout.h"
#include "utils/printing/Formatter.h"

using namespace utils::printing;

void display_scores_inline(const std::vector<int>& characteristic_scores) {
	std::vector<std::string> strv;
	for (int j = 0; j < 6; j++) {
        strv.push_back(utils::characteristic_abbrev[j]
					   + " is " + std::to_string(characteristic_scores[j]));
    }
	printout() << CommaList(strv);
}

void display_scores_vertical(const std::vector<int>& characteristic_scores) {
    for (int j = 0; j < 6; j++) {
        printout() << std::to_string(j + 1) << ". ";
        printout() << utils::characteristic_abbrev[j] << " is " <<
            characteristic_scores[j] << "\n";
    }
}

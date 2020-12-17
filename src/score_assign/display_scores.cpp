#include <array>
#include <string>
#include "utils/utils.h"
#include "display_scores.h"
#include "utils/printing/printout.h"

using namespace utils::printing;

void display_scores_inline(const std::array<int,6>& characteristic_scores) {
    bool first = true;
    for (int j = 0; j < 6; j++) {
        if (!first) printout() << ", ";
        printout() << utils::characteristic_abbrev[j] << " is " <<
            characteristic_scores[j];
        first = false;
    }
    printout() << ".\n";
}

void display_scores_vertical(const std::array<int,6>& characteristic_scores) {
    for (int j = 0; j < 6; j++) {
        printout() << std::to_string(j + 1) << ". ";
        printout() << utils::characteristic_abbrev[j] << " is " <<
            characteristic_scores[j] << "\n";
    }
}

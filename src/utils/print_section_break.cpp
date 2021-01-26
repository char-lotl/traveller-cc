#include "print_section_break.h"
#include "utils/printing/printout.h"
#include "utils/printing/Formatter.h"

using namespace utils::printing;

void utils::print_section_break() {
	printout() << std::string(CONSOLE_WIDTH, '-') << '\n';
}


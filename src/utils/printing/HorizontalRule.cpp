#include <string>
#include "Formatter.h"

using namespace utils::printing;

std::string const hrule_string = std::string(CONSOLE_WIDTH, '-') + '\n';

std::string HorizontalRule::get_formatted_string() const {
	return hrule_string;
}

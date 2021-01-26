#include <string>
#include <vector>
#include "Formatter.h"

using namespace utils::printing;

CommaList::CommaList(std::vector<std::string> const& v)
: StringSequentialFormatter(v) {}

std::string CommaList::get_formatted_string() const {
	bool first = true;
	std::string list_string;
	for (std::string const& s : string_contents) {
		if (first) first = false;
		else list_string += ", ";
		list_string += s;
	}
	list_string += ".\n";
	return list_string;
}

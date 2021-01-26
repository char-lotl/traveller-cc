#include <string>
#include <vector>
#include "Formatter.h"

using namespace utils::printing;

CommaList::CommaList(std::vector<std::string> const& v)
: StringSequentialFormatter(v), conjunction() {}

CommaList::CommaList(std::vector<std::string> const& v, std::string const& c)
: StringSequentialFormatter(v), conjunction(c) {}

std::string CommaList::get_formatted_string() const {
	bool first = true;
	std::string list_string;
	int num_contents = string_contents.size();
	for (int i = 0; i < num_contents; i++) {
		if (first) first = false;
		else list_string += ", ";
		
		if (i == num_contents - 1) list_string += conjunction + " ";
		
		list_string += string_contents[i];
	}
	list_string += ".\n";
	return list_string;
}

CommaListAnd::CommaListAnd(std::vector<std::string> const& v)
: CommaList(v, "and") {}

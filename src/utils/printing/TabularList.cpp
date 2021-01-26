#include <string>
#include <vector>
#include "Formatter.h"

using namespace utils::printing;

TabularList::TabularList(std::vector<std::string> const& v)
: StringSequentialFormatter(v) {}

std::string TabularList::get_formatted_string() const {
	int max_length = 0;
	int len = 0;
	int num_items = string_contents.size();
	for (const std::string& s : string_contents) {
		if ((len = s.length()) > max_length) max_length = len;
	}
	
	int num_cols = CONSOLE_WIDTH / (max_length + SPACER_WIDTH);
	if (num_cols > num_items) num_cols = num_items; // fill the space
	
	int col_width = CONSOLE_WIDTH / num_cols;
	
	int col = 0;
	std::string tabular_output;
	
	for (const std::string& s : string_contents) {
		tabular_output += s + std::string(col_width - s.length(), ' ');
		++col;
		if (col == num_cols) {
			tabular_output += "\n";
			col = 0;
		}
	}
	
	if (col != 0) tabular_output += '\n';
	
	return tabular_output;
}


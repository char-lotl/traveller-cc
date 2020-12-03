#include <vector>
#include <string>

#include "print_smart_list.h"
#include "utils/printing/printout.h"

using namespace utils::printing;

int const CONSOLE_WIDTH = 80;

void utils::print_smart_list(const std::vector<std::string>& string_list) {
	int max_length = 0;
	int len = 0;
	for (const std::string& s : string_list) {
		if ((len = s.length()) > max_length) max_length = len;
	}
	
	int num_cols = CONSOLE_WIDTH / (max_length + 2);
	int col_width = CONSOLE_WIDTH / num_cols;
	
	//int list_length = string_list.size();
	//int num_rows = list_length / num_cols;
	
	int i = 0;
	
	for (const std::string& s : string_list) {
		printout() << s << std::string(col_width - s.length(), ' ');
		++i;
		if (i == num_cols) {
			printout() << "\n";
			i = 0;
		}
	}
	
}

#include <vector>
#include <string>

#include "enumerate_list.h"

std::vector<std::string> utils::enumerate_list(std::vector<std::string> strl) {
	char e = 'a' - 1;
	for (std::string& s : strl) {
		s = std::string(1, ++e) + ". " + s;
	}
	return strl;
}

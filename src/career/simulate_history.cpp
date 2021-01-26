#include <vector>
#include <string>
class Repertoire;

#include "simulate_history.h"
#include "utils/reading/get_file_lines.h"
#include "utils/printing/printout.h"
#include "utils/printing/Formatter.h"
#include "utils/enumerate_list.h"
#include "utils/utils.h"

using namespace utils::printing;

int age_from_term(int const t);
int pick_career_from_list(std::vector<std::string> const& carlist);

void simulate_history(std::vector<int>& cscores, Repertoire& r) {
    
	printout() << HorizontalRule();
	
	int term = 0;

	printout() << "You are now " << age_from_term(term) << " years of age.\n";
	
    std::vector<std::string> career_types =
        utils::reading::get_file_lines("content/career/directory.cfg");
    
    std::vector<bool> have_left_career(career_types.size(), false);
    
	int chosen_career_ID = pick_career_from_list(career_types);
	
	
    // choose a career
    // use the choose from list utils function
    
}

int pick_career_from_list(std::vector<std::string> const& carlist) {
	std::vector<std::string> enumerated_careers =
		utils::enumerate_list(carlist);
	
	printout() << "You may select a career from among the following options:\n";
	
	printout() << TabularList(enumerated_careers);
	char resp_char = utils::get_char_response_in_range(
	    "Select a career from the above list: ",
		'a', 'a' + (carlist.size() - 1));
	
	int resp_car_ID = resp_char - 'a';
	return resp_car_ID;
}

int age_from_term(int const t) {
	return (t * 4) + 18;
}

//
//  main.cpp
//  Mongoose Traveller Command-Line Character Creator
//
//  Created by Charlotte on 6/6/20.
//

#include <array>

#include "skills/Repertoire.h"
#include "config/Rules.h"
#include "score_assign/assign_characteristic_scores.h"
#include "config/read_in_preferences.h"
#include "background/pick_background_skills.h"

int main() {
    
    Rules ru = read_in_preferences();
    
    std::array<int,6> characteristic_scores{};
    
    assign_characteristic_scores(characteristic_scores, ru);
    
    Repertoire rep;
    
    pick_background_skills(characteristic_scores, rep, ru);
    
}

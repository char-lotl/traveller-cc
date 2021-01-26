//
//  main.cpp
//  Mongoose Traveller Command-Line Character Creator
//
//  Created by Charlotte on 6/6/20.
//

#include <vector>

#include "skills/Repertoire.h"
#include "score_assign/assign_characteristic_scores.h"
#include "background/pick_background_skills.h"
#include "career/simulate_history.h"

int main() {
    
    std::vector<int> characteristic_scores(6, 0);
    
    assign_characteristic_scores(characteristic_scores);
    
    Repertoire rep;
    
    pick_background_skills(characteristic_scores, rep);
    
    simulate_history(characteristic_scores, rep);
    
}

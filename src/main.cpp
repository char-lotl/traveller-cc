//
//  main.cpp
//  Mongoose Traveller Command-Line Character Creator
//
//  Created by Charlotte Eastwood on 6/6/20.
//  Copyright © 2020 Charlotte Eastwood. All rights reserved.
//

#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include <vector>
//#include <list>

#include "Roller.h"
#include "Rules.h"
#include "assign_characteristic_scores.h"
#include "read_in_preferences.h"

using namespace std;

int main() {
    
    Rules ru = read_in_preferences();
    
    Roller r;
    vector<int> characteristic_scores(6, 0);
    
    assign_characteristic_scores(r, characteristic_scores, ru);
    
}

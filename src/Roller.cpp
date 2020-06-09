#include <iostream>
#include <random>
#include "Roller.h"

using namespace std;

Roller::Roller() : device(),
                   generator(device()),
                   //d2(1, 2), d4(1, 4),
                   d6(1, 6)
                   //d8(1, 8), d10(1, 10), d12(1, 12), d20(1, 20),
                   //bigDie(1, 1000000)
                   {
                       // nothing to do here
}

//int Roller::roll2(){ return d2(generator); }
//int Roller::roll4(){ return d4(generator); }
int Roller::roll6(){ return d6(generator); }
int Roller::roll2d6(){ return roll6() + roll6(); }
//int Roller::roll8(){ return d8(generator); }
//int Roller::roll10(){ return d10(generator); }
//int Roller::roll12(){ return d12(generator); }
//int Roller::roll20(){ return d20(generator); }

/*int Roller::rollAny(int dieSize){
    if (dieSize <= 0){
        cout << "Invalid die size: " << dieSize << "." << endl;
        return 0;
    }
    if (dieSize > 1000000){
        cout << "The die size of " << dieSize << " is too large!" << endl;
        return 1;
    }
    bool resultAcquired = false;
    int maxUsable = (1000000 / dieSize) * dieSize;
    int intermediateRoll;
    while (!resultAcquired){
        intermediateRoll = bigDie(generator);
        if (intermediateRoll <= maxUsable){
            resultAcquired = true;
            return (intermediateRoll - dieSize * ((intermediateRoll - 1) / dieSize));
        }
    }
    return 1;
}*/

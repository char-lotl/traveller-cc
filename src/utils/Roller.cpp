#include <random>
#include "Roller.h"

//using namespace std;

std::random_device Roller::device{}; // most vexing parse lmao
std::mt19937 Roller::generator(Roller::device());
std::uniform_int_distribution<int> Roller::d6(1, 6);

Roller::Roller() //: //device(),
                   //generator(device()),
                   //d2(1, 2), d4(1, 4),
                   //d6(1, 6)
                   //d8(1, 8), d10(1, 10), d12(1, 12), d20(1, 20),
                   //bigDie(1, 1000000)
                   {
                       // nothing to do here
}

//int Roller::roll2(){ return d2(generator); }
//int Roller::roll4(){ return d4(generator); }
int Roller::rolld6(){ return d6(generator); }
int Roller::roll2d6(){ return rolld6() + rolld6(); }
//int Roller::roll8(){ return d8(generator); }
//int Roller::roll10(){ return d10(generator); }
//int Roller::roll12(){ return d12(generator); }
//int Roller::roll20(){ return d20(generator); }

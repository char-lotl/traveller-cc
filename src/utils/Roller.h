#ifndef ROLLER_H
#define ROLLER_H

#include <random>

class Roller {
private:
    static std::random_device device;
    static std::mt19937 generator;
    //std::uniform_int_distribution<int> d2;
    //std::uniform_int_distribution<int> d4;
    static std::uniform_int_distribution<int> d6;
    //std::uniform_int_distribution<int> d8;
    //std::uniform_int_distribution<int> d10;
    //std::uniform_int_distribution<int> d12;
    //std::uniform_int_distribution<int> d20;
    //std::uniform_int_distribution<int> bigDie;
protected:
    Roller();
public:
    
    
    //int roll2();
    //int roll4();
    static int rolld6();
    static int roll2d6();
    //int roll8();
    //int roll10();
    //int roll12();
    //int roll20();
    //int rollAny(int dieSize);
};

#endif

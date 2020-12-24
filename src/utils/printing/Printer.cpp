#include <iostream>
#include <string>
#include "Printer.h"

/*
template <class T>
const utils::printing::Printer& utils::printing::Printer::operator<<(const T& x) const {
    std::cout << x;
    return (*this);
}*/

const utils::printing::Printer& utils::printing::Printer::operator<<(const std::string& s) const {
    std::cout << s;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const char& c) const {
    std::cout << c;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const int& i) const {
    std::cout << i;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const unsigned int& i) const {
    std::cout << i;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const long& i) const {
    std::cout << i;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const unsigned long& i) const {
    std::cout << i;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const long long& i) const {
    std::cout << i;
    return (*this);
}

const utils::printing::Printer& utils::printing::Printer::operator<<(const unsigned long long& i) const {
    std::cout << i;
    return (*this);
}

#include <iostream>
#include <string>
#include <vector>
#include "Printer.h"
#include "Formatter.h"

using namespace utils::printing;

/*
template <class T>
const Printer& Printer::operator<<(const T& x) const {
    std::cout << x;
    return (*this);
}*/

const Printer& Printer::operator<<(const std::string& s) const {
    std::cout << s;
    return (*this);
}

const Printer& Printer::operator<<(const char& c) const {
    std::cout << c;
    return (*this);
}

const Printer& Printer::operator<<(const int& i) const {
    std::cout << i;
    return (*this);
}

const Printer& Printer::operator<<(const unsigned int& i) const {
    std::cout << i;
    return (*this);
}

const Printer& Printer::operator<<(const long& i) const {
    std::cout << i;
    return (*this);
}

const Printer& Printer::operator<<(const unsigned long& i) const {
    std::cout << i;
    return (*this);
}

const Printer& Printer::operator<<(const long long& i) const {
    std::cout << i;
    return (*this);
}

const Printer& Printer::operator<<(const unsigned long long& i) const {
    std::cout << i;
    return (*this);
}

const Printer& Printer::operator<<(Formatter const& f) const {
	std::cout << f.get_formatted_string();
	return (*this);
}

#ifndef PRINTER_H
#define PRINTER_H

#include <string>

namespace utils {
namespace printing {
    class Printer {
    private:
        Printer() = default;
    public:
        const Printer& operator<<(const std::string& s) const;
        const Printer& operator<<(const char& c) const;
        const Printer& operator<<(const int& i) const;
        const Printer& operator<<(const unsigned int& i) const;
        const Printer& operator<<(const long& i) const;
        const Printer& operator<<(const unsigned long& i) const;
        const Printer& operator<<(const long long& i) const;
        const Printer& operator<<(const unsigned long long& i) const;
        friend const Printer& printout();
    };

    extern const std::string NUMBER_WORDS[11];

}
}

#endif


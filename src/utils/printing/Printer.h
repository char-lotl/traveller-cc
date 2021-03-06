#ifndef PRINTER_H
#define PRINTER_H

#include <string>

namespace utils {
namespace printing {
	
	class Formatter;
	
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
		const Printer& operator<<(Formatter const& f) const;
        friend const Printer& printout();
    };

}
}

#endif

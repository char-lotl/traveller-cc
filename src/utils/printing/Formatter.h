#ifndef FORMATTER_H
#define FORMATTER_H

#include "Printer.h"

namespace utils {
	namespace printing {
		
		int const CONSOLE_WIDTH = 80;
		int const SPACER_WIDTH = 2;
		
		class Formatter {
		private:
			friend Printer const& Printer::operator<<(Formatter const&) const;
		protected:
			virtual std::string get_formatted_string() const = 0;
		};
		
		// SequentialFormatter can be made into a template class, with
		// StringSequentialFormatter being an alias of SequentialFormatter<std::string>.
		// However, it's not yet clear that this will be necessary.
		class StringSequentialFormatter : public Formatter {
		protected:
			std::vector<std::string> const& string_contents;
		public:
			StringSequentialFormatter(std::vector<std::string> const& v) : string_contents(v) {}
		};
		
		class CommaList : public StringSequentialFormatter {
		public:
			CommaList(std::vector<std::string> const&);
		protected:
			std::string get_formatted_string() const override;
		};
		
		class TabularList : public StringSequentialFormatter {
		public:
			TabularList(std::vector<std::string> const&);
		protected:
			std::string get_formatted_string() const override;
		};
		
		
	}
}

#endif

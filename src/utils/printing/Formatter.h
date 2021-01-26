#ifndef FORMATTER_H
#define FORMATTER_H

#include "Printer.h"

namespace utils {
	namespace printing {
		
		int constexpr CONSOLE_WIDTH = 80;
		int constexpr SPACER_WIDTH = 2;
		
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
		private:
			std::string const conjunction;
		public:
			CommaList(std::vector<std::string> const&);
		protected:
			CommaList(std::vector<std::string> const&, std::string const& conjunction);
			std::string get_formatted_string() const override;
		};
		
		class CommaListAnd : public CommaList {
		public:
			CommaListAnd(std::vector<std::string> const&);
		};
		
		class TabularList : public StringSequentialFormatter {
		public:
			TabularList(std::vector<std::string> const&);
		protected:
			std::string get_formatted_string() const override;
		};
		
		class HorizontalRule : public Formatter {
		protected:
			std::string get_formatted_string() const override;
		};
		
	}
}

#endif

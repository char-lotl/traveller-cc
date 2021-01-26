#ifndef READER_H
#define READER_H

#include <fstream>

namespace utils {
namespace reading {
    class Reader {
    private:
        std::ifstream in_stream;
        Reader() = default;
        const std::vector<std::string> fread(const std::string& file_name);
    public:
        friend const std::vector<std::string> get_file_lines(const std::string& file_name);
    };
}
}

#endif

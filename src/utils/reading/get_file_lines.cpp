#include <vector>
#include <string>
#include "Reader.h"
#include "get_file_lines.h"

const std::vector<std::string> utils::reading::get_file_lines(const std::string& fn) {
    static utils::reading::Reader r{};
    return r.fread(fn);
}

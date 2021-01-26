#include <fstream>
#include <string>
#include <vector>
#include "Reader.h"

const std::vector<std::string> utils::reading::Reader::fread(const std::string& fn) {
    in_stream.open(fn);
    std::string s;
    std::vector<std::string> v;
    while (!in_stream.eof()) {
        std::getline(in_stream, s);
        if (s[0] != '#') v.push_back(s);
    }
    in_stream.close();
    return v;
}

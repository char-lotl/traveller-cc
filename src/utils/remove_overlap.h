#ifndef REMOVE_OVERLAP_H
#define REMOVE_OVERLAP_H

#include <iterator>

template<class T>
void remove_overlap(std::list<T>& a, const std::list<T>& b) {
    auto i = a.begin();
    auto j = b.begin();
    auto k = i;
    
    while (i != a.end() && j != b.end()) {
        if (*i < *j) { std::advance(i, 1); continue; }
        if (*i == *j) {
            k = i;
            std::advance(i, 1);
            a.erase(k);
            continue;
        }
        if (*i > *j) { std::advance(j, 1); continue; }
    }
}

#endif

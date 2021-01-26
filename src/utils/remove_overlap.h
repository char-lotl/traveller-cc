#ifndef REMOVE_OVERLAP_H
#define REMOVE_OVERLAP_H

#include <iterator>

template<class T>
void remove_overlap(std::vector<T>& a, const std::vector<T>& b) {
	auto i = a.begin();
	auto j = b.begin();
	std::vector<T> c;
    
    while (i != a.end() && j != b.end()) {
		if (*i < *j) { c.push_back(*i); std::advance(i, 1); continue; }
        if (*i == *j) { std::advance(i, 1); continue; }
        if (*i > *j) { std::advance(j, 1); continue; }
    }
	
	c.insert(c.end(), i, a.end()); // grab anything else in vector a
	
	a = std::move(c);
}

#endif

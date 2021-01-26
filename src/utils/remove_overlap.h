#ifndef REMOVE_OVERLAP_H
#define REMOVE_OVERLAP_H

#include <iterator>

template<class T>
void remove_overlap(std::vector<T>& a, const std::vector<T>& b) {
	unsigned int i = 0, j = 0;
	unsigned int lena = a.size(), lenb = b.size();
	std::vector<T> c;
    
    while (i < lena && j < lenb) {
		if (a[i] < b[j]) { c.push_back(a[i++]); continue; }
        if (a[i] == b[j]) { ++i; continue; }
        if (a[i] > b[j]) { ++j; continue; }
    }
	
	a = std::move(c);
}

#endif

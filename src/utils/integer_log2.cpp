#include "integer_log2.h"

int utils::integer_log2(int x) {
    int i = 0;
    while (x > 1) {
        x >>= 1;
        ++i;
    }
    return i;
}

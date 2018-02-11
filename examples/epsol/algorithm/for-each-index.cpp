#include "epsol/algorithm/extend/for-each-index.h"
#include <list>
#include <cstdio>

using namespace epsol::algorithm;

int main() {
    std::list<int> l{10, 9, 8, 7, 6};
    for_each_index(begin(l), end(l), [](int i, int val) {
        std::printf("index: %d, value: %d\n", i, val);
    });
}
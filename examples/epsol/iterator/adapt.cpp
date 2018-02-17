#include "epsol/iterator/adaptor.h"
#include <iostream>
#include <vector>

using namespace epsol::iterator;
using std::vector;

int main() {
    vector<int> v{1, 2, 3, 4, 5};
    for (auto e : adapt_forward(begin(v), end(v))) {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    for (auto b = adapt_forward(begin(v), end(v)); b != end(b); ++b) {
        *b = 100;
    }

    for (auto e : adapt_forward_iterable(v)) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}
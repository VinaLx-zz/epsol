#include "epsol/range.h"
#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int main() {
    vector<int> v{5, 4, 3, 2, 1};

    std::sort(RANGE(v));
    FOR_EACH(e, v) std::cout << e << '\n'; // 1 2 3 4 5

    std::sort(RANGE_R(v));
    FOR_EACH(e, v) std::cout << e << '\n'; // 5 4 3 2 1
}
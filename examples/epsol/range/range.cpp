// API imagination, uncomment when complete

#include "epsol/range.h"
#include <iostream>


using namespace epsol::range;
using std::cout;

int main() {
    for (auto i : from(1).to(5)) {
        cout << i << ' '; // 1 2 3 4 5
    }
    cout << '\n';

    // for (auto i : range::from(1).to(5).filter([](int i) { return i % 2; })) {
    //     cout << i << ' '; // 1 3 5
    // }
    // cout << '\n';
    for (auto i : from(1).step([](int i) { return i + 3; }).to(10)) {
        cout << i << ' '; // 1 4 7 10
    }
    cout << '\n';
    for (auto i : from(1).when([](int i) { return i < 5; })) {
        cout << i << ' '; // 1 2 3 4
    }
    cout << '\n';
    // infinite range
    // for (auto i : from(1)) {
    //     cout << i << ' '; // 1 2 3 4 ..
    // }
}
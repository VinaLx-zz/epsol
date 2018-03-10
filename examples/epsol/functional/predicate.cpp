#include "epsol/functional/predicate.h"
#include <iostream>

using namespace epsol::functional::predicate;
using epsol::functional::Predicate;

int main() {
    Predicate<int> p1 = [](int i) {
        std::cout << "p1 testing " << i << '\n';
        return i == 1;
    };
    Predicate<int> p2 = [](int i) {
        std::cout << "p2 testing " << i << '\n';
        return i == 2;
    };
    Predicate<int> p3 = [](int i) {
        std::cout << "p3 testing " << i << '\n';
        return i == 3;
    };
    Predicate<int> p4 = p1 or p2 or p3, p5 = p1 and p2 and p3;

    std::cout << std::boolalpha;
    std::cout << p4(2) << '\n' << p4(3) << '\n' << p5(1) << '\n';
}
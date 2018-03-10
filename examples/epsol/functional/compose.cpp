#include "epsol/functional.h"
#include <functional>
#include <iostream>
#include <string>

using epsol::functional::operator>>;

int main() {
    std::function<std::string(int)> f = [](int i) { return std::to_string(i); };
    std::function<void(int)> g = f >> [](const std::string &s) {
        return s.size();
    } >> [](int i) { std::cout << "the number has " << i << " digits\n"; };

    g(1234567);
}
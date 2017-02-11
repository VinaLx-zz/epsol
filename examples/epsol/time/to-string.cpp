#include <chrono>
#include <iostream>
#include "epsol/time.h"

using epsol::time::operator<<;
using epsol::time::to_string;
using namespace std::chrono;

int main(int argc, char** argv) {
    std::cout << to_string(42ns) << " = " << 42ns << '\n'
              << to_string(42us) << " = " << 42us << '\n'
              << to_string(42ms) << " = " << 42ms << '\n'
              << to_string(42s) << " = " << 42s << '\n'
              << to_string(42min) << " = " << 42min << '\n'
              << to_string(42h) << " = " << 42h << '\n';
}

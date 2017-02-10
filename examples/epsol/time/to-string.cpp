#include <chrono>
#include <iostream>
#include "epsol/time.h"

using namespace epsol;
using namespace std::chrono;

int main(int argc, char** argv) {
    std::cout << "42 nanoseconds is " << 42ns << '\n'
              << "42 microseconds is " << 42us << '\n'
              << "42 milliseconds is " << 42ms << '\n'
              << "42 seconds is " << 42s << '\n'
              << "42 minutes is " << 42min << '\n'
              << "42 hours is " << 42h << '\n';
}

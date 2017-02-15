#include <cctype>
#include <iostream>
#include <string>
#include "epsol/string.h"

int main(int argc, char** argv) {
    std::string s;

    for (; std::getline(std::cin, s);)
        std::cout << '\"' << s << '\"' << " with spaces stripped is \""
                  << epsol::string::strip(s) << "\"\n";
}

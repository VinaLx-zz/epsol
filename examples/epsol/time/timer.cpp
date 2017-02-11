#include <iostream>
#include "epsol/time.h"

using namespace epsol::time;
using epsol::operator<<;
using std::cout;

void DummyFunction(const std::string& s) {
    int a = 0;
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < s.size(); ++j) {
            a += s[j];
        }
    }
    cout << "Dummy Function say: " << a << '\n';
}

int main(int argc, char** argv) {
    auto time_in_milli = time(DummyFunction, "Some Parameter");
    cout << "DummyFunction takes " << time_in_milli << " to finish\n";

    auto time_in_sec = time<std::chrono::seconds>([]() {
        for (int i = 0; i >= 0; ++i)
            continue;
    });
    cout << "The lambda takes " << time_in_sec << " to finish\n";
}

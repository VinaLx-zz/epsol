#include <iostream>
#include "epsol/time.h"

using namespace epsol;

// year/month/day/hour/minute/second
using namespace epsol::time::tags;

using std::cout;

int main(int argc, char** argv) {
    // or simply time::now();
    auto tp = time::now<std::chrono::system_clock>();
    cout << "Current time:\n"
         << "year: " << time::extract_year(tp)
         << "\nmonth: " << time::extract_month(tp)
         << "\nday: " << time::extract_day(tp)
         << "\nhour: " << time::extract_hour(tp)
         << "\nminute: " << time::extract_minute(tp)
         << "\nsecond: " << time::extract_second(tp) << '\n';

    auto time_tup = time::extract<year, month, day, hour, minute, second>(tp);
    cout << "year from tuple: " << std::get<0>(time_tup)
         << "\nmonth from tuple: " << std::get<1>(time_tup)
         << "\nday from tuple: " << std::get<2>(time_tup)
         << "\nhour from tuple: " << std::get<3>(time_tup)
         << "\nminute from tuple: " << std::get<4>(time_tup)
         << "\nsecond from tuple: " << std::get<5>(time_tup) << '\n';
}

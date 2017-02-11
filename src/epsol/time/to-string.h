#ifndef EPSOL_TIME_TO_STRING_
#define EPSOL_TIME_TO_STRING_

#include <chrono>
#include <iostream>
#include <string>

namespace epsol {
namespace time {

/**
 * bunch of convenient overloads converting time to string
 */
#define DEF_TIME_TO_STRING(time, unit)                                       \
    inline std::string to_string(std::chrono::time t) {                      \
        return std::to_string(t.count()) + #unit;                            \
    }                                                                        \
    inline std::ostream& operator<<(std::ostream& os, std::chrono::time t) { \
        return os << to_string(t);                                           \
    }

DEF_TIME_TO_STRING(nanoseconds, ns)
DEF_TIME_TO_STRING(microseconds, us)
DEF_TIME_TO_STRING(milliseconds, ms)
DEF_TIME_TO_STRING(seconds, s)
DEF_TIME_TO_STRING(minutes, min)
DEF_TIME_TO_STRING(hours, h)

#undef DEF_TIME_TO_STRING

}  // namespace time
}  // namespace epsol

#endif  // EPSOL_TIME_TO_STRING_

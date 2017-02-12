#ifndef EPSOL_TIME_TIME_ZONE_
#define EPSOL_TIME_TIME_ZONE_

#include <cassert>
#include <chrono>
#include <ctime>

namespace epsol {
namespace time {

/**
 * synonym for std::long::namespaces::now()
 */
template <typename Clock = std::chrono::system_clock>
typename Clock::time_point now() {
    return Clock::now();
}

enum class TimeZone { GMT, LOCAL };

template <typename TimePoint>
std::tm to_tm(TimePoint tp, TimeZone tz = TimeZone::LOCAL) {
    return *to_tm_ptr(tp, tz);
}

template <typename TimePoint>
std::tm* to_tm_ptr(TimePoint tp, TimeZone tz = TimeZone::LOCAL) {
    auto the_time = TimePoint::clock::to_time_t(tp);
    if (tz == TimeZone::LOCAL) {
        return std::localtime(&the_time);
    } else if (tz == TimeZone::GMT) {
        return std::gmtime(&the_time);
    }

    // the code can't reach here
    assert(false);
}

}  // namespace time
}  // namespace epsol

#endif  // EPSOL_TIME_TIME_ZONE_

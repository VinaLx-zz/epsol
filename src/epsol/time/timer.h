#ifndef EPSOL_TIME_TIMER_H_
#define EPSOL_TIME_TIMER_H_

#include <chrono>

namespace epsol {
namespace time {

/**
 * times a function, returns the running time of the funcion and simply ignore
 * its return value, since c++ provides no effective way to extract the return
 * type from a function(which is possibly a lambda). So the return value may be
 * obtained by a `output parameter`.
 *
 * examples see examples/epsol/time/timer.cpp
 */
template <
    typename Duration = std::chrono::milliseconds, typename Func,
    typename... Args>
Duration time(Func&& f, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    f(std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<Duration>(end - start);
}

}  // namespace time
}  // namespace epsol
#endif

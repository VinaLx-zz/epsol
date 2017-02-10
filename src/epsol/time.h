#include <chrono>
#include <string>
#include <utility>

namespace epsol {

/**
 * bunch of convenient overloads converting time to string
 */
#define DECL_TO_STRING(time, unit)                                           \
    inline std::string to_string(std::chrono::time t) {                      \
        return std::to_string(t.count()) + #unit;                            \
    }                                                                        \
    inline std::ostream& operator<<(std::ostream& os, std::chrono::time t) { \
        return os << to_string(t);                                           \
    }

DECL_TO_STRING(nanoseconds, ns)
DECL_TO_STRING(microseconds, us)
DECL_TO_STRING(milliseconds, ms)
DECL_TO_STRING(seconds, s)
DECL_TO_STRING(minutes, min)
DECL_TO_STRING(hours, h)

#undef DECL_TO_STRING

/**
 * time a function, return the running time of the funcion and simply ignore
 * its return value, since c++ provides no effective way to extract the return
 * type of a function(which is possibly a lambda). So the return value may be
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

}  // namespace epsol

#ifndef EPSOL_FUNCTIONAL_PREDICATE_
#define EPSOL_FUNCTIONAL_PREDICATE_

#include <functional>

namespace epsol::functional {

template <typename... Args>
using Predicate = std::function<bool(Args...)>;

namespace predicate {

template <typename... Args>
Predicate<Args...> operator||(Predicate<Args...> p1, Predicate<Args...> p2) {
    return [ p1 = std::move(p1), p2 = std::move(p2) ](Args... args)->bool {
        return p1(args...) or p2(args...);
    };
}

template <typename... Args>
Predicate<Args...> operator&&(Predicate<Args...> p1, Predicate<Args...> p2) {
    return [ p1 = std::move(p1), p2 = std::move(p2) ](Args... args)->bool {
        return p1(args...) and p2(args...);
    };
}

} // namespace predicate

} // namespace epsol::functional

#endif // EPSOL_FUNCTIONAL_PREDICATE_
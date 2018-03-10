#ifndef EPSOL_FUNCTIONAL_PREDICATE_
#define EPSOL_FUNCTIONAL_PREDICATE_

#include <functional>

namespace epsol::functional {

template <typename... Args>
using Predicate = std::function<bool(Args...)>;

namespace predicate {

namespace detail {
template <typename T>
struct is_predicate : std::false_type {};

template <typename... Args>
struct is_predicate<Predicate<Args...>> : std::true_type {};

} // namespace detail

template <
    typename... Args, typename F,
    typename = std::enable_if_t<std::is_convertible_v<F, Predicate<Args...>>>>
Predicate<Args...> operator||(Predicate<Args...> p1, F p2) {
    return [ p1 = std::move(p1), p2 = std::move(p2) ](Args... args)->bool {
        return p1(args...) or p2(args...);
    };
}

template <
    typename... Args, typename F,
    typename = std::enable_if_t<
        not detail::is_predicate<F>::value and
        std::is_convertible_v<F, Predicate<Args...>>>>
Predicate<Args...> operator||(F p1, Predicate<Args...> p2) {
    return [ p1 = std::move(p1), p2 = std::move(p2) ](Args... args)->bool {
        return p1(args...) or p2(args...);
    };
}

template <
    typename... Args, typename F,
    typename = std::enable_if_t<std::is_convertible_v<F, Predicate<Args...>>>>
Predicate<Args...> operator&&(Predicate<Args...> p1, F p2) {
    return [ p1 = std::move(p1), p2 = std::move(p2) ](Args... args)->bool {
        return p1(args...) and p2(args...);
    };
}

template <
    typename... Args, typename F,
    typename = std::enable_if_t<
        not detail::is_predicate<F>::value and
        std::is_convertible_v<F, Predicate<Args...>>>>
Predicate<Args...> operator&&(F p1, Predicate<Args...> p2) {
    return [ p1 = std::move(p1), p2 = std::move(p2) ](Args... args)->bool {
        return p1(args...) and p2(args...);
    };
}

} // namespace predicate

} // namespace epsol::functional

#endif // EPSOL_FUNCTIONAL_PREDICATE_
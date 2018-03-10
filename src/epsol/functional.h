#ifndef EPSOL_FUNCTIONAL_
#define EPSOL_FUNCTIONAL_

#include "epsol/functional/predicate.h"
#include <functional>

namespace epsol::functional {

template <typename... Args>
std::function<void(Args...)> noop() {
    return [](Args...) {};
}

// naming should be 'const', but which is obviously a keyword
template <typename... Args, typename T>
std::function<T(Args...)> always(T t) {
    return [t = std::move(t)](Args...)->T {
        return t;
    };
}

template <
    typename... Args, typename R, typename F,
    typename R2 = std::result_of_t<F(R)>>
std::function<R2(Args...)> compose(F g, std::function<R(Args...)> f) {
    return [ f = std::move(f), g = std::move(g) ](Args... args)->R2 {
        return g(f(args...));
    };
}

/**
 * composition
 */
template <
    typename... Args, typename R, typename F,
    typename R2 = std::result_of_t<F(R)>>
std::function<R2(Args...)> operator>>(std::function<R(Args...)> f, F g) {
    return compose(std::move(g), std::move(f));
}

} // namespace epsol::functional

#endif // EPSOL_FUNCTIONAL_
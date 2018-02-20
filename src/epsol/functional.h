#ifndef EPSOL_FUNCTIONAL_
#define EPSOL_FUNCTIONAL_

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

} // namespace epsol::functional

#endif // EPSOL_FUNCTIONAL_
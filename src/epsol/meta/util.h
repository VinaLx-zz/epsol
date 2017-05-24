#ifndef EPSOL_META_UTIL_
#define EPSOL_META_UTIL_

#include <type_traits>

namespace epsol::meta {

template <typename T>
constexpr bool less(T lhs, T rhs) {
    return lhs < rhs;
}

template <typename T>
constexpr bool greater(T lhs, T rhs) {
    return lhs > rhs;
}

template <typename T>
struct identity {
    using type = T;
};

template <typename T, template <typename...> class Temp>
struct is_template : std::false_type {};

template <typename... Ts, template <typename...> class Temp>
struct is_template<Temp<Ts...>, Temp> : std::true_type {};

template <typename... Ts>
using void_t = void;

}  // namespace epsol::meta

#endif  // EPSOL_META_UTIL_

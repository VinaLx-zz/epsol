#ifndef EPSOL_META_UTIL_COMPARE_
#define EPSOL_META_UTIL_COMPARE_

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
constexpr bool less_equal(T lhs, T rhs) {
    return lhs <= rhs;
}

template <typename T>
constexpr bool greater_equal(T lhs, T rhs) {
    return lhs >= rhs;
}

}  // namespace epsol::meta

#endif  // EPSOL_META_UTIL_COMPARE_

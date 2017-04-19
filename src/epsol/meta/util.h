#ifndef EPSOL_META_UTIL_
#define EPSOL_META_UTIL_

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

}  // namespace epsol::meta

#endif // EPSOL_META_UTIL_

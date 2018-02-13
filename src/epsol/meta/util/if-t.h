#ifndef EPSOL_META_UTIL_IF_T_
#define EPSOL_META_UTIL_IF_T_

namespace epsol::meta {

template <bool b, typename T, typename F>
struct if_ {
    using type = T;
};

template <typename T, typename F>
struct if_<false, T, F> {
    using type = F;
};

template <bool b, typename T, typename F>
using if_t = typename if_<b, T, F>::type;

} // namespace epsol::meta

#endif // EPSOL_META_UTIL_IF_T_
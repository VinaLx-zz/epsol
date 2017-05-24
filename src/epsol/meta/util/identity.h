#ifndef EPSOL_META_UTIL_IDENTITY_
#define EPSOL_META_UTIL_IDENTITY_

namespace epsol::meta {

template <typename T>
struct identity {
    using type = T;
};

template <typename T>
using identity_t = typename identity<T>::type;

}  // namespace epsol::meta

#endif  // EPSOL_META_UTIL_IDENTITY_

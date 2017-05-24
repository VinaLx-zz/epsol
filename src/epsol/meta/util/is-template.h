#ifndef EPSOL_META_UTIL_IS_TEMPLATE_
#define EPSOL_META_UTIL_IS_TEMPLATE_

#include <type_traits>

namespace epsol::meta {

template <typename T, template <typename...> class Temp>
struct is_template : std::false_type {};

template <typename... Ts, template <typename...> class Temp>
struct is_template<Temp<Ts...>, Temp> : std::true_type {};

}

#endif // EPSOL_META_UTIL_IS_TEMPLATE_

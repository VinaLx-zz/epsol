#include "epsol/meta/util.h"

using epsol::meta::is_template;

template <typename A, typename B, typename C>
class Temp {};

template <typename A>
class Temp2 {};

int main() {
    static_assert(is_template<Temp<int, double, char>, Temp>::value);
    static_assert(not is_template<Temp<int, double, char>, Temp2>::value);
    static_assert(is_template<Temp2<int>, Temp2>::value);
}

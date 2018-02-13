#ifndef EPSOL_ITERATOR_BASIC_TRAITS_
#define EPSOL_ITERATOR_BASIC_TRAITS_

#include "epsol/meta/type-list.h"
#include "epsol/meta/util/if-t.h"
#include <cstdint>
#include <iterator>
#include <type_traits>

namespace epsol::iterator {

template <bool Readonly, typename T, typename IterTag>
struct iterator_basic_traits {

    static_assert(
        epsol::meta::find<
            epsol::meta::type_list<
                std::input_iterator_tag, std::output_iterator_tag,
                std::forward_iterator_tag, std::bidirectional_iterator_tag,
                std::random_access_iterator_tag>,
            IterTag>::value,
        "invalid iterator tag");

    using value_type = std::remove_cv_t<T>;
    using pointer = epsol::meta::if_t<Readonly, const T*, T*>;
    using reference = epsol::meta::if_t<Readonly, const T&, T&>;
    using difference_type = int64_t;
    using iterator_category = IterTag;
};

} // namespace epsol::iterator

#endif // EPSOL_ITERATOR_BASIC_TRAITS_
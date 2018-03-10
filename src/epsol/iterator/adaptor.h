#ifndef EPSOL_ITERATOR_ADAPTOR_
#define EPSOL_ITERATOR_ADAPTOR_

#include "./general.h"
#include "epsol/meta/type-list.h"
#include "epsol/meta/util/if-t.h"
#include "epsol/meta/util/is-iterator.h"
#include <iterator>

namespace epsol::iterator {

template <typename Iter, typename EndIter>
auto adapt_forward(Iter b, EndIter e) {
    static_assert(epsol::meta::is_iterator_v<Iter>);
    constexpr bool Readonly = epsol::meta::is_const_iterator_v<Iter>;
    using Tp = typename std::iterator_traits<Iter>::value_type;
    using IterTag = typename std::iterator_traits<Iter>::iterator_category;
    using Tag = typename meta::if_t<
        meta::find<
            meta::type_list<
                std::input_iterator_tag, std::forward_iterator_tag,
                std::output_iterator_tag>,
            IterTag>::value,
        IterTag, std::forward_iterator_tag>;

    using Result = forward_iterator<Readonly, Tp, Iter, Tag>;

    return Result(
        b, [](const Iter &iter) -> typename Result::reference { return *iter; },
        [](Iter iter) -> Iter { return ++iter; },
        functional::always<const Iter &>(false),
        [e](const Iter &next) { return next == e; },
        functional::always<const Tp &>(true));
}

template <typename Iterable>
auto adapt_forward_iterable(Iterable &iter) {
    return adapt_forward(begin(iter), end(iter));
}

template <typename Iter>
class adaptor
    : public forward_iterator<
          true, typename std::iterator_traits<Iter>::value_type, Iter> {};

} // namespace epsol::iterator

#endif // EPSOL_ITERATOR_ADAPTOR_
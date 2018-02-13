#ifndef EPSOL_RANGE_ITERATOR_
#define EPSOL_RANGE_ITERATOR_

#include "epsol/iterator/basic-traits.h"
#include "epsol/iterator/general.h"
#include <functional>

namespace epsol::range {

template <typename T>
class iterator : public epsol::iterator::forward_iterator<true, T, T> {
  private:
    using super_type = epsol::iterator::forward_iterator<true, T, T>;

  public:
    iterator(
        const T &init, typename super_type::incrementor inc,
        typename super_type::terminator term)
        : super_type(
              init, [](const T &t) -> const T & { return t; }, inc, term){};
};

} // namespace epsol::range

#endif // EPSOL_RANGE_ITERATOR_
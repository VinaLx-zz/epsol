#ifndef EPSOL_ALGORITHM_EXTEND_FOR_EACH_INDEX
#define EPSOL_ALGORITHM_EXTEND_FOR_EACH_INDEX

#include <cstddef>

namespace epsol::algorithm {

/**
 * index version of std::for_each
 */
template <typename Iter, typename Func>
void for_each_index(Iter first, Iter last, Func f) {
    for (size_t i = 0; first != last; ++first, ++i)
        f(i, *first);
}

/**
 * index version of std::for_each_n
 */
template <typename Size, typename Iter, typename Func>
void for_each_n_index(Iter first, Size n, Func f) {
    for (Size i = 0; i < n; ++first, ++i)
        f(i, *first);
}

} // namespace epsol::algorithm

#endif // EPSOL_ALGORITHM_EXTEND_FOR_EACH_INDEX
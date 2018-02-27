#ifndef EPSOL_RANGE_RANGE_
#define EPSOL_RANGE_RANGE_

#include "./iterator.h"
#include "epsol/iterator/general.h"
#include <functional>
#include <type_traits>

namespace epsol::range {

template <typename T, bool DefaultIncrement>
class range {
  public:
    range(const T &start) : start_(start){};

    using incrementor_t = typename iterator<T>::incrementor;
    using terminator_t = typename iterator<T>::terminator;
    using filter_t = typename iterator<T>::filter;

    range(
        const T &start, incrementor_t inc, terminator_t term_now,
        terminator_t term_next, filter_t p)
        : start_(start), incrementor_(std::move(inc)),
          term_now_(std::move(term_now)), term_next_(std::move(term_next)),
          filter_(std::move(p)) {}

    iterator<T> begin() const {
        if constexpr (DefaultIncrement) {
            return iterator<T>(
                start_, [](T t) -> T { return ++t; }, term_now_, term_next_,
                filter_);
        }
        return iterator<T>(
            start_, incrementor_, term_now_, term_next_, filter_);
    }
    epsol::iterator::iter_end_t end() const {
        return epsol::iterator::iter_end_t{};
    }

    range<T, DefaultIncrement> to(const T &e) {
        using namespace epsol::functional::predicate;
        return range<T, DefaultIncrement>(
            start_, incrementor_,
            terminator_t([e](const T &now) { return now == e; }) or term_now_,
            term_next_, filter_);
    }

    range<T, DefaultIncrement> until(const T &e) {
        using namespace epsol::functional::predicate;
        return range<T, DefaultIncrement>(
            start_, incrementor_, term_now_,
            terminator_t([e](const T &next) { return next == e; }) or
                term_next_,
            filter_);
    }

    template <typename Func>
    range<T, DefaultIncrement> when(Func f) {
        using namespace epsol::functional::predicate;
        return range<T, DefaultIncrement>(
            start_, incrementor_, term_now_,
            terminator_t([f = std::move(f)](const T &next) {
                return not f(next);
            }) or
                term_next_,
            filter_);
    }

    range<T, DefaultIncrement> filter(filter_t f) {
        using namespace epsol::functional::predicate;
        return range<T, DefaultIncrement>(
            start_, incrementor_, term_now_, term_next_, f and filter_);
    }

    template <typename P>
    range<T, false> step(P p) {
        if constexpr (std::is_convertible<P, incrementor_t>::value) {
            return range<T, false>(
                start_, make_incrementor(std::move(p)), term_now_, term_next_,
                filter_);
        } else {
            return range<T, false>(
                start_, make_incrementor([p = std::move(p)](const T &t)->T {
                    return t + p;
                }),
                term_now_, term_next_, filter_);
        }
    }

  private:
    incrementor_t make_incrementor(incrementor_t new_inc) {
        if constexpr (DefaultIncrement) {
            return new_inc;
        }
        return [ old = this->incrementor_, new_inc ](const T &t) {
            return new_inc(old(t));
        };
    }

    T start_;
    incrementor_t incrementor_;
    filter_t filter_ = functional::always<const T &>(true);
    terminator_t term_now_ = functional::always<const T &>(false),
                 term_next_ = functional::always<const T &>(false);
};

template <typename T>
range<T, true> from(const T &start) {
    return range<T, true>(start);
}

} // namespace epsol::range

#endif // EPSOL_RANGE_RANGE_

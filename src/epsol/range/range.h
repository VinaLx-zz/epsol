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
    range(const T &start)
        : start_(start),
          terminator_([](const T &_1, const T &_2) { return false; }) {}

    using incrementor = typename iterator<T>::incrementor;
    using terminator = typename iterator<T>::terminator;

    range(const T &start, incrementor inc, terminator term)
        : start_(start), incrementor_(std::move(inc)),
          terminator_(std::move(term)) {}

    iterator<T> begin() const {
        if constexpr (DefaultIncrement) {
            return iterator<T>(
                start_,
                [](const T &t) {
                    T tt(t);
                    return ++tt;
                },
                terminator_);
        }
        return iterator<T>(start_, incrementor_, terminator_);
    }
    epsol::iterator::iter_end_t end() const {
        return epsol::iterator::iter_end_t{};
    }

    range<T, DefaultIncrement> to(const T &e) {
        return range<T, DefaultIncrement>(
            start_, incrementor_,
            make_terminator(
                [e](const T &now, const T &_) { return now == e; }));
    }

    range<T, DefaultIncrement> until(const T &e) {
        return range<T, DefaultIncrement>(
            start_, incrementor_,
            make_terminator(
                [e](const T &_, const T &next) { return next == e; }));
    }

    template <typename Func>
    range<T, DefaultIncrement> when(Func f) {
        return range<T, DefaultIncrement>(
            start_, incrementor_,
            make_terminator([f = std::move(f)](const T &_, const T &next) {
                return not f(next);
            }));
    }

    template <typename P>
    range<T, false> step(P p) {
        if constexpr (std::is_convertible<P, incrementor>::value) {
            return range<T, false>(
                start_, make_incrementor(std::move(p)), terminator_);
        } else {
            return range<T, false>(
                start_, make_incrementor([p = std::move(p)](const T &t)->T {
                    return t + p;
                }),
                terminator_);
        }
    }

  private:
    terminator make_terminator(terminator new_term) {
        return
            [ old = this->terminator_, new_term ](const T &now, const T &next) {
            return new_term(now, next) or old(now, next);
        };
    }
    incrementor make_incrementor(incrementor new_inc) {
        if constexpr (DefaultIncrement) {
            return new_inc;
        }
        return [ old = this->incrementor_, new_inc ](const T &t) {
            return new_inc(old(t));
        };
    }

    T start_;
    typename iterator<T>::incrementor incrementor_;
    typename iterator<T>::terminator terminator_;
};

template <typename T>
range<T, true> from(const T &start) {
    return range<T, true>(start);
}

} // namespace epsol::range

#endif // EPSOL_RANGE_RANGE_

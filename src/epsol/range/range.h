#ifndef EPSOL_RANGE_RANGE_
#define EPSOL_RANGE_RANGE_

#include "./iterator.h"
#include "epsol/iterator/general.h"
#include <functional>

namespace epsol::range {

template <typename T>
class range {
  public:
    range(const T &start)
        : start_(start), terminator_([](const T &t) { return false; }) {}

    iterator<T> begin() const {
        if (not incrementor_) {
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

    range<T> to(const T &e) {
        add_terminator([e](const T &t) { return t == e; });
        return *this;
    }
    template <typename Func>
    range<T> when(Func f) {
        add_terminator([f](const T &t) { return not f(t); });
        return *this;
    }

    template <typename Func>
    range<T> step(Func f) {
        add_incrementor(f);
        return *this;
    }

  private:
    void add_terminator(typename iterator<T>::terminator new_term) {
        auto old = terminator_;
        terminator_ = [ old, new_term ](const T &t) {
            return new_term(t) or old(t);
        };
    }
    void add_incrementor(typename iterator<T>::incrementor new_inc) {
        if (not incrementor_) {
            incrementor_ = [](const T &t) { return t; };
        }
        incrementor_ = [ old = this->incrementor_, new_inc ](const T &t) {
            return new_inc(old(t));
        };
    }
    T start_;
    typename iterator<T>::incrementor incrementor_;
    typename iterator<T>::terminator terminator_;
};

template <typename T>
range<T> from(const T &start) {
    return range<T>(start);
}

} // namespace epsol::range

#endif // EPSOL_RANGE_RANGE_
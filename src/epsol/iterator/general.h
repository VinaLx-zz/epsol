#ifndef EPSOL_ITERATOR_GENERAL_
#define EPSOL_ITERATOR_GENERAL_

#include "basic-traits.h"
#include <functional>

namespace epsol::iterator {

class iter_end_t {};

template <bool Readonly, typename T, typename H>
class forward_iterator
    : public iterator_basic_traits<Readonly, T, std::forward_iterator_tag> {
  private:
    using super_type =
        iterator_basic_traits<Readonly, T, std::forward_iterator_tag>;
    using self_type = forward_iterator<Readonly, T, H>;

  public:
    using incrementor = std::function<H(const H &)>;
    using terminator = std::function<bool(const H &)>;
    using accessor = std::function<typename super_type::reference(const H &)>;

    forward_iterator(
        const H &init, accessor get, incrementor inc, terminator term)
        : next_(init), get_(get), inc_(inc), is_terminate_(term){};

    typename super_type::pointer operator->() {
        return &get_value();
    }
    typename super_type::reference operator*() {
        return get_value();
    }

    bool terminated() const {
        return terminated_;
    }

    self_type operator++() {
        if (should_terminated()) {
            terminated_ = true;
        } else {
            increment();
        }
        return *this;
    }
    self_type operator++(int) {
        auto ret = *this;
        operator++();
        return ret;
    }

  protected:
    typename super_type::reference get_value() {
        return get_(next_);
    }
    void increment() {
        next_ = inc_(next_);
    }
    bool should_terminated() const {
        return terminated_ or is_terminate_(next_);
    }

  private:
    H next_;
    bool terminated_ = false;
    accessor get_;
    incrementor inc_;
    terminator is_terminate_;
};

template <bool b, typename T, typename H>
bool operator==(const forward_iterator<b, T, H> &iter, iter_end_t _) {
    return iter.terminated();
}

template <bool b, typename T, typename H>
bool operator==(iter_end_t e, const forward_iterator<b, T, H> &iter) {
    return iter == e;
}

template <bool b, typename T, typename H>
bool operator!=(const forward_iterator<b, T, H> &iter, iter_end_t e) {
    return not (iter == e);
}

template <bool b, typename T, typename H>
bool operator!=(iter_end_t e, const forward_iterator<b, T, H> &iter) {
    return not (iter == e);
}

} // namespace epsol::iterator

#endif // EPSOL_ITERATOR_GENERAL_
#ifndef EPSOL_ITERATOR_GENERAL_
#define EPSOL_ITERATOR_GENERAL_

#include "basic-traits.h"
#include "epsol/functional.h"
#include <functional>
#include <type_traits>

namespace epsol::iterator {

class iter_end_t {};

inline iter_end_t end() {
    return iter_end_t{};
}

template <
    bool Readonly, typename T, typename H,
    typename Tag = std::forward_iterator_tag>
class forward_iterator : public iterator_basic_traits<Readonly, T, Tag> {
    static_assert(
        std::is_base_of<Tag, std::forward_iterator_tag>::value or
        (std::is_same<Tag, std::output_iterator_tag>::value and not Readonly));

  private:
    using super_type = iterator_basic_traits<Readonly, T, Tag>;
    using self_type = forward_iterator<Readonly, T, H>;

  public:
    using incrementor = std::function<H(H)>;
    using terminator = functional::Predicate<const H &>;
    using filter = functional::Predicate<const T &>;
    using accessor = std::function<typename super_type::reference(const H &)>;

    forward_iterator(
        const H &init, accessor get, incrementor inc, terminator term_now,
        terminator term_next, filter p)
        : now_(init), get_(get), inc_(inc), term_now_(term_now),
          term_next_(term_next), filter_(p),
          terminated_(term_next_(init) or not p(get(init))){};

    typename super_type::pointer operator->() {
        return &get_value();
    }
    typename super_type::reference operator*() {
        return get_value();
    }

    bool terminated() const {
        return terminated_;
    }

    self_type &begin() {
        return *this;
    }

    iter_end_t end() {
        return epsol::iterator::end();
    }

    self_type &operator++() {
        if (terminated_ or (terminated_ = term_now_(now_))) {
            return *this;
        }
        auto next = inc_(now_);
        if ((terminated_ = term_next_(next))) {
            return *this;
        }
        now_ = std::move(next);
        return filter_(get_value()) ? *this : operator++();
    }
    self_type operator++(int) {
        auto ret = *this;
        operator++();
        return ret;
    }

  protected:
    typename super_type::reference get_value() {
        return get_(now_);
    }
    void increment() {
        now_ = inc_(now_);
    }

  private:
    H now_;
    accessor get_;
    incrementor inc_;
    terminator term_now_, term_next_;
    filter filter_;
    bool terminated_;
};

template <bool b, typename T, typename H, typename Tag>
bool operator==(const forward_iterator<b, T, H, Tag> &iter, iter_end_t _) {
    return iter.terminated();
}

template <bool b, typename T, typename H, typename Tag>
bool operator==(iter_end_t e, const forward_iterator<b, T, H, Tag> &iter) {
    return iter == e;
}

template <bool b, typename T, typename H, typename Tag>
bool operator!=(const forward_iterator<b, T, H, Tag> &iter, iter_end_t e) {
    return not(iter == e);
}

template <bool b, typename T, typename H, typename Tag>
bool operator!=(iter_end_t e, const forward_iterator<b, T, H, Tag> &iter) {
    return not(iter == e);
}

} // namespace epsol::iterator

#endif // EPSOL_ITERATOR_GENERAL_
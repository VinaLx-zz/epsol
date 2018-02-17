#ifndef EPSOL_ITERATOR_GENERAL_
#define EPSOL_ITERATOR_GENERAL_

#include "basic-traits.h"
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
    using terminator = std::function<bool(const H &, const H &)>;
    using accessor = std::function<typename super_type::reference(const H &)>;

    forward_iterator(
        const H &init, accessor get, incrementor inc, terminator term)
        : now_(init), get_(get), inc_(inc), is_terminate_(term){};

    typename super_type::pointer operator->() {
        return &get_value();
    }
    typename super_type::reference operator*() {
        return get_value();
    }

    bool terminated() const {
        return terminated_;
    }

    self_type& begin() {
        return *this;
    }

    iter_end_t end() {
        return epsol::iterator::end();
    }

    self_type operator++() {
        auto next = inc_(now_);
        if (not(terminated_ = terminated_ or is_terminate_(now_, next))) {
            now_ = std::move(next);
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
        return get_(now_);
    }
    void increment() {
        now_ = inc_(now_);
    }

  private:
    H now_;
    bool terminated_ = false;
    accessor get_;
    incrementor inc_;
    terminator is_terminate_;
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
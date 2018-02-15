#ifndef EPSOL_META_UTIL_IS_CONST_ITERATOR_
#define EPSOL_META_UTIL_IS_CONST_ITERATOR_

#include "./void-t.h"
#include <iterator>
#include <type_traits>

namespace epsol::meta {

template <typename T, typename = void>
struct is_iterator : public std::false_type {};

template <typename T>
struct is_iterator<
    T, std::enable_if_t<
           std::is_base_of<
               std::input_iterator_tag,
               typename std::iterator_traits<T>::iterator_category>::value or
           std::is_same<
               std::output_iterator_tag,
               typename std::iterator_traits<T>::iterator_category>::value>>
    : public std::true_type {};

template <typename T>
[[maybe_unused]] constexpr bool is_iterator_v = is_iterator<T>::value;

template <typename T, typename = void>
struct is_mutable_iterator : std::false_type {};

template <typename T>
struct is_mutable_iterator<
    T, std::enable_if_t<
           is_iterator<T>::value and
           std::is_same<
               std::add_lvalue_reference_t<
                   typename std::iterator_traits<T>::value_type>,
               decltype(*std::declval<T>())>::value>> : std::true_type {};

template <typename T>
[[maybe_unused]] constexpr bool is_mutable_iterator_v =
    is_mutable_iterator<T>::value;

template <typename T, typename = void>
struct is_const_iterator : std::false_type {};

template <typename T>
struct is_const_iterator<
    T, std::enable_if_t<
           is_iterator<T>::value and not is_mutable_iterator<T>::value>>
    : std::true_type {};

template <typename T>
[[maybe_unused]] constexpr bool is_const_iterator_v =
    is_const_iterator<T>::value;

} // namespace epsol::meta

#endif // EPSOL_META_UTIL_IS_CONST_ITERATOR_
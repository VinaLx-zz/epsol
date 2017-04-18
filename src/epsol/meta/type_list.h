#ifndef EPSOL_META_TYPE_LIST
#define EPSOL_META_TYPE_LIST

#include <cstdint>
#include <type_traits>

namespace epsol::meta {

template <typename... Types>
struct type_list {
    static constexpr size_t size = sizeof...(Types);
    static constexpr bool empty = size == 0;
    using type = type_list<Types...>;
};

/**
 * add type T to the tail of type_list
 */
template <typename TpList, typename T>
struct push_back;

template <typename TpList, typename T>
using push_back_t = typename push_back<TpList, T>::type;

template <typename T, typename... Types>
struct push_back<type_list<Types...>, T> : type_list<Types..., T> {};

/**
 * add type T to the head of the type_list
 */
template <typename T, typename TpList>
struct push_front;

template <typename T, typename TpList>
using push_front_t = typename push_front<T, TpList>::type;

template <typename T, typename... Types>
struct push_front<T, type_list<Types...>> : type_list<T, Types...> {};

/**
 * remove the last type fron type_list
 * if type_list is empty, return the empty list itself
 */
template <typename TpList>
struct pop_back;

template <typename TpList>
using pop_back_t = typename pop_back<TpList>::type;

template <typename T>
struct pop_back<type_list<T>> : type_list<> {};

template <typename Head, typename... Types>
struct pop_back<type_list<Head, Types...>>
    : push_front_t<Head, pop_back_t<type_list<Types...>>> {};

/**
 * remove the first type in the type_list
 * if type_lsit is empty, return the empty list itself
 */
template <typename TpList>
struct pop_front;

template <typename TpList>
using pop_front_t = typename pop_front<TpList>::type;

template <typename Head, typename... Types>
struct pop_front<type_list<Head, Types...>> : type_list<Types...> {};

template <>
struct pop_front<type_list<>> : type_list<> {};

/**
 * try to find T in specific type_list<Types...>
 * if found     find::index is the non-negative index, find::value = true
 * if not found find::index = -1, find::value = false
 */
template <typename TpList, typename T>
struct find;

template <typename T, typename... Types>
struct find<type_list<T, Types...>, T> : std::true_type {
    static constexpr int64_t index = 0;
};

template <typename T1, typename T2, typename... Types>
struct find<type_list<T2, Types...>, T1> : find<type_list<Types...>, T1> {
    static constexpr int64_t index = find<type_list<Types...>, T1>::index + 1;
};

template <typename T>
struct find<type_list<>, T> : std::false_type {
    static constexpr int64_t index = -1;
};

}  // namespace epsol::meta

#endif  // EPSOL_META_TYPE_LIST

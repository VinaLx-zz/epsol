#ifndef EPSOL_CONTAINER_CONTAINER_TRAITS_
#define EPSOL_CONTAINER_CONTAINER_TRAITS_

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace epsol::container {

/**
 * an ordinary non-associative container traits contains following
 * types
 */
template <typename Container>
struct container_traits_base {
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using pointer = typename Container::pointer;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::iterator;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;
};

/**
 * associative container add key_type
 */
template <typename Container>
struct associative_container_traits_base : container_traits_base<Container> {
    using key_type = typename Container::key_type;
};

/**
 * the value_type of maps IS DIFFERENT from the definition in STL,
 * which treat `std::pair<const key_type, value_type>` as value_type
 */
template <typename Container>
struct map_traits_base : associative_container_traits_base<Container> {
    using value_type = typename Container::mapped_type;
    using item_type = typename Container::value_type;
};

template <typename Container>
struct container_traits;

/**
 * check whether the container specialize container_traits and its traits
 * inherit container_traits_base
 */
template <typename Container, typename = void>
struct is_container : std::false_type {};

template <typename Container>
struct is_container<
    Container,
    std::enable_if_t<std::is_base_of<
        container_traits_base<Container>, container_traits<Container>>::value>>
    : std::true_type {};

/**
 * check whether the container specialize container_traits and its traits
 * inherit associative_container_traits_base
 */
template <typename Container, typename = void>
struct is_associative : std::false_type {};

template <typename Container>
struct is_associative<
    Container, std::enable_if_t<std::is_base_of<
                   associative_container_traits_base<Container>,
                   container_traits<Container>>::value>> : std::true_type {};

/**
 * check whether the container specialize container_traits and its traits
 * inherit map_traits_base
 */
template <typename Container, typename = void>
struct is_map : std::false_type {};

template <typename Container>
struct is_map<
    Container,
    std::enable_if_t<std::is_base_of<
        map_traits_base<Container>, container_traits<Container>>::value>>
    : std::true_type {};

// add all STL container to container traits

template <typename T, size_t L>
struct container_traits<std::array<T, L>>
    : container_traits_base<std::array<T, L>> {};

template <typename T, typename Alloc>
struct container_traits<std::vector<T, Alloc>>
    : container_traits_base<std::vector<T, Alloc>> {};

template <typename T, typename Alloc>
struct container_traits<std::deque<T, Alloc>>
    : container_traits_base<std::deque<T, Alloc>> {};

template <typename T, typename Alloc>
struct container_traits<std::list<T, Alloc>>
    : container_traits_base<std::list<T, Alloc>> {};

template <typename T, typename Alloc>
struct container_traits<std::forward_list<T, Alloc>>
    : container_traits_base<std::forward_list<T, Alloc>> {};

template <typename T, typename Comp, typename Alloc>
struct container_traits<std::set<T, Comp, Alloc>>
    : associative_container_traits_base<std::set<T, Comp, Alloc>> {};

template <typename T, typename Comp, typename Alloc>
struct container_traits<std::multiset<T, Comp, Alloc>>
    : associative_container_traits_base<std::multiset<T, Comp, Alloc>> {};

template <typename T, typename H, typename E, typename A>
struct container_traits<std::unordered_set<T, H, E, A>>
    : associative_container_traits_base<std::unordered_set<T, H, E, A>> {};

template <typename T, typename H, typename E, typename A>
struct container_traits<std::unordered_multiset<T, H, E, A>>
    : associative_container_traits_base<std::unordered_multiset<T, H, E, A>> {};

template <typename K, typename T, typename Comp, typename Alloc>
struct container_traits<std::map<K, T, Comp, Alloc>>
    : map_traits_base<std::map<K, T, Comp, Alloc>> {};

template <typename K, typename T, typename Comp, typename Alloc>
struct container_traits<std::multimap<K, T, Comp, Alloc>>
    : map_traits_base<std::multimap<K, T, Comp, Alloc>> {};

template <typename K, typename T, typename H, typename E, typename A>
struct container_traits<std::unordered_map<K, T, H, E, A>>
    : map_traits_base<
          std::unordered_map<K, T, H, E, A>> {};

template <typename K, typename T, typename H, typename E, typename A>
struct container_traits<std::unordered_multimap<K, T, H, E, A>>
    : map_traits_base<std::unordered_multimap<K, T, H, E, A>> {};

}  // namespace epsol::container

#endif  // EPSOL_CONTAINER_CONTAINER_TRAITS

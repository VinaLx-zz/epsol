#include <iostream>
#include <type_traits>
#include <typeinfo>
#include "epsol/container.h"

using namespace epsol;

int main(int argc, char** argv) {
    static_assert(std::is_same<
                  container::container_traits<std::vector<int>>::value_type,
                  int>::value);
    static_assert(std::is_base_of<
                  container::container_traits_base<std::vector<int>>,
                  container::container_traits<std::vector<int>>>::value);

    static_assert(container::is_container<std::vector<int>>::value);
    static_assert(container::is_associative<std::unordered_set<int>>::value);
    static_assert(container::is_map<std::map<int, double>>::value);
    static_assert(
        container::is_associative<std::unordered_map<double, int>>::value);
    static_assert(not container::is_associative<std::vector<int>>::value);
    static_assert(not container::is_map<std::multiset<int>>::value);
}

#include <string>
#include <type_traits>
#include "epsol/meta/type_list.h"

using namespace epsol::meta;
using std::is_same;
using std::string;

using list1 = type_list<int, double>;

template <typename A>
class TD;

int main() {
    static_assert(list1::size == 2);
    static_assert(list1::empty == false);
    static_assert(
        is_same<
            push_back_t<list1, string>, type_list<int, double, string>>::value);
    static_assert(
        is_same<push_front_t<string, list1>, type_list<string, int, double>>::
            value);
    static_assert(is_same<pop_front_t<list1>, type_list<double>>::value);
    static_assert(is_same<pop_back_t<list1>, type_list<int>>::value);
    static_assert(find<list1, int>::value);
    static_assert(find<list1, int>::index == 0);
    static_assert(find<list1, double>::index == 1);
    static_assert(not find<list1, string>::value);
}

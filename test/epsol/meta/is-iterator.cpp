#include "epsol/meta/util/is-iterator.h"
#include <vector>

using namespace epsol::meta;

int main() {
    static_assert(is_iterator_v<std::vector<int>::iterator>);

    static_assert(is_mutable_iterator_v<std::vector<int>::iterator>);
    static_assert(not is_const_iterator_v<std::vector<int>::iterator>);

    static_assert(not is_mutable_iterator_v<std::vector<int>::const_iterator>);
    static_assert(is_const_iterator_v<std::vector<int>::const_iterator>);
}

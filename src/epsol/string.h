#include <cctype>
#include <string>

namespace epsol {
namespace string {

/**
 * returns an copy of the original string with the leading and trailing
 * characters that satisfy the predicate stripped
 */
template <typename Predicate>
std::string strip_if(const std::string& s, Predicate p) {
    if (s.empty()) {
        return "";
    }
    std::string::size_type b(0), e(s.size());
    for (; b < e and p(s[b]);)
        ++b;
    for (; e > b and p(s[e - 1]);)
        --e;
    return s.substr(b, e - b);
}
/**
 * returns an copy of the original string with leading and trailing spaces
 * (satisfies isspace) stripped
 */
inline std::string strip(const std::string& s) {
    return strip_if(s, [](char c) { return isspace(c); });
}

}  // namespace string

}  // namespace epsol

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_NONE_OF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_NONE_OF_H_

#include <algorithm>

namespace liuyunbin {

/*
 * none_of
 */
template <typename InputIt, typename UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if(first, last, p) == last;
}

} // namespace liuyunbin

#endif

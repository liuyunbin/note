#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_ALL_OF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_ALL_OF_H_

#include <algorithm>

namespace liuyunbin {

/*
 * all_of
 */
template <typename InputIt, typename UnaryPredicate>
bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if_not(first, last, p) == last;
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_ANY_OF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_ANY_OF_H_

#include <algorithm>

namespace liuyunbin {

/*
 * any_of
 */
template <typename InputIt, typename UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if(first, last, p) != last;
}

} // namespace liuyunbin

#endif

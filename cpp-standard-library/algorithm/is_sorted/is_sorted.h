#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_IS_SORTED_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_IS_SORTED_H_

#include <algorithm>

namespace liuyunbin {

/*
 * is_sorted
 */
template <typename ForwardIt, typename Compare>
bool is_sorted(ForwardIt first, ForwardIt last, Compare comp) {
  return std::is_sorted_until(first, last, comp) == last;
}

template <typename ForwardIt> bool is_sorted(ForwardIt first, ForwardIt last) {
  return std::is_sorted_until(first, last) == last;
}

} // namespace liuyunbin

#endif

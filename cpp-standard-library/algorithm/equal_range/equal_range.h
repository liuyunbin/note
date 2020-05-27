#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_EQUAL_RANGE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_EQUAL_RANGE_H_

#include <algorithm>
#include <utility>

namespace liuyunbin {

/*
 * equal_range
 */
template <typename ForwardIt, typename T, typename Compare>
std::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last,
                                            const T &value, Compare comp) {
  return {std::lower_bound(first, last, value, comp),
          std::upper_bound(first, last, value, comp)};
}

template <typename ForwardIt, typename T>
std::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last,
                                            const T &value) {
  return {std::lower_bound(first, last, value),
          std::upper_bound(first, last, value)};
}

} // namespace liuyunbin

#endif

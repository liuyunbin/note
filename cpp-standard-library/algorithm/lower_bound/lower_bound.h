#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_LOWER_BOUND_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_LOWER_BOUND_H_

#include <iterator>

namespace liuyunbin {

/*
 * lower_bound
 */
template <typename ForwardIt, typename T, typename Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value,
                      Compare comp) {
  auto count = std::distance(first, last);
  while (count > 0) {
    auto half = count / 2;
    auto it = std::next(first, half);
    if (comp(*it, value)) {
      first = ++it;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return first;
}

template <typename ForwardIt, typename T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value) {
  auto count = std::distance(first, last);
  while (count > 0) {
    auto half = count / 2;
    auto it = std::next(first, half);
    if (*it < value) {
      first = ++it;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return first;
}

} // namespace liuyunbin

#endif

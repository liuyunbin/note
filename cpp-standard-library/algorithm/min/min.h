#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MIN_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MIN_H_

#include <algorithm>
#include <initializer_list>

namespace liuyunbin {

/*
 * min
 */
template <typename T> const T &min(const T &lhs, const T &rhs) {
  return lhs < rhs ? lhs : rhs;
}

template <typename T, typename Compare>
const T &min(const T &lhs, const T &rhs, Compare comp) {
  return comp(lhs, rhs) ? lhs : rhs;
}

template <class T> T min(std::initializer_list<T> ilist) {
  return *std::min_element(ilist.begin(), ilist.end());
}

template <class T, class Compare>
T min(std::initializer_list<T> ilist, Compare comp) {
  return *std::min_element(ilist.begin(), ilist.end(), comp);
}
} // namespace liuyunbin

#endif

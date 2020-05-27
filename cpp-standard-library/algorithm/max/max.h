#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MAX_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MAX_H_

#include <algorithm>
#include <initializer_list>

namespace liuyunbin {

/*
 * max
 */
template <typename T> const T &max(const T &lhs, const T &rhs) {
  return lhs < rhs ? rhs : lhs;
}

template <typename T, typename Compare>
const T &max(const T &lhs, const T &rhs, Compare comp) {
  return comp(lhs, rhs) ? rhs : lhs;
}

template <class T> T max(std::initializer_list<T> ilist) {
  return *std::max_element(ilist.begin(), ilist.end());
}

template <class T, class Compare>
T max(std::initializer_list<T> ilist, Compare comp) {
  return *std::max_element(ilist.begin(), ilist.end(), comp);
}

} // namespace liuyunbin

#endif

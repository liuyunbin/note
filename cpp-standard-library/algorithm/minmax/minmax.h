#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MINMAX_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MINMAX_H_

#include <algorithm>
#include <initializer_list>
#include <utility>

namespace liuyunbin {

/*
 * minmax
 */
template <typename T>
std::pair<const T &, const T &> minmax(const T &lhs, const T &rhs) {
  if (lhs < rhs)
    return {lhs, rhs};
  return {rhs, lhs};
}

template <typename T, typename Compare>
std::pair<const T &, const T &> minmax(const T &lhs, const T &rhs,
                                       Compare comp) {
  if (comp(lhs, rhs))
    return {lhs, rhs};
  return {rhs, lhs};
}

template <typename T> std::pair<T, T> minmax(std::initializer_list<T> ilist) {
  auto p = std::minmax_element(ilist.begin(), ilist.end());
  return {*p.first, *p.second};
}

template <typename T, typename Compare>
std::pair<T, T> minmax(std::initializer_list<T> ilist, Compare comp) {
  auto p = std::minmax_element(ilist.begin(), ilist.end(), comp);
  return {*p.first, *p.second};
}

} // namespace liuyunbin

#endif

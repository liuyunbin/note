#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_BINARY_SEARCH_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_BINARY_SEARCH_H_

#include <algorithm>

namespace liuyunbin {

/*
 * binary_search
 */
template <typename InputIt, typename T, typename Compare>
bool binary_search(InputIt first, InputIt last, const T &value, Compare comp) {
  first = std::lower_bound(first, last, value, comp);
  if (first == last)
    return false;
  return !comp(value, *first);
}

template <typename InputIt, typename T>
bool binary_search(InputIt first, InputIt last, const T &value) {
  first = std::lower_bound(first, last, value);
  if (first == last)
    return false;
  return !(value < *first);
}

} // namespace liuyunbin

#endif

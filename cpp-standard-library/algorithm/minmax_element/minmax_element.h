#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MINMAX_ELEMENT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MINMAX_ELEMENT_H_

#include <algorithm>
#include <utility>

namespace liuyunbin {

/*
 * minmax_element
 */
template <typename ForwardIt>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first,
                                               ForwardIt last) {
  return {std::min_element(first, last), std::max_element(first, last)};
}

template <typename ForwardIt, typename Compare>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last,
                                               Compare comp) {
  return {std::min_element(first, last, comp),
          std::max_element(first, last, comp)};
}

} // namespace liuyunbin

#endif

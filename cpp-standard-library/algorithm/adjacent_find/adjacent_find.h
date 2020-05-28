#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_ADJACENT_FIND_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_ADJACENT_FIND_H_

#include <iterator>

namespace liuyunbin {

/*
 * adjacent_find
 */
template <typename ForwardIt>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last) {
  if (first == last)
    return last;
  for (auto next = std::next(first); next != last; ++first, ++next)
    if (*next == *first)
      return first;
  return last;
}

template <typename ForwardIt, typename BinaryPredicate>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p) {
  if (first == last)
    return last;
  for (auto next = std::next(first); next != last; ++first, ++next)
    if (p(*next, *first))
      return first;
  return last;
}

} // namespace liuyunbin

#endif

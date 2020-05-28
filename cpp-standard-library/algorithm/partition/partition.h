#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PARTITION_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PARTITION_H_

#include <algorithm>

namespace liuyunbin {

/*
 * partition
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  first = std::find_if_not(first, last, p);
  if (first == last)
    return first;
  for (auto next = std::next(first); next != last; ++next)
    if (p(*next))
      std::iter_swap(first++, next);
  return first;
}

} // namespace liuyunbin

#endif

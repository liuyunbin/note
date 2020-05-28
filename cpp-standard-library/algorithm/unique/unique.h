#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_UNIQUE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_UNIQUE_H_

#include <utility>

namespace liuyunbin {

/*
 * unique
 */
template <typename ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last) {
  if (first == last)
    return last;
  auto next = first;
  while (++next != last)
    if (!(*first == *next))
      *++first = std::move(*next);
  return ++first;
}

template <typename ForwardIt, typename BinaryPredicate>
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p) {
  if (first == last)
    return last;
  auto next = first;
  while (++next != last)
    if (!p(*first, *next))
      *++first = std::move(*next);
  return ++first;
}

} // namespace liuyunbin

#endif

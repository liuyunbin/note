#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_ROTATE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_ROTATE_H_

#include <algorithm>

namespace liuyunbin {

/*
 * rotate
 */
template <typename ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
  if (first == n_first)
    return last;
  if (n_first == last)
    return first;
  auto next = n_first;
  while (next != last) {
    std::iter_swap(next++, first++);
    if (first == n_first)
      n_first = next;
  }
  auto return_value = first;
  std::rotate(first, n_first, last);
  return return_value;
}

} // namespace liuyunbin

#endif

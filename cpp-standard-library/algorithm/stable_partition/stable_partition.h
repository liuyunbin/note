#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_STABLE_PARTITION_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_STABLE_PARTITION_H_

#include <algorithm>

namespace liuyunbin {

/*
 * stable_partition
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt stable_partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  while (first != last && p(*first))
    ++first;
  if (first == last)
    return last;

  auto n = std::distance(first, last);
  auto *temp_memory =
      new typename std::iterator_traits<ForwardIt>::value_type[n];
  decltype(n) index = 0;
  auto current = first;

  while (first != last) {
    if (p(*first))
      *current++ = *first++;
    else
      temp_memory[index++] = *first++;
  }
  std::copy_n(temp_memory, index, current);
  delete[] temp_memory;
  return current;
}

} // namespace liuyunbin

#endif

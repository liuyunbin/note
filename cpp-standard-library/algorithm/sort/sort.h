#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_SORT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_SORT_H_

#include <algorithm>
#include <functional>
#include <utility>

namespace liuyunbin {

/*
 * sort
 */
template <typename RandomAccessIt, typename Compare>
void sort(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1)
    return;
  auto value = std::move(*first);
  auto lhs = first;
  auto rhs = last - 1;
  while (lhs != rhs) {
    while (lhs != rhs && !comp(*rhs, value))
      --rhs;
    if (lhs == rhs)
      break;
    *lhs++ = std::move(*rhs);
    while (lhs != rhs && !comp(value, *lhs))
      ++lhs;
    if (lhs == rhs)
      break;
    *rhs-- = std::move(*lhs);
  }
  *lhs = std::move(value);
  std::sort(first, lhs, comp);
  std::sort(lhs + 1, last, comp);
}

template <typename RandomAccessIt>
void sort(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::sort(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

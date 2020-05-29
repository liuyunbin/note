#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_NTH_ELEMENT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_NTH_ELEMENT_H_

#include <algorithm>
#include <functional>
#include <utility>

namespace liuyunbin {

/*
 * nth_element
 */
template <typename RandomAccessIt, typename Compare>
void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last,
                 Compare comp) {
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
  if (lhs == nth)
    return;
  if (lhs < nth)
    liuyunbin::nth_element(lhs + 1, nth, last, comp);
  else
    liuyunbin::nth_element(first, nth, lhs, comp);
}

template <typename RandomAccessIt>
void nth_element(RandomAccessIt first, RandomAccessIt nth,
                 RandomAccessIt last) {
  liuyunbin::nth_element(
      first, nth, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

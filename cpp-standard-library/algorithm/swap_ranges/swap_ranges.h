#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_SWAP_RANGES_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_SWAP_RANGES_H_

#include <algorithm>

namespace liuyunbin {

/*
 * swap_ranges
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) {
  while (first1 != last1)
    std::iter_swap(first1++, first2++);
  return first2;
}

} // namespace liuyunbin

#endif

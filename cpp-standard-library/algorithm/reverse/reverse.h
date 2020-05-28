#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REVERSE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REVERSE_H_

#include <algorithm>

namespace liuyunbin {

/*
 * reverse
 */
template <typename BidirIt> void reverse(BidirIt first, BidirIt last) {
  while (first != last && --last != first)
    std::iter_swap(first++, last);
}

} // namespace liuyunbin

#endif

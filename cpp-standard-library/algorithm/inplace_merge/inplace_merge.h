#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_INPLACE_MERGE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_INPLACE_MERGE_H_

#include <algorithm>

namespace liuyunbin {

/*
 * inplace_merge
 */
template <typename BidirIt, typename Compare>
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last, Compare comp) {
  auto n = std::distance(first, middle);
  auto *p = new typename std::iterator_traits<BidirIt>::value_type[n];
  std::copy(first, middle, p);
  std::merge(p, p + n, middle, last, first, comp);
  delete[] p;
}

template <typename BidirIt>
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last) {
  auto n = std::distance(first, middle);
  auto *p = new typename std::iterator_traits<BidirIt>::value_type[n];
  std::copy(first, middle, p);
  std::merge(p, p + n, middle, last, first);
  delete[] p;
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_INPLACE_MERGE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_INPLACE_MERGE_H_

#include <algorithm>

namespace liuyunbin {

/*
 * inplace_merge
 */
template <typename ForwardIt, typename Compare>
void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last,
                   Compare comp) {
  auto n = std::distance(first, middle);
  auto *p = new typename std::iterator_traits<ForwardIt>::value_type[n];
  std::copy(first, middle, p);
  std::merge(p, p + n, middle, last, first, comp);
  delete[] p;
}

template <typename ForwardIt>
void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last) {
  auto n = std::distance(first, middle);
  auto *p = new typename std::iterator_traits<ForwardIt>::value_type[n];
  std::copy(first, middle, p);
  std::merge(p, p + n, middle, last, first);
  delete[] p;
}

} // namespace liuyunbin

#endif

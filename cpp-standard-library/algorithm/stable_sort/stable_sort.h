#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_STABLE_SORT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_STABLE_SORT_H_

#include <algorithm>
#include <functional>

namespace liuyunbin {

/*
 * stable_sort
 */
template <typename RandomAccessIt, typename Compare>
void stable_sort(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1)
    return;
  auto mid = first + (last - first) / 2;
  std::sort(first, mid, comp);
  std::sort(mid, last, comp);
  std::inplace_merge(first, mid, last);
}

template <typename RandomAccessIt>
void stable_sort(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::stable_sort(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

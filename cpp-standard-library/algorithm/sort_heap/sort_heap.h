#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_SORT_HEAP_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_SORT_HEAP_H_

#include <algorithm>
#include <functional>

namespace liuyunbin {

/*
 * sort_heap
 */
template <typename RandomAccessIt, typename Compare>
void sort_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1)
    return;
  while (last - first > 1)
    std::pop_heap(first, last--, comp);
}

template <typename RandomAccessIt>
void sort_heap(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::sort_heap(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

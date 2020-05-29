#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PARTIAL_SORT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PARTIAL_SORT_H_

#include <algorithm>
#include <functional>
#include <iterator>

namespace liuyunbin {

/*
 * partial_sort
 */
template <typename RandomAccessIt, typename Compare>
void partial_sort(RandomAccessIt first, RandomAccessIt middle,
                  RandomAccessIt last, Compare comp) {
  std::make_heap(first, middle);
  for (auto it = middle; it != last; ++it)
    if (comp(*it, *first)) {
      std::pop_heap(first, middle, comp);
      std::swap(*it, *(middle - 1));
      std::push_heap(first, middle, comp);
    }
  std::sort_heap(first, middle);
}

template <typename RandomAccessIt>
void partial_sort(RandomAccessIt first, RandomAccessIt middle,
                  RandomAccessIt last) {
  liuyunbin::partial_sort(
      first, middle, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

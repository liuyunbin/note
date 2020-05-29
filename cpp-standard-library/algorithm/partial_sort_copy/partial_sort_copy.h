#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PARTIAL_SORT_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PARTIAL_SORT_COPY_H_

#include <algorithm>
#include <functional>
#include <iterator>

namespace liuyunbin {

/*
 * partial_sort_copy
 */
template <typename InputIt, typename RandomAccessIt, typename Compare>
RandomAccessIt partial_sort_copy(InputIt first, InputIt last,
                                 RandomAccessIt d_first, RandomAccessIt d_last,
                                 Compare comp) {
  auto d_middle = d_first;
  while (first != last && d_middle != d_last)
    *d_middle++ = *first++;
  std::make_heap(d_first, d_middle);
  for (auto it = first; it != last; ++it)
    if (comp(*it, *d_first)) {
      std::pop_heap(d_first, d_middle, comp);
      std::swap(*it, *(d_middle - 1));
      std::push_heap(d_first, d_middle, comp);
    }
  std::sort_heap(d_first, d_middle);
  return d_middle;
}

template <typename InputIt, typename RandomAccessIt>
RandomAccessIt partial_sort_copy(InputIt first, InputIt last,
                                 RandomAccessIt d_first,
                                 RandomAccessIt d_last) {
  return liuyunbin::partial_sort_copy(
      first, last, d_first, d_last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_IS_HEAP_UNTIL_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_IS_HEAP_UNTIL_H_

namespace liuyunbin {

/*
 * is_heap_until
 */
template <typename RandomAccessIt, typename Compare>
RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last,
                             Compare comp) {
  auto n = last - first;
  decltype(n) i = 1;
  for (;;) {
    if (i >= n)
      return last;
    if (comp(first[(i - 1) / 2], first[i]))
      return first + i;
    ++i;
  }
}

template <typename RandomAccessIt>
RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last) {
  auto n = last - first;
  decltype(n) i = 1;
  for (;;) {
    if (i >= n)
      return last;
    if (first[(i - 1) / 2] < first[i])
      return first + i;
    ++i;
  }
}

} // namespace liuyunbin

#endif

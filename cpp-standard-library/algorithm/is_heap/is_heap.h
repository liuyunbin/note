#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_IS_HEAP_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_IS_HEAP_H_

namespace liuyunbin {

/*
 * is_heap
 */
template <typename RandomAccessIt, typename Compare>
bool is_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  auto n = last - first;
  decltype(n) i = 0;
  for (;;) {
    if (2 * i + 1 >= n)
      return true;
    if (comp(first[i], first[2 * i + 1]))
      return false;
    if (2 * i + 2 >= n)
      return true;
    if (comp(first[i], first[2 * i + 2]))
      return false;
    ++i;
  }
}

template <typename RandomAccessIt>
bool is_heap(RandomAccessIt first, RandomAccessIt last) {
  auto n = last - first;
  decltype(n) i = 0;
  for (;;) {
    if (2 * i + 1 >= n)
      return true;
    if (first[i] < first[2 * i + 1])
      return false;
    if (2 * i + 2 >= n)
      return true;
    if (first[i] < first[2 * i + 2])
      return false;
    ++i;
  }
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MAKE_HEAP_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MAKE_HEAP_H_

#include <algorithm>
#include <functional>
#include <utility>

namespace liuyunbin {

/*
 * make_heap
 */
namespace detail {

template <typename RandomAccessIt, typename Distance, typename T,
          typename Compare>
void __pop_heap(RandomAccessIt first, Distance current_index,
                Distance max_index, T &&value, Compare comp) {
  for (;;) {
    auto lhs_index = current_index * 2 + 1;
    auto rhs_index = lhs_index + 1;
    if (lhs_index >= max_index)
      break;
    if (rhs_index >= max_index) {
      if (comp(value, first[lhs_index])) {
        first[current_index] = std::move(first[lhs_index]);
        current_index = lhs_index;
      }
      break;
    }
    if (comp(first[lhs_index], value) && comp(first[rhs_index], value))
      break;
    if (comp(first[lhs_index], first[rhs_index])) {
      first[current_index] = std::move(first[rhs_index]);
      current_index = rhs_index;
    } else {
      first[current_index] = std::move(first[lhs_index]);
      current_index = lhs_index;
    }
  }
  first[current_index] = std::move(value);
}

} // namespace detail

template <typename RandomAccessIt, typename Compare>
void make_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1)
    return;
  auto max_index = last - first;
  auto current_index = (max_index - 2) / 2;
  for (;;) {
    detail::__pop_heap(first, current_index, max_index,
                       std::move(first[current_index]), comp);
    if (current_index == 0)
      break;
    --current_index;
  }
}

template <typename RandomAccessIt>
void make_heap(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::make_heap(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

} // namespace liuyunbin

#endif

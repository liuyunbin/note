#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PUSH_HEAP_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PUSH_HEAP_H_

#include <utility>

namespace liuyunbin {

/*
 * push_heap
 */
template <typename RandomAccessIt, typename Compare>
void push_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1)
    return;
  auto value = std::move(*--last);
  auto current_index = last - first;
  auto parent_index = (current_index - 1) / 2;
  while (current_index > 0 && comp(first[parent_index], value)) {
    first[current_index] = std::move(first[parent_index]);
    current_index = parent_index;
    parent_index = (current_index - 1) / 2;
  }
  first[current_index] = std::move(value);
}

template <typename RandomAccessIt>
void push_heap(RandomAccessIt first, RandomAccessIt last) {
  if (last - first <= 1)
    return;
  auto value = std::move(*--last);
  auto current_index = last - first;
  auto parent_index = (current_index - 1) / 2;
  while (current_index > 0 && first[parent_index] < value) {
    first[current_index] = std::move(first[parent_index]);
    current_index = parent_index;
    parent_index = (current_index - 1) / 2;
  }
  first[current_index] = std::move(value);
}

} // namespace liuyunbin

#endif

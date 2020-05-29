#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PREV_PERMUTATION_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PREV_PERMUTATION_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace liuyunbin {

/*
 * prev_permutation
 */
template <typename BidirIt, typename Compare>
bool prev_permutation(BidirIt first, BidirIt last, Compare comp) {
  if (first == last)
    return false;
  auto it = std::prev(last);
  if (first == it)
    return false;
  for (;;) {
    --it;
    if (comp(*std::next(it), *it)) {
      auto temp_it = last;
      while (!comp(*--temp_it, *it))
        ;
      std::iter_swap(it, temp_it);
      std::reverse(++it, last);
      return true;
    }
    if (it == first) {
      std::reverse(first, last);
      return true;
    }
  }
}

template <typename BidirIt> bool prev_permutation(BidirIt first, BidirIt last) {
  if (first == last)
    return false;
  auto it = std::prev(last);
  if (first == it)
    return false;
  for (;;) {
    --it;
    if (*std::next(it) < *it) {
      auto temp_it = last;
      while (!(*--temp_it < *it))
        ;
      std::iter_swap(it, temp_it);
      std::reverse(++it, last);
      return true;
    }
    if (it == first) {
      std::reverse(first, last);
      return true;
    }
  }
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_NEXT_PERMUTATION_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_NEXT_PERMUTATION_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace liuyunbin {

/*
 * next_permutation
 */
template <typename BidirIt, typename Compare>
bool next_permutation(BidirIt first, BidirIt last, Compare comp) {
  if (first == last)
    return false;
  auto it = std::prev(last);
  if (first == it)
    return false;
  for (;;) {
    --it;
    if (comp(*it, *std::next(it))) {
      auto temp_it = last;
      while (!comp(*it, *--temp_it))
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

template <typename BidirIt> bool next_permutation(BidirIt first, BidirIt last) {
  if (first == last)
    return false;
  auto it = std::prev(last);
  if (first == it)
    return false;
  for (;;) {
    --it;
    if (*it < *std::next(it)) {
      auto temp_it = last;
      while (!(*it < *--temp_it))
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

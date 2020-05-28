#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FIND_FIRST_OF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FIND_FIRST_OF_H_

#include <algorithm>

namespace liuyunbin {

/*
 * find_first_of
 */
template <typename InputIt, typename ForwardIt>
InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2,
                      ForwardIt last2) {
  while (first1 != last1) {
    if (std::find(first2, last2, *first1) != last2)
      return first1;
    ++first1;
  }
  return last1;
}

template <typename InputIt, typename ForwardIt, typename BinaryPredicate>
InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2,
                      ForwardIt last2, BinaryPredicate p) {
  while (first1 != last1) {
    for (auto it = first2; it != last2; ++it)
      if (p(*first1, *it))
        return first1;
    ++first1;
  }
  return last1;
}

} // namespace liuyunbin

#endif

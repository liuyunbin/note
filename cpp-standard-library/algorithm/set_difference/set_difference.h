#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_SET_DIFFERENCE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_SET_DIFFERENCE_H_

#include <algorithm>

namespace liuyunbin {

/*
 * set_difference
 */
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                        InputIt2 last2, OutputIt d_first, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      ++first2;
    else if (comp(*first1, *first2))
      *d_first++ = *first1++;
    else {
      ++first1;
      ++first2;
    }
  }
  return std::copy(first1, last1, d_first);
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                        InputIt2 last2, OutputIt d_first) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      ++first2;
    else if (*first1 < *first2)
      *d_first++ = *first1++;
    else {
      ++first1;
      ++first2;
    }
  }
  return std::copy(first1, last1, d_first);
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_INCLUDES_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_INCLUDES_H_

namespace liuyunbin {

/*
 * includes
 */
template <typename InputIt1, typename InputIt2, typename Compare>
bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
              Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      return false;
    else if (comp(*first1, *first2))
      ++first1;
    else {
      ++first1;
      ++first2;
    }
  }
  return first2 == last2;
}

template <typename InputIt1, typename InputIt2>
bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2,
              InputIt2 last2) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      return false;
    else if (*first1 < *first2)
      ++first1;
    else {
      ++first1;
      ++first2;
    }
  }
  return first2 == last2;
}

} // namespace liuyunbin

#endif

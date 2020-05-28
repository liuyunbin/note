#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MISMATCH_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MISMATCH_H_

#include <utility>

namespace liuyunbin {

/*
 * mismatch
 */
template <typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2) {
  while (first1 != last1 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, BinaryPredicate op) {
  while (first1 != last1 && op(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

template <typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2) {
  while (first1 != last1 && first2 != last2 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2,
                                       BinaryPredicate op) {
  while (first1 != last1 && first2 != last2 && op(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

} // namespace liuyunbin

#endif

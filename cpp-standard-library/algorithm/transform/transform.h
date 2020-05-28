#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_TRANSFORM_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_TRANSFORM_H_

namespace liuyunbin {

/*
 * transform
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt transform(InputIt first, InputIt last, OutputIt d_first,
                   UnaryPredicate p) {
  while (first != last)
    *d_first++ = p(*first++);
  return d_first;
}

template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename BinaryPredicate>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   OutputIt d_first, BinaryPredicate p) {
  while (first1 != last1)
    *d_first++ = p(*first1++, *first2++);
  return d_first;
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_UNIQUE_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_UNIQUE_COPY_H_

namespace liuyunbin {

/*
 * unique_copy
 */
template <typename InputIt, typename OutputIt>
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first) {
  if (first == last)
    return d_first;
  *d_first = *first;
  while (++first != last)
    if (!(*first == *d_first))
      *++d_first = *first;
  return ++d_first;
}

template <typename InputIt, typename OutputIt, typename BinaryPredicate>
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first,
                     BinaryPredicate p) {
  if (first == last)
    return d_first;
  *d_first = *first;
  while (++first != last)
    if (!p(*first, *d_first))
      *++d_first = *first;
  return ++d_first;
}

} // namespace liuyunbin

#endif

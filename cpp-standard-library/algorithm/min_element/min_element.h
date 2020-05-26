#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MIN_ELEMENT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MIN_ELEMENT_H_

namespace liuyunbin {

/*
 * min_element
 */
template <typename ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last) {
  if (first == last)
    return last;
  ForwardIt smallest = first;
  while (++first != last)
    if (*first < *smallest)
      smallest = first;
  return smallest;
}

template <typename ForwardIt, typename Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last)
    return last;
  ForwardIt smallest = first;
  while (++first != last)
    if (comp(*first, *smallest))
      smallest = first;
  return smallest;
}

} // namespace liuyunbin

#endif

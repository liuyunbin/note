#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MAX_ELEMENT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MAX_ELEMENT_H_

namespace liuyunbin {

/*
 * max_element
 */
template <typename ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last) {
  if (first == last)
    return last;
  ForwardIt largest = first;
  while (++first != last)
    if (*largest < *first)
      largest = first;
  return largest;
}

template <typename ForwardIt, typename Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last)
    return last;
  ForwardIt largest = first;
  while (++first != last)
    if (comp(*largest, *first))
      largest = first;
  return largest;
}

} // namespace liuyunbin

#endif

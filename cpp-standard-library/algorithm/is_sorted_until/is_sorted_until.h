#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_IS_SORTED_UNTIL_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_IS_SORTED_UNTIL_H_

namespace liuyunbin {

/*
 * is_sorted_until
 */
template <typename ForwardIt, typename Compare>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last)
    return last;
  auto next = first;
  while (++next != last) {
    if (comp(*next, *first))
      return next;
    first = next;
  }
  return last;
}

template <typename ForwardIt>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last) {
  if (first == last)
    return last;
  auto next = first;
  while (++next != last) {
    if (*next < *first)
      return next;
    first = next;
  }
  return last;
}

} // namespace liuyunbin

#endif

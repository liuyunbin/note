#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_IF_H_

namespace liuyunbin {

/*
 * remove_if
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  for (auto it = first; it != last; ++it) {
    if (p(*it))
      continue;
    *first++ = *it;
  }
  return first;
}

} // namespace liuyunbin

#endif

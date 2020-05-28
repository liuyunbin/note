#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_H_

namespace liuyunbin {

/*
 * remove
 */
template <typename ForwardIt, typename T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T &value) {
  for (auto it = first; it != last; ++it) {
    if (*it == value)
      continue;
    *first++ = *it;
  }
  return first;
}

} // namespace liuyunbin

#endif

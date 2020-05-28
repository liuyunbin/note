#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_IS_PARTITIONED_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_IS_PARTITIONED_H_

namespace liuyunbin {

/*
 * is_partitioned
 */
template <typename InputIt, typename UnaryPredicate>
bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last) {
    if (!p(*first))
      break;
    ++first;
  }
  while (first != last) {
    if (p(*first))
      return false;
    ++first;
  }
  return true;
}

} // namespace liuyunbin

#endif

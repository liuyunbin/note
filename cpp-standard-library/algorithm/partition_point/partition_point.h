#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PARTITION_POINT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PARTITION_POINT_H_

namespace liuyunbin {

/*
 * partition_point
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  while (first != last && p(*first))
    ++first;
  return first;
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_PARTITION_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_PARTITION_COPY_H_

#include <utility>

namespace liuyunbin {

/*
 * partition_copy
 */
template <typename InputIt, typename OutputIt1, typename OutputIt2,
          typename UnaryPredicate>
std::pair<OutputIt1, OutputIt2>
partition_copy(InputIt first, InputIt last, OutputIt1 d_first_true,
               OutputIt2 d_first_false, UnaryPredicate p) {
  while (first != last) {
    if (p(*first))
      *d_first_true++ = *first++;
    else
      *d_first_false++ = *first++;
  }
  return {d_first_true, d_first_false};
}

} // namespace liuyunbin

#endif

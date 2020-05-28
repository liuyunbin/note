#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_ROTATE_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_ROTATE_COPY_H_

#include <algorithm>

namespace liuyunbin {

/*
 * rotate_copy
 */
template <typename ForwardIt, typename OutputIt>
OutputIt rotate_copy(ForwardIt first, ForwardIt n_first, ForwardIt last,
                     OutputIt d_first) {
  d_first = std::copy(n_first, last, d_first);
  return std::copy(first, n_first, d_first);
}

} // namespace liuyunbin

#endif

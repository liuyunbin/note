#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MOVE_BACKWARD_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MOVE_BACKWARD_H_

#include <utility>

namespace liuyunbin {

/*
 * move_backward
 */
template <typename BindirIt1, typename BindirIt2>
BindirIt2 move_backward(BindirIt1 first, BindirIt1 last, BindirIt2 d_last) {
  while (first != last)
    *--d_last = std::move(*--last);
  return d_last;
}

} // namespace liuyunbin

#endif

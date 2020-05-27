#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_COPY_BACKWARD_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_COPY_BACKWARD_H_

namespace liuyunbin {

/*
 * copy_backward
 */
template <typename BidirectionalIt1, typename BidirectionalIt2>
BidirectionalIt2 copy_backward(BidirectionalIt1 first, BidirectionalIt1 last,
                               BidirectionalIt2 d_last) {
  while (first != last)
    *--d_last = *--last;
  return d_last;
}

} // namespace liuyunbin

#endif

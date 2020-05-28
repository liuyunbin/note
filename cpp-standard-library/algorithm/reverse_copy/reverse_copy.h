#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REVERSE_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REVERSE_COPY_H_

namespace liuyunbin {

/*
 * reverse_copy
 */
template <typename BidirIt, typename OutputIt>
OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first) {
  while (first != last)
    *d_first++ = *--last;
  return d_first;
}

} // namespace liuyunbin

#endif

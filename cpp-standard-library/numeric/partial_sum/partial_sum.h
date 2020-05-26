#ifndef CPP_STANDARD_LIBRARY_NUMERIC_PARTIAL_SUM_H_
#define CPP_STANDARD_LIBRARY_NUMERIC_PARTIAL_SUM_H_

#include <utility>

namespace liuyunbin {

/*
 * partial_sum()
 */

template <typename InputIt, typename OutputIt>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first) {
  if (first == last)
    return d_first;
  auto value = *first;
  *d_first++ = value;
  while (++first != last) {
    value = std::move(value) + *first;
    *d_first++ = value;
  }
  return d_first;
}

template <typename InputIt, typename OutputIt, typename BinaryOperation>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first,
                     BinaryOperation op) {
  if (first == last)
    return d_first;
  auto value = *first;
  *d_first++ = value;
  while (++first != last) {
    value = op(std::move(value), *first);
    *d_first++ = value;
  }
  return d_first;
}

} // namespace liuyunbin

#endif

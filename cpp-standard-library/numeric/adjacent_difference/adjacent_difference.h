#ifndef CPP_STANDARD_LIBRARY_NUMERIC_ADJACENT_DIFFERENCE_H_
#define CPP_STANDARD_LIBRARY_NUMERIC_ADJACENT_DIFFERENCE_H_

#include <utility>

namespace liuyunbin {

/*
 * adjacent_difference()
 */
template <typename InputIt, typename OutputIt>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first) {
  if (first == last)
    return d_first;
  auto previous_value = *first;
  *d_first++ = previous_value;
  while (++first != last) {
    *d_first++ = *first - std::move(previous_value);
    previous_value = *first;
  }
  return d_first;
}

template <typename InputIt, typename OutputIt, typename BinaryOperation>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first,
                             BinaryOperation op) {
  if (first == last)
    return d_first;
  auto previous_value = *first;
  *d_first++ = previous_value;
  while (++first != last) {
    *d_first++ = op(*first, std::move(previous_value));
    previous_value = *first;
  }
  return d_first;
}

} // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_NUMERIC_ACCUMULATE_H_
#define CPP_STANDARD_LIBRARY_NUMERIC_ACCUMULATE_H_

#include <utility>

namespace liuyunbin {

/*
 *   accumulate()
 */
template <typename InputIt, typename T>
T accumulate(InputIt first, InputIt last, T init) {
  while (first != last)
    init = std::move(init) + *first++;
  return init;
}

template <typename InputIt, typename T, typename BinaryOperation>
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op) {
  while (first != last)
    init = op(std::move(init), *first++);
  return init;
}

} // namespace liuyunbin

#endif

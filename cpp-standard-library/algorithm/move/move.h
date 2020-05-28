#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_MOVE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_MOVE_H_

#include <utility>

namespace liuyunbin {

/*
 * move
 */
template <typename InputIt, typename OutputIt>
OutputIt move(InputIt first, InputIt last, OutputIt d_first) {
  while (first != last)
    *d_first++ = std::move(*first++);
  return d_first;
}

} // namespace liuyunbin

#endif

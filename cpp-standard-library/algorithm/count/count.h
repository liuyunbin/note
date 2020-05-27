#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_COUNT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_COUNT_H_

#include <iterator>

namespace liuyunbin {

/*
 * count
 */
template <typename InputIt, typename T>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T &value) {
  typename std::iterator_traits<InputIt>::difference_type n = 0;
  while (first != last)
    if (*first++ == value)
      ++n;
  return n;
}

} // namespace liuyunbin

#endif

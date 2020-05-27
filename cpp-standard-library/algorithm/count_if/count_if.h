#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_COUNT_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_COUNT_IF_H_

#include <iterator>

namespace liuyunbin {

/*
 * count_if
 */
template <typename InputIt, typename UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p) {
  typename std::iterator_traits<InputIt>::difference_type n = 0;
  while (first != last)
    if (p(*first++))
      ++n;
  return n;
}

} // namespace liuyunbin

#endif

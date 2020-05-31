#ifndef CPP_STANDARD_LIBRARY_ITERATOR_DISTANCE_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_DISTANCE_H_

#include <iterator>

namespace liuyunbin {

/***********************************
 *                                 *
 *           distance              *
 *                                 *
 ***********************************/

namespace detail {

template <typename InputIt>
typename std::iterator_traits<InputIt>::difference_type
__distance(InputIt first, InputIt last, std::input_iterator_tag) {
  typename std::iterator_traits<InputIt>::difference_type n = 0;
  while (first != last) {
    ++n;
    ++first;
  }
  return n;
}

template <typename RandomAccessIt, typename Distance>
typename std::iterator_traits<RandomAccessIt>::difference_type
__distance(RandomAccessIt first, RandomAccessIt last,
           std::random_access_iterator_tag) {
  return last - first;
}

}  // namespace detail

template <typename InputIt>
typename std::iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last) {
  return detail::__distance(
      first, last, typename std::iterator_traits<InputIt>::iterator_category());
}

}  // namespace liuyunbin

#endif

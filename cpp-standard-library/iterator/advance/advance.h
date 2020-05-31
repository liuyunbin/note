#ifndef CPP_STANDARD_LIBRARY_ITERATOR_ADVANCE_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_ADVANCE_H_

#include <iterator>

namespace liuyunbin {

/***********************************
 *                                 *
 *           advance               *
 *                                 *
 ***********************************/

namespace detail {

template <typename InputIt, typename Distance>
void __advance(InputIt& it, Distance n, std::input_iterator_tag) {
  while (n-- != 0) ++it;
}

template <typename BidirectionalIt, typename Distance>
void __advance(BidirectionalIt& it, Distance n, std::bidirectional_iterator_tag) {
  if (n == 0) return;
  if (n > 0)
    while (n-- > 0) ++it;
  else
    while (n++ < 0) --it;
}

template <typename RandomAccessIt, typename Distance>
void __advance(RandomAccessIt& it, Distance n, std::random_access_iterator_tag) {
  it += n;
}

}  // namespace detail

template <typename InputIt, typename Distance>
void advance(InputIt& it, Distance n) {
  detail::__advance(
      it, n, typename std::iterator_traits<InputIt>::iterator_category());
}

}  // namespace liuyunbin

#endif

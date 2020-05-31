#ifndef CPP_STANDARD_LIBRARY_ITERATOR_PREV_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_PREV_H_

#include <iterator>

namespace liuyunbin {

/*******************************************
 *                                         *
 *                prev                     *
 *                                         *
 *******************************************/

template <typename BidirectionalIt>
BidirectionalIt prev(
    BidirectionalIt it,
    typename std::iterator_traits<BidirectionalIt>::difference_type n =
        1) {
  std::advance(it, -n);
  return it;
}

}  // namespace liuyunbin

#endif

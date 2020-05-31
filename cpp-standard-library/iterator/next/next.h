#ifndef CPP_STANDARD_LIBRARY_ITERATOR_NEXT_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_NEXT_H_

#include <iterator>

namespace liuyunbin {

/*******************************************
 *                                         *
 *                next                     *
 *                                         *
 *******************************************/

template <typename InputIt>
InputIt next(
    InputIt it,
    typename std::iterator_traits<InputIt>::difference_type n = 1) {
  std::advance(it, n);
  return it;
}

}  // namespace liuyunbin

#endif

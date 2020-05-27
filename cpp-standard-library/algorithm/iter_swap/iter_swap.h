#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_ITER_SWAP_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_ITER_SWAP_H_

#include <utility>

namespace liuyunbin {

/*
 * iter_swap
 */
template <typename ForwardIt1, typename ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b) {
  using std::swap;
  swap(*a, *b);
}

} // namespace liuyunbin

#endif

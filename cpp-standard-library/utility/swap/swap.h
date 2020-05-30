#ifndef CPP_STANDARD_LIBRARY_UTILITY_SWAP_H_
#define CPP_STANDARD_LIBRARY_UTILITY_SWAP_H_

#include <iostream>

namespace liuyunbin {

/*******************************************
 *                                         *
 *               swap                      *
 *                                         *
 *******************************************/

template <typename T>
void swap(T& a, T& b) noexcept {
  T temp = std::move(a);
  a = std::move(b);
  b = std::move(temp);
}

template <typename T, std::size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept {
  using std::swap;
  for (std::size_t i = 0; i != N; ++i)
    swap(a[i], b[i]);
}

}  // namespace liuyunbin

#endif

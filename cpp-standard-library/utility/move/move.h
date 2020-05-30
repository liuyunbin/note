#ifndef CPP_STANDARD_LIBRARY_UTILITY_MOVE_H_
#define CPP_STANDARD_LIBRARY_UTILITY_MOVE_H_

#include <type_traits>

namespace liuyunbin {

/*******************************************
 *                                         *
 *               move                      *
 *                                         *
 *******************************************/

// Universal Reference
template <typename T>
auto move(T&& t) noexcept -> typename std::remove_reference<T>::type&& {
  using return_type = typename std::remove_reference<T>::type&&;
  return static_cast<return_type>(t);
}

}  // namespace liuyunbin

#endif

#ifndef CPP_STANDARD_LIBRARY_UTILITY_FORWARD_H_
#define CPP_STANDARD_LIBRARY_UTILITY_FORWARD_H_

#include <type_traits>

namespace liuyunbin {

/*******************************************
 *                                         *
 *              forward                    *
 *                                         *
 *******************************************/

template <typename T>
T&& forward(typename std::remove_reference<T>::type& t) noexcept {
  return static_cast<T&&>(t);
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
  return static_cast<T&&>(t);
}

}  // namespace liuyunbin

#endif

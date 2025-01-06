#ifndef CPP_STANDARD_LIBRARY_UTILITY_H_
#define CPP_STANDARD_LIBRARY_UTILITY_H_

#include <type_traits>
#include <iostream>
#include <iterator>
#include <utility>

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

/********************************************
 *                                          *
 *                pair                      *
 *                                          *
 ********************************************/

template <typename T1, typename T2>
struct pair {
  using first_type = T1;
  using second_type = T2;

  T1 first;
  T2 second;

  /*******************************
   *                             *
   *          constructor        *
   *                             *
   *******************************/

  pair() : first(), second() {}

  pair(const T1& x, const T2& y) : first(x), second(y) {}

  // Universal Reference
  template <typename U1, typename U2>
  pair(U1&& x, U2&& y) : first(std::forward<U1>(x)), second(std::forward<U2>(y)) {}

  template <typename U1, typename U2>
  pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

  template <typename U1, typename U2>
  pair(pair<U1, U2>&& p) : first(std::move(p.first)), second(std::move(p.second)) {}

  // copy constructor
  pair(const pair& p) : first(p.first), second(p.second) {}

  // move constructor
  pair(pair&& p) noexcept : first(std::move(p.first)), second(std::move(p.second)) {}

  /*********************************
   *                               *
   *              =                *
   *                               *
   *********************************/

  // copy-assignment operator
  pair& operator=(const pair& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  // move-assignment operator
  pair& operator=(pair&& other) noexcept {
    first = std::move(other.first);
    second = std::move(other.second);
    return *this;
  }

  template <typename U1, typename U2>
  pair& operator=(const pair<U1, U2>& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  template <typename U1, typename U2>
  pair& operator=(pair<U1, U2>&& other) {
    first = std::move<U1>(other.first);
    second = std::move<U2>(other.second);
    return *this;
  }

  void swap(pair& other) {
    using std::swap;
    swap(first, other.first);
    swap(second, other.second);
  }
};

/********************************************
 *                                          *
 *                make_pair                 *
 *                                          *
 *                   swap                   *
 *                                          *
 ********************************************/

template <typename T1, typename T2>
pair<T1, T2> make_pair(T1&& first, T2&& second) {  // Universal Reference
  return pair<T1, T2>(std::forward<T1>(first), std::forward<T2>(second));
}

template <typename T1, typename T2>
void swap(pair<T1, T2>& left, pair<T1, T2>& right) {
  left.swap(right);
}

/********************************************
 *                                          *
 *       ==    !=   <    <=    >    >=      *
 *                                          *
 ********************************************/

template <typename T1, typename T2>
bool operator==(const pair<T1, T2>& left, const pair<T1, T2>& right) {
  return left.first == right.first && left.second == right.second;
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2>& left, const pair<T1, T2>& right) {
  return !(left == right);
}

template <typename T1, typename T2>
bool operator<(const pair<T1, T2>& left, const pair<T1, T2>& right) {
  if (left.first < right.first) return true;
  if (right.first < left.first) return false;
  return left.second < right.second;
}

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2>& left, const pair<T1, T2>& right) {
  return !(right < left);
}

template <typename T1, typename T2>
bool operator>(const pair<T1, T2>& left, const pair<T1, T2>& right) {
  return right < left;
}

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2>& left, const pair<T1, T2>& right) {
  return !(left < right);
}

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

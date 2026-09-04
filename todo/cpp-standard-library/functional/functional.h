#ifndef CPP_STANDARD_LIBRARY_FUNCTIONAL_H_
#define CPP_STANDARD_LIBRARY_FUNCTIONAL_H_

#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>

namespace liuyunbin {

/*******************************
 *                             *
 *        unary_function       *
 *                             *
 *       binary_function       *
 *                             *
 *******************************/

template <typename Arg, typename Result>
struct unary_function {
  using argument_type = Arg;
  using   result_type = Result;
};

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
  using  first_argument_type = Arg1;
  using second_argument_type = Arg2;
  using          result_type = Result;
};

/*************************************
 *                                   *
 *               plus                *
 *               minus               *
 *               multiplies          *
 *               divides             *
 *               modulus             *
 *               negate              *
 *                                   *
 *************************************/

template <typename T = void>
struct plus : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left + right;
  }
};

template <typename T = void>
struct minus : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left - right;
  }
};

template <typename T = void>
struct multiplies : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left * right;
  }
};

template <typename T = void>
struct divides : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left / right;
  }
};

template <typename T = void>
struct modulus : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left % right;
  }
};

template <typename T = void>
struct negate : public unary_function<T, T> {
  constexpr T operator()(const T& arg) const { return -arg; }
};

/********************************************
 *                                          *
 *               equal_to                   *
 *               not_equal_to               *
 *               greater                    *
 *               greater_equal              *
 *               less                       *
 *               less_equal                 *
 *                                          *
 ********************************************/

template <typename T = void>
struct equal_to : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left == right;
  }
};

template <typename T = void>
struct not_equal_to : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left != right;
  }
};

template <typename T = void>
struct greater : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left > right;
  }
};

template <typename T = void>
struct greater_equal : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left >= right;
  }
};

template <typename T = void>
struct less : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left < right;
  }
};

template <typename T = void>
struct less_equal : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left <= right;
  }
};

/********************************
 *                              *
 *         logical_add          *
 *         logical_or           *
 *         logical_not          *
 *                              *
 ********************************/

template <typename T = void>
struct logical_add : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left && right;
  }
};

template <typename T = void>
struct logical_or : public binary_function<T, T, T> {
  constexpr bool operator()(const T& left, const T& right) const {
    return left || right;
  }
};

template <typename T = void>
struct logical_not : public unary_function<T, T> {
  constexpr bool operator()(const T& arg) const { return !arg; }
};

/********************************
 *                              *
 *         bit_add              *
 *         bit_or               *
 *         bit_xor              *
 *         bit_not              *
 *                              *
 ********************************/

template <typename T = void>
struct bit_add : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left & right;
  }
};

template <typename T = void>
struct bit_or : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left | right;
  }
};

template <typename T = void>
struct bit_xor : public binary_function<T, T, T> {
  constexpr T operator()(const T& left, const T& right) const {
    return left ^ right;
  }
};

template <typename T = void>
struct bit_not : public unary_function<T, T> {
  constexpr T operator()(const T& arg) const { return ~arg; }
};

/****************************
 *                          *
 *         identity         *   not STL
 *                          *
 ****************************/

template <typename T = void>
struct identity : public unary_function<T, T> {
  constexpr const T& operator()(const T& x) const { return x; }
};

/****************************
 *                          *
 *        select1st         *   not STL
 *                          *
 ****************************/

template <typename Pair = void>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
  constexpr const typename Pair::first_type& operator()(const Pair& x) const {
    return x.first;
  }
};

/****************************
 *                          *
 *        select2nd         *   not STL
 *                          *
 ****************************/

template <typename Pair = void>
struct select2nd : public unary_function<Pair, typename Pair::second_type> {
  constexpr const typename Pair::second_type& operator()(const Pair& x) const {
    return x.second;
  }
};

/*******************************
 *                             *
 *              hash           *
 *                             *
 *******************************/

template <typename Key>
struct hash : public unary_function<Key, std::size_t> {};

template <>
struct hash<char*> {
  std::size_t operator()(const char* s) const {
    std::size_t h = 0;
    while (*s != '\0') h = h * 5 + *s++;
    return h;
  }
};

template <>
struct hash<const char*> {
  std::size_t operator()(const char* s) const {
    std::size_t h = 0;
    while (*s != '\0') h = h * 5 + *s++;
    return h;
  }
};

template <>
struct hash<char> {
  std::size_t operator()(char x) const { return x; }
};

template <>
struct hash<signed char> {
  std::size_t operator()(signed char x) const { return x; }
};

template <>
struct hash<unsigned char> {
  std::size_t operator()(unsigned char x) const { return x; }
};

template <>
struct hash<short> {
  std::size_t operator()(short x) const { return x; }
};

template <>
struct hash<unsigned short> {
  std::size_t operator()(unsigned short x) const { return x; }
};

template <>
struct hash<int> {
  std::size_t operator()(int x) const { return x; }
};

template <>
struct hash<unsigned int> {
  std::size_t operator()(unsigned int x) const { return x; }
};

template <>
struct hash<long> {
  std::size_t operator()(long x) const { return x; }
};

template <>
struct hash<unsigned long> {
  std::size_t operator()(unsigned long x) const { return x; }
};

template <>
struct hash<long long> {
  std::size_t operator()(long long x) const { return x; }
};

template <>
struct hash<unsigned long long> {
  std::size_t operator()(unsigned long long x) const { return x; }
};

}  // namespace liuyunbin

#endif

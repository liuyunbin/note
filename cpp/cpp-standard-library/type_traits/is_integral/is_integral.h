#ifndef CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_INTEGRAL_H_
#define CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_INTEGRAL_H_

#include <type_traits>

namespace liuyunbin {

template <typename T> struct __is_integral : std::false_type{};

template <> struct __is_integral<bool> : std::true_type{};

template <> struct __is_integral<char> : std::true_type{};

template <> struct __is_integral<signed char> : std::true_type{};

template <> struct __is_integral<unsigned char> : std::true_type{};

template <> struct __is_integral<short> : std::true_type{};

template <> struct __is_integral<unsigned short> : std::true_type{};

template <> struct __is_integral<int> : std::true_type{};

template <> struct __is_integral<unsigned int> : std::true_type{};

template <> struct __is_integral<long> : std::true_type{};

template <> struct __is_integral<unsigned long> : std::true_type{};

template <> struct __is_integral<long long> : std::true_type{};

template <> struct __is_integral<unsigned long long> : std::true_type{};

template <typename T>
struct is_integral : __is_integral<typename std::remove_cv<T>::type> {};

} // namespace liuyunbin

#endif

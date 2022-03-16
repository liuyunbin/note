#ifndef CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_CONVERTIBLE_H_
#define CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_CONVERTIBLE_H_

#include <type_traits>

namespace liuyunbin {

template <typename T>
void test_convertion(T);

template <typename From, 
         typename To, 
         typename = decltype(test_convertion<To>(std::declval<From>()))>
std::true_type test(int);

template <typename From, typename To>
std::false_type test(...);

template <typename From, 
         typename To, 
         bool = std::is_void<From>::value && std::is_void<To>::value,
         bool = std::is_array<To>::value || std::is_function<To>::value>
struct is_convertible : std::false_type {};

template <typename From, typename To>
struct is_convertible<From, To, true, false> : std::true_type {};

template <typename From, typename To>
struct is_convertible<From, To, false, false> : decltype(test<From, To>(1))
{};

template <typename T>
void test_noexcept(T) noexcept;

template <typename From, typename To, bool = std::is_void<From>::value>
struct is_nothrow_convertible_helper : std::true_type {};

template <typename From, typename To>
struct is_nothrow_convertible_helper<From, To, false>
    : std::integral_constant<bool, noexcept(test_noexcept<To>(
                                       std::declval<From>()))> {};

template <typename From, typename To, bool = is_convertible<From, To>::value>
struct is_nothrow_convertible : std::false_type {};

template <typename From, typename To>
struct is_nothrow_convertible<From, To, true>
    : is_nothrow_convertible_helper<From, To> {};

} // namespace liuyunbin

#endif

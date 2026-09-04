#ifndef CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_BASE_OF_H_
#define CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_BASE_OF_H_

#include <type_traits>

namespace liuyunbin {

template <typename...> using void_t = void; 

template<typename T> std::true_type  test(const volatile T*);
template<typename T> std::false_type test(const volatile void*);

template <typename B, typename D>
using test_same_or_public_inheritance = decltype(test<B>(std::declval<D*>()));

template <typename B, typename D, typename = void>
struct is_base_of_helper : public std::true_type {}; // 处理私有继承 或 受保护继承

template <typename B, typename D>
struct is_base_of_helper<B, D, void_t<test_same_or_public_inheritance<B, D>>> :
  public test_same_or_public_inheritance<B, D> 
{};

template <typename B, typename D>
struct is_base_of 
  : public std::conditional <
  std::is_class<B>::value && std::is_class<D>::value,
  is_base_of_helper<B, D>,
  std::false_type>::type 
{};

} // namespace liuyunbin

#endif

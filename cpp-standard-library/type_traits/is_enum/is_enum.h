#ifndef CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_ENUM_H_
#define CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_ENUM_H_

#include <type_traits>

namespace liuyunbin {

template <typename T>
std::true_type test_is_class_or_union(int T::*);

template <typename T>
std::false_type test_is_class_or_union(...);

template <typename T>
struct is_class_or_union : decltype(test_is_class_or_union<T>(nullptr)) {};

template <typename T>
struct is_enum
    : public std::integral_constant<
          bool, !std::is_void<T>::value && !std::is_null_pointer<T>::value &&
                    !std::is_integral<T>::value &&
                    !std::is_floating_point<T>::value &&
                    !std::is_array<T>::value && !std::is_function<T>::value &&
                    !std::is_pointer<T>::value &&
                    !std::is_reference<T>::value &&
                    !std::is_member_pointer<T>::value &&
                    !is_class_or_union<T>::value> {};

} // namespace liuyunbin

#endif

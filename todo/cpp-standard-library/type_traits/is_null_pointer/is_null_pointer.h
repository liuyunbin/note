#ifndef CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_NULL_POINTER_H_
#define CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_NULL_POINTER_H_

#include <type_traits>

namespace liuyunbin {

template <typename T>
struct is_null_pointer
    : std::is_same<std::nullptr_t, typename std::remove_cv<T>::type> {};

} // namespace liuyunbin

#endif


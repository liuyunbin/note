#ifndef CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_VOID_H_
#define CPP_STANDARD_LIBRARY_TYPE_TRAITS_IS_VOID_H_

#include <type_traits>

namespace liuyunbin {

template <typename T>
struct is_void : std::is_same<void, typename std::remove_cv<T>::type> {};

} // namespace liuyunbin

#endif

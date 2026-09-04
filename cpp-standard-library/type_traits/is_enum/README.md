
```
template <typename T>
is_enum;
```

如果 `T` 为 `enum`，`enum class` 或 包含 `CV` 限定的上述类型
则 `std::is_enum<T>::value` 为 `true`，否则为 `false`

接下来，我们来实现它，使用排除法，即，将其它类型都排除了，剩下的就是枚举类型

首先，我们无法精确判断是类还是结构体，但可以使用重载决议判断是 类 或 共同体

```
template <typename T>
std::true_type test_is_class_or_union(int T::*);

template <typename T>
std::false_type test_is_class_or_union(...);

template <typename T>
struct is_class_or_union : decltype(test_is_class_or_union<T>(nullptr)) {};
```

其它类型都可以手动实现，所以，在此直接调用 `C++` 标准库

```
template <typename T>
struct is_enum : public std::integral_constant<bool, 
  !std::is_void<T>::value &&
  !std::is_null_pointer<T>::value &&
  !std::is_integral<T>::value &&
  !std::is_floating_point<T>::value &&
  !std::is_array<T>::value &&
  !std::is_function<T>::value &&
  !std::is_pointer<T>::value &&
  !std::is_reference<T>::value &&
  !std::is_member_pointer<T>::value &&
  !::is_class_or_union<T>::value>
{};
```

完整代码及其测试，参见源文件


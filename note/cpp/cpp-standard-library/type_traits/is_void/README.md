
```
template <typename T>
is_void;
```

如果 `T` 为 `void`，`void const`，`void volatile` 或 `void const volatile`，
则 `std::is_void<T>::value` 为 `true`，否则为 `false`

接下来，一步一步实现，最直接的方法是直接对每一种情况偏特化，

```
template <typename T>
struct is_void : std::false_type {};

template <>
struct is_void<void> : std::true_type {};

template <>
struct is_void<void const> : std::true_type {};

template <>
struct is_void<void volatile> : std::true_type {};

template <>
struct is_void<void const volatile> : std::true_type {};
```

但是，有点太繁琐了，我们可以将 `T` 去的 `CV` 属性后，和 `void` 比较即可

```
template <typename T>
struct is_void : std::is_same<void, typename std::remove_cv<T>::type> {};
```

在 C++14 及其之后，可以更加简化它，

```
template <typename T>
struct is_void : std::is_same<void, std::remove_cv_t<T>> {};
```


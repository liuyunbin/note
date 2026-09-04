
```
template <typename T>
is_null_pointer;
```

此结构体的实现方法和 `is_void` 类似，移除 `CV` 属性后，用 `std::is_same` 比较即可



#### 函数原型：
```
template <typename T>
const T &min(const T &lhs, const T &rhs);

template <typename T, typename Compare>
const T &min(const T &lhs, const T &rhs, Compare comp);

template <typename T>
T min(std::initializer_list<T> ilist);

template <typename T, typename Compare>
T min(std::initializer_list<T> ilist, Compare comp);
```

#### 函数说明：
* 该函数用于求指定参数的最小值

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename T>
std::pair<const T &, const T &>
minmax(const T &lhs, const T &rhs);

template <typename T, typename Compare>
std::pair<const T &, const T &>
minmax(const T &lhs, const T &rhs, Compare comp);

template <typename T>
std::pair<T, T>
minmax(std::initializer_list<T> ilist);

template <typename T, typename Compare>
std::pair<T, T>
minmax(std::initializer_list<T> ilist, Compare comp);
```

#### 函数说明：
* 该函数用于求指定区间的最小值和最大值

详细内容见 函数实现及其注释


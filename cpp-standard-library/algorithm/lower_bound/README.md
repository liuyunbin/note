
#### 函数原型：
```
template <typename ForwardIt, typename T, typename Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value, Compare comp);

template <typename ForwardIt, typename T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value);
```

#### 函数说明：
* 该函数返回在指定的有序区间内，第一个大于等于 value 的位置

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename ForwardIt, typename T, typename Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value, Compare comp);

template <typename ForwardIt, typename T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value);
```

#### 函数说明：
* 该函数返回在指定的有序区间内，第一个大于 value 的位置

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


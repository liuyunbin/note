
#### 函数原型：
```
template <typename ForwardIt, typename T, typename Compare>
bool binary_search(ForwardIt first, ForwardIt last, const T &value, Compare comp);

template <typename ForwardIt, typename T>
bool binary_search(ForwardIt first, ForwardIt last, const T &value);
```

#### 函数说明：
* 该函数用于判断指有序区间内是否存在元素 value

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


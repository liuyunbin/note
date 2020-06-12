
#### 函数原型：
```
template <typename ForwardIt>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last);

template <typename ForwardIt, typename BinaryPredicate>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p);
```

#### 函数说明：
* 该函数用于查找在指定区间内是否存在连续的两个相等元素

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


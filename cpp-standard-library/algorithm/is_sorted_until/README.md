
#### 函数原型：
```
template <typename ForwardIt, typename Compare>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp);

template <typename ForwardIt>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last);
```

#### 函数说明：
* 该函数用于查找从头开始满足已排序的子区间

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


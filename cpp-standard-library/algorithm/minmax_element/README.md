
#### 函数原型：
```
template <typename ForwardIt>
std::pair<ForwardIt, ForwardIt>
minmax_element(ForwardIt first, ForwardIt last);

template <typename ForwardIt, typename Compare>
std::pair<ForwardIt, ForwardIt>
minmax_element(ForwardIt first, ForwardIt last, Compare comp);
```

#### 函数说明：
* 该函数用于求指定区间的最小值和最大值

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


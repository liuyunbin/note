
#### 函数原型：
```
template <typename ForwardIt, typename Compare>
void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last, Compare comp);

template <typename ForwardIt>
void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last);
```

#### 函数说明：
* 该函数用于原地合并两个有序区间

#### 模板参数要求：
* C++11 要求 至少是双向迭代器，但我觉得 只要满足条件，前向迭代器就可以

详细内容见 函数实现及其注释


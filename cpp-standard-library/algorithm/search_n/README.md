
#### 函数原型：
```
template <typename ForwardIt, typename Size, typename T>
ForwardIt
search_n(ForwardIt first, ForwardIt last, Size count, const T &value);

template <typename ForwardIt, typename Size, typename T, typename BinaryPredicate>
ForwardIt
search_n(ForwardIt first, ForwardIt last, Size count, const T &value, BinaryPredicate p);
```

#### 函数说明：
* 该函数用于查找是否前一个区间的某个子区间是否存在连续的 count 个元素 value，如果存在，返回，第一个子区间的第一个元素的迭代器

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


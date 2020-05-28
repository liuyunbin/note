
#### 函数原型：
```
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1
find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2);

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1
find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, BinaryPredicate p);
```

#### 函数说明：
* 该函数用于查找是否前一个区间的某个子区间和后一个区间的元素相同，如果存在，返回，最后一个子区间的第一个元素的迭代器
* 可以通过区分是否是双向迭代器来优化

详细内容见 函数实现及其注释


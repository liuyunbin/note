
#### 函数原型：
```
template <typename InputIt, typename ForwardIt>
InputIt
find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2);

template <typename InputIt, typename ForwardIt, typename BinaryPredicate>
InputIt
find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2, BinaryPredicate p);
```

#### 函数说明：
* 该函数用于查找对于第一个区间内的元素，如果在第二个区间内的出现过，则返回第一个迭代器的位置

详细内容见 函数实现及其注释


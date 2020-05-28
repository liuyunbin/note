
#### 函数原型：
```
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt transform(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p);

template <typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryPredicate>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryPredicate p);
```

#### 函数说明：
* 该函数用于对指定区间内的元素进行转化

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename InputIt, typename OutputIt>
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first);

template <typename InputIt, typename OutputIt, typename BinaryPredicate>
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first, BinaryPredicate p);
```

#### 函数说明：
* 该函数用于去除指定区间内相同的相邻元素，并将结果拷入对应区间

详细内容见 函数实现及其注释


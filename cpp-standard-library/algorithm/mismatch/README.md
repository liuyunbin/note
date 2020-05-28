
#### 函数原型：
```
template <typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2);

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate op);

template <typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate op);
```

#### 函数说明：
* 该函数用于返回两个区间内首个不相等的值对应的迭代器

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate op);

template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);

// C++14
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate op);

template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
```

#### 函数说明：
* 该函数用于比较指定的区间是否相等

详细内容见 函数实现及其注释


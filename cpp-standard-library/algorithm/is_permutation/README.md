
#### 函数原型：
```
template <typename ForwardIt1, typename ForwardIt2, typename Compare>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, Compare comp);

template <typename ForwardIt1, typename ForwardIt2>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2);

template <typename ForwardIt1, typename ForwardIt2, typename Compare>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, Compare comp);

template <typename ForwardIt1, typename ForwardIt2>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2);
```

#### 函数说明：
* 该函数用于判断第一个区间能否通过交换转化为第二个区间

详细内容见 函数实现及其注释


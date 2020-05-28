
#### 函数原型：
```
template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp);

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first);
```

#### 函数说明：
* 该函数用于合并两个有序区间

详细内容见 函数实现及其注释


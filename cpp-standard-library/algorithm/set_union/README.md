
#### 函数原型：
```
template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp);

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first);
```

#### 函数说明：
* 求两个有序集合的并集

#### 模板参数要求：
* 至少是输入迭代器 输入迭代器 输出迭代器

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename InputIt, typename RandomAccessIt, typename Compare>
RandomAccessIt partial_sort_copy(InputIt first, InputIt last, RandomAccessIt d_first, RandomAccessIt d_last, Compare comp);

template <typename InputIt, typename RandomAccessIt>
RandomAccessIt partial_sort_copy(InputIt first, InputIt last, RandomAccessIt d_first, RandomAccessIt d_last);
```

#### 函数说明：
* 该函数用部分排序，并将结果存入指定区间

#### 模板参数要求：
* 至少是输入迭代器 随机迭代器

详细内容见 函数实现及其注释


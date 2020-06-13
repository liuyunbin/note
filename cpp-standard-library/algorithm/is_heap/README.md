
#### 函数原型：
```
template <typename RandomAccessIt, typename Compare>
bool is_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);

template <typename RandomAccessIt>
bool is_heap(RandomAccessIt first, RandomAccessIt last);
```

#### 函数说明：
* 该函数用于判断指定区间是否满足堆

#### 模板参数要求：
* 要求是是随机迭代器

详细内容见 函数实现及其注释


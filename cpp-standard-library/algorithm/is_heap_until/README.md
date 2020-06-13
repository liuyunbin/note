
#### 函数原型：
```
template <typename RandomAccessIt, typename Compare>
RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last, Compare comp);

template <typename RandomAccessIt>
RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last);
```

#### 函数说明：
* 该函数用于查找从头开始满足堆的子区间

#### 模板参数要求：
* 要求是是随机迭代器

详细内容见 函数实现及其注释


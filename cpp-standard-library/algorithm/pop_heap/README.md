
#### 函数原型：
```
template <typename RandomAccessIt, typename Compare>
void pop_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);

template <typename RandomAccessIt>
void pop_heap(RandomAccessIt first, RandomAccessIt last);
```

#### 函数说明：
* 该函数用于删除堆顶元素，并将放在最后一个位置

#### 模板参数要求：
* 要求是随机迭代器

详细内容见 函数实现及其注释


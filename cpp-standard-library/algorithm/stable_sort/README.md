
#### 函数原型：
```
template <typename RandomAccessIt, typename Compare>
void stable_sort(RandomAccessIt first, RandomAccessIt last, Compare comp);

template <typename RandomAccessIt>
void stable_sort(RandomAccessIt first, RandomAccessIt last);
```

#### 函数说明：
* 该函数用于对指定区间进行排序，保持元素的相对位置

#### 模板参数要求：
* 要求是随机迭代器

详细内容见 函数实现及其注释


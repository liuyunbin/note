
#### 函数原型：
```
template <typename RandomAccessIt, typename Compare>
void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last, Compare comp);

template <typename RandomAccessIt>
void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last);
```

#### 函数说明：
* 该函数使得第 nth 个元素的元素和排好序的位置的元素相同，且，在它之前的元素都小于等于它，在它之后的元素都大于等于它

#### 模板参数要求：
* 要求是随机迭代器

详细内容见 函数实现及其注释


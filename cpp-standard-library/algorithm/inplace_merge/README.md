
#### 函数原型：
```
template <typename BidirIt, typename Compare>
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last, Compare comp);

template <typename BidirIt>
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last);
```

#### 函数说明：
* 该函数用于原地合并两个有序区间

#### 模板参数要求：
* 至少是双向迭代器

详细内容见 函数实现及其注释


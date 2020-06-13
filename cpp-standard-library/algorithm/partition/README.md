
#### 函数原型：
```
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p);
```

#### 函数说明：
* 调整指定区间内元素的顺序，使得，符合谓词的在前，不符合的在后

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


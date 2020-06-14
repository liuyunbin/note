
#### 函数原型：
```
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt stable_partition(ForwardIt first, ForwardIt last, UnaryPredicate p);
```

#### 函数说明：
* 调整指定区间内元素的顺序，使得，符合谓词的在前，不符合的在后，保持元素的相对位置

#### 模板参数要求：
* C++11 要求至少是双向迭代器，但我觉得用 前向迭代器 就可以

详细内容见 函数实现及其注释


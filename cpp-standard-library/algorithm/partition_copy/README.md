
#### 函数原型：
```
template <typename InputIt, typename OutputIt1, typename OutputIt2, typename UnaryPredicate>
std::pair<OutputIt1, OutputIt2>
partition_copy(InputIt first, InputIt last, OutputIt1 d_first_true, OutputIt2 d_first_false, UnaryPredicate p);
```

#### 函数说明：
* 对于指定区间内的元素，符合谓词的拷贝在第二个区间，不符合的拷贝在第三个区间

#### 模板参数要求：
* 至少是输入迭代器 输出迭代器 输出迭代器

详细内容见 函数实现及其注释


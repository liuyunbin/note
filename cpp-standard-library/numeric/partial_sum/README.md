
#### 函数原型：
```
template<typename InputIt, typename OutputIt>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first);

template<typename InputIt, typename OutputIt, typename BinaryOperation>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first, BinaryOperation op);
```

#### 函数说明：
* 该函数用于求指定区间的部分和，可使用 std::move 提高效率

#### 模板参数要求：
* 至少是输入迭代器 和 输出迭代器

详细内容见 函数实现及其注释


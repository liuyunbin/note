
#### 函数原型：
```
template <typename InputIt, typename T>
T accumulate(InputIt first, InputIt last, T init);

template <typename InputIt, typename T, typename BinaryOperation>
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op);
```

#### 函数说明：
* 该函数用于求指定区间的值的和，可使用 std::move 提高效率

#### 模板参数要求：
* 至少是输入迭代器

详细内容见 函数实现及其注释


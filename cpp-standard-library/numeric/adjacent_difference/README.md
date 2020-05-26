
#### 函数原型：
```
template <typename InputIt, typename OutputIt>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first);

template <typename InputIt, typename OutputIt, typename BinaryOperation>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first, BinaryOperation op);
```

#### 函数说明：
* 该函数用于求指定区间的值的差值，可使用 std::move 提高效率

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename InputIt1, typename InputIt2, typename T>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init);

template <typename InputIt1, typename InputIt2, typename T, typename BinaryOperation1, typename BinaryOperation2>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, BinaryOperation1 op1, BinaryOperation2 op2);
```

#### 函数说明：
* 该函数用于求指定区间的值的内积，可使用 std::move 提高效率

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename InputIt, typename OutputIt, typename T>
OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first, const T &old_value, const T &new_value);
```

#### 函数说明：
* 该函数用于替换区间内的指定元素，并将结果存入指定区间

#### 模板参数要求：
* 至少是输入迭代器 输出迭代器

详细内容见 函数实现及其注释



#### 函数原型：
```
template <typename InputIt, typename OutputIt, typename UnaryPredicate, typename T>
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p, const T &new_value);
```

#### 函数说明：
* 该函数用于替换区间内的满足指定谓词的元素，并将结果存入指定区间

详细内容见 函数实现及其注释


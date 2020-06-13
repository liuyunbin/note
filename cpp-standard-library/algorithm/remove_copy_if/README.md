
#### 函数原型：
```
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p);
```

#### 函数说明：
* 该函数用于移除区间内的满足指定谓词的元素，并将结果存入指定区间

#### 模板参数要求：
* 至少是输入迭代器 输出迭代器

详细内容见 函数实现及其注释


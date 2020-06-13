
#### 函数原型：
```
template <typename ForwardIt, typename UnaryPredicate, typename T>
void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, const T &new_value);
```

#### 函数说明：
* 该函数用于替换区间内的满足指定谓词的元素

#### 模板参数要求：
* 至少是前向迭代器

详细内容见 函数实现及其注释


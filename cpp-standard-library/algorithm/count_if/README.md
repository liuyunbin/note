
#### 函数原型：
```
template <typename InputIt, typename UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type count_if(InputIt first, InputIt last, UnaryPredicate p);
```

#### 函数说明：
* 该函数用于统计满足指定条件的元素的个数

#### 模板参数要求：
* 至少是输入迭代器

详细内容见 函数实现及其注释


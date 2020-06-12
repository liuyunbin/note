
#### 函数原型：
```
template <typename InputIt, typename T, typename Compare>
bool binary_search(InputIt first, InputIt last, const T &value, Compare comp);

template <typename InputIt, typename T>
bool binary_search(InputIt first, InputIt last, const T &value);
```

#### 函数说明：
* 该函数用于判断指有序区间内是否存在元素 value

#### 模板参数要求：
* C++11 要求至少是前向迭代器，但我觉得，只要满足条件，输入迭代器也可以

详细内容见 函数实现及其注释


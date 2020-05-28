
#### 函数原型：
```
template <typename InputIt1, typename InputIt2, typename Compare>
bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp);

template <typename InputIt1, typename InputIt2>
bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
```

#### 函数说明：
* 对于两个有序区间，判断第二个区间是否是第一个区间的子区间

详细内容见 函数实现及其注释


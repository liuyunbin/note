
#### 函数原型：
```
int memcmp(const void* lhs, const void* rhs, size_t count);
```

#### 函数说明：
* 比较 lhs 和 rhs 所指向数组的大小，最多比较 count 个字符，
* lhs 将转化为 unsigned char*
* rhs 将转化为 unsigned char*

#### 返回说明：
* 如果 lhs >  rhs，返回 1
* 如果 lhs == rhs，返回 0
* 如果 lhs <  rhs，返回 -1

#### 未定义的行为：
* lhs 或 rhs 所指向的数组的大小小于 count 且 查找的过程中使用超出了其范围

#### 优化：
* 如果，lhs 和 rhs 的值相同，则直接返回

详细内容见 函数实现及其注释


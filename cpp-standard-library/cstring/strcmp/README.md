
#### 函数原型：
```
int strcmp(const char* lhs, const char* rhs);
```

#### 函数说明：
比较 lhs 和 rhs 所指向字符串的大小，将转化为 unsigned char 比较

#### 参数要求：
* lhs 所指向的字符数组中一定包含 '\0'
* rhs 所指向的字符数组中一定包含 '\0'

#### 返回说明：
* 如果 lhs >  rhs，返回 1
* 如果 lhs == rhs，返回 0
* 如果 lhs <  rhs，返回 -1

#### 优化：
* 如果，lhs 和 rhs 的值相同，则无需比较，直接相同

详细内容见 函数实现及其注释



#### 函数原型：
```
int strncmp(const char* lhs, const char* rhs, size_t count);
``` 

#### 函数说明：
* 比较 lhs 和 rhs 所指向字符串的大小，将转化为 unsigned char 比较，最多比较 count 个字符

#### 参数要求：
* lhs 所指向的字符数组中不一定包含 '\0'
* rhs 所指向的字符数组中不一定包含 '\0'

#### 返回说明：
* 如果 lhs >  rhs，返回 1
* 如果 lhs == rhs，返回 0
* 如果 lhs <  rhs，返回 -1

#### 未定义的行为：
* 当 lhs 或 rhs 指向的字符数组不包括 '\0'，且比较时，超出其对应的数组大小

#### 优化：
* 如果，lhs 和 rhs 的值相同，则无需比较，直接相同
* 如果，count <= 0，则无需比较，直接相同

详细内容见 函数实现及其注释


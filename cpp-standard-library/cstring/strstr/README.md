
####  函数原型：
```
const char* strstr(const char* str, const char* target);
      char* strstr(      char* str, const char* target);
```

#### 函数说明：
* 查找 str 所指向的字符串中和 target 相同的子序列的首位置

#### 参数要求：
* str    所指向的字符数组中不一定包含 '\0'
* target 所指向的字符数组中一定包含 '\0'

#### 返回说明：
* 如果找到，返回首位置
* 否则，返回 NULL

#### 未定义的行为：
* 如果 str 所指向的字符数组不包括 '\0' 且 使用过程中超过了数组表示的范围

#### 优化：
* 如果，str 和 target 的值相同，则直接返回

详细内容见 函数实现及其注释



#### 函数原型：
```
const char* strpbrk(const char* dest, const char* breakset);
      char* strpbrk(      char* dest, const char* breakset);
```

#### 函数说明：
* 查找 dest 所指向的字符串中，第一个在 breakset 中出现的字符的位置

#### 参数要求：
* dest     所指向的字符数组中不一定包含 '\0'
* breakset 所指向的字符数组中不一定包含 '\0'

#### 返回说明：
* 如果找到，返回该字符的位置
* 否则，返回 NULL

#### 未定义的行为：
* 如果 dest 或 breakset 所指向的字符数组不包括 '\0' 且 使用过程中超过了数组表示的范围

#### 优化：
* 如果，dest 和 breakset 的值相同，则直接返回

详细内容见 函数实现及其注释


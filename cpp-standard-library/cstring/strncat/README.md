
#### 函数原型：
```
char* strncat(char* dest, const char* src, size_t count);
```

#### 函数说明：
将 src 所指向的字符串（包括 '\0'），添加到 dest 所指向的字符串之后，最多拷贝 count 个字符

#### 参数要求：
* src  所指向的字符数组不一定包含 '\0'
* dest 所指向的字符数组中一定包含 '\0'
* dest 所指向的字符数组的长度最小为：strlen(dest) + min(strlen(src), count) + 1
* src 和 dest 所指向的字符数组不能重叠

#### 返回说明：
* 返回 dest，dest 所指向的字符数组最终一定包含 '\0'

#### 特别说明：
* src 所指向的字符数组的长度小于 count，且 src 所指向的字符数组不包括 '\0'，是未定义的行为

#### 优化：
* 如果，count <= 0，则无需添加

详细内容见 函数实现及其注释


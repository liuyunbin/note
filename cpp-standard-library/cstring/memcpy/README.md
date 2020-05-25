 
#### 函数原型：
```
void* memcpy(void* dest, const void* src, size_t count);
```

#### 函数说明：
* 将 src 指向的数组复制到 dest 所指向的数组，复制 count 个字符
* dest 将转化为 unsigned char*
* src  将转化为 unsigned char*
* 本函数不能处理数组重叠的情况

#### 参数要求：
* dest 所指向的数组的大小最小为 count
* src  所指向的数组的大小最小为 count

#### 返回说明：
* 返回 dest

#### 优化：
* 如果，dest 和 src 的值相同，则直接返回

详细内容见 函数实现及其注释


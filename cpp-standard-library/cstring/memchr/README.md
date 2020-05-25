
#### 函数原型：
```
const void* memchr(const void* ptr, int ch, size_t count);
      void* memchr(      void* ptr, int ch, size_t count);
```

#### 函数说明：
* 查找 ptr 所指向的数组中的 ch 第一次出现的位置
* ptr 将转化为 unsigned char*
* ch  将转化为 unsigned char

#### 返回说明：
* 如果找到，返回 ch 第一次出现的位置
* 否则，返回 NULL

#### 未定义的行为：
* ptr 所指向的数组的大小小于 count 且 查找的过程中使用超出了 ptr 数组的范围

详细内容见 函数实现及其注释


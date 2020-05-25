
## 简介
头文件 `cstring` 里的函数实现也很简单，需要特别注意的情况有：

1. `strcpy`, `strncpy`, `strcat`, `strncat`, `memcpy` 不能处理数组重叠的情况
2. `strncpy` 返回的结果不一定是字符串
3. `strncpy` 可能会添加额外的 `'\0'`，导致效率低下
4. `strchr`, `strrchr` 将查找 `'\0'`
5. `strtok` 不是线程安全的 
6. `memmove` 可以处理数组重叠的情况 
7. 很多情况可以优化

详细说明，见函数实现及其注释

## 目录
* [实现 strlen](./strlen)
* [实现 strcpy](./strcpy)
* [实现 strncpy](./strncpy)
* [实现 strcat](./strcat)
* [实现 strncat](./strncat)
* [实现 strcmp](./strcmp)
* [实现 strncmp](./strncmp)
* [实现 strchr](./strchr)
* [实现 strrchr](./strrchr)
* [实现 strstr](./strstr)
* [实现 strspn](./strspn)
* [实现 strcspn](./strcspn)
* [实现 strpbrk](./strpbrk)
* [实现 strtok](./strtok)
* [实现 memchr](./memchr)
* [实现 memcmp](./memcmp)
* [实现 memcpy](./memcpy)
* [实现 memmove](./memmove)
* [实现 memset](./memset)



## cpp
### 基本函数
* time(time_t*) 计算 基于 1970-01-01 00:00:00 +0000 utc 的时间戳
* struct tm*    gmtime(const time_t*)                           时间戳   --> 时间元组, +0000 utc
* struct tm* localtime(const time_t*)                           时间戳   --> 时间元组, 本地时间
* char *         ctime(const time_t*)                           时间戳   --> 字符串
* char *  asctime(const struct tm *tm)                          时间元组 --> 字符串
* size_t strftime(char*, size_t, const char*, const struct tm*) 时间元组 --> 字符串, 可以指的格式
* time     mktime(struct tm *tm)                                时间元组 --> 字符戳
* char *strptime(const char*, const char*, struct tm*)          字符串   --> 时间元组




double difftime(time_t time1, time_t time0);

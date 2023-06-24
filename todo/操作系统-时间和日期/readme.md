
# 操作系统-日期和时间
## 基础概念
* 地球自转一圈为一天
* 地球公转一圈为一年
* 地球公转一圈时, 地球自转了 365.24219 圈, 所以, 一年等于 365.24219 天
* 为了修正误差, 区分了平年和闰年
* 规则(这样算完还有误差, 但误差就比较小了)
    * 如果遇到不是整百年, 且能被四  整除, 是闰年
    * 如果遇到  是整百年, 且能被四百整除, 是闰年
* 为什么不把一年直接定义为 365 天, 为了保证夏天始终热, 冬天始终冷, 否则就乱了
* 闰年的参照物是太阳
* 闰月的参照物是月亮
* 时间戳:
    * 距离 1970-01-01 00:00:00 +0000 的秒数, 不包括闰秒
    * 不受时区的影响, 所有时区都相同
    * 有的系统允许使用负数, 有的系统不允许

## GMT(格林威治时间)(已过时)
* 太阳经过格林威治天文台的时间为中午12点
* 这里说的一天不受地球自转速度的影响
* 地球转的快了, 一天就短, 一秒也变短, 慢了, 一天就长, 一秒也变长

## UTC(正在用)
* 原子时间: 一秒是精确的, 一天也是精确的(原子时间有误差, 但很小)
* 由于, 地球自转速度的变化, 导致和 GMT 的时间对不上, 由此, 产生了闰秒
* 好消息是: 2035 年要取消闰秒了

## 夏令时
* 进夏令时的那一天只有 23 个小时
* 出夏令时的那一天只有 25 个小时
* 其他日期都有 24 个小时
* 可以节约能源

## 时区
* 每 15 个经度一个时区
* 总共 24 个时区
* 相邻时区相差一个小时

## 配置
* /etc/default/locale -- 修改系统显示

## 常用函数
```
* time(time_t*)                                                 获取基于 1970-01-01 00:00:00 +0000 的时间戳
* struct tm*    gmtime(const time_t*)                           时间戳   --> 时间元组, +0000 utc
* struct tm* localtime(const time_t*)                           时间戳   --> 时间元组, 本地时间
* char *         ctime(const time_t*)                           时间戳   --> 字符串
* char *  asctime(const struct tm *tm)                          时间元组 --> 字符串
* size_t strftime(char*, size_t, const char*, const struct tm*) 时间元组 --> 字符串, 可以指定格式
* time     mktime(struct tm *tm)                                时间元组 --> 字符戳
* char *strptime(const char*, const char*, struct tm*)          字符串   --> 时间元组
* double difftime(time_t time1, time_t time0);                  两个时间戳的差值

time() => localtime() => strftime(): 时间戳 => 时间元组 => 字符串形式
strptime() => mktime()             : 字符串形式 => 时间元组 => 时间戳
```

## 常用命令
```
* ntpdate -s time-b.nist.gov          # 使用时间服务器更新时间

* date "+%Y-%m-%d %H:%M:%S %z"        # 输出: 年-月-日 时-分-秒 时区
* date "+%F %T %z"                    # 输出: 年-月-日 时-分-秒 时区
* date "+%j"                          # 输出: 一年中的第几天
* date "+%u"                          # 输出: 一周中的第几天(1..7), 1 为周一
* date "+%U"                          # 输出: 一年中的第几周(00..53), 从周一开始
* date "+%w"                          # 输出: 一周中的第几天(0..6), 0 为周末
* date "+%W"                          # 输出: 一年中的第几周(00..53), 从周末开始
* date "+%s"                          # 输出: 时间戳
* date -d "2020-02-02 01:01:01 +0800" # 指定输入日期和时间, 秒数不能为 60
* date -d "@...."                     # 使用: 时间戳
* date -d "next sec"                  # 下一秒
* date -d "next secs"                 # 下一秒
* date -d "next second"               # 下一秒
* date -d "next seconds"              # 下一秒
* date -d "next min"                  # 下一分钟
* date -d "next mins"                 # 下一分钟
* date -d "next minute"               # 下一分钟
* date -d "next minutes"              # 下一分钟
* date -d "next hour"                 # 下一小时
* date -d "next hours"                # 下一小时
* date -d "next day"                  # 明天
* date -d "next days"                 # 明天
* date -d "next mon"                  # 下周一
* date -d "next monday"               # 下周一
* date -d "next month"                # 下个月
* date -d "next months"               # 下个月
* date -d "next year"                 # 下年
* date -d "next years"                # 下年
* date -d "next year  ago"            # 去年, 除年外, 其他也可以
* date -d "next years ago"            # 去年, 除年外, 其他也可以
* date -d "10year"                    # 十年以后, 除年外, 其他也可以
* date -d "10years"                   # 十年以后, 除年外, 其他也可以
* date -d "10   year"                 # 十年以后, 除年外, 其他也可以
* date -d "10   years"                # 十年以后, 除年外, 其他也可以
* date -d "10   year  ago"            # 十年以前, 除年外, 其他也可以
* date -d "10   years ago"            # 十年以前, 除年外, 其他也可以
* date -d "tomorrow"                  # 明天
* date -d "now"                       # 现在
* date -s "2020-02-02 10:10:10"       # 更新系统时间, 需要 root, 格式见 -d 选项
* date -r 1.c                         # 使用: 文件的 mtime

       %A        %a
星期日 sunday    sun
星期一 monday    mon
星期二 tuesday   tue
星期三 wednesday wed
星期四 thursday  thu
星期五 friday    fri
星期六 saturday  sat

       %B         %b
一月   january    jan
二月   february   feb
三月   march      mar
四月   april      apr
五月   may        may
六月   june       jun
七月   july       jul
八月   august     aug
九月   september  sep
十月   october    oct
十一月 november   nov
十二月 december   dec
```


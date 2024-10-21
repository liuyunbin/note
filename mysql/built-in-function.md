
## 1. 数值函数

| 函数                | 用法                                                         |
| ------------------- | ------------------------------------------------------------ |
| ABS(x)              | 返回x的绝对值                                                |
| SIGN(X)             | 返回X的符号。正数返回1，负数返回-1，0返回0                   |
| PI()                | 返回圆周率的值                                               |
| CEIL(x)，CEILING(x) | 返回大于或等于某个值的最小整数                               |
| FLOOR(x)            | 返回小于或等于某个值的最大整数                               |
| LEAST(e1,e2,e3…)    | 返回列表中的最小值                                           |
| GREATEST(e1,e2,e3…) | 返回列表中的最大值                                           |
| MOD(x,y)            | 返回X除以Y后的余数                                           |
| RAND()              | 返回0~1的随机值                                              |
| RAND(x)             | 返回0~1的随机值，其中x的值用作种子值，相同的X值会产生相同的随机数 |
| ROUND(x)            | 返回一个对x的值进行四舍五入后，最接近于X的整数               |
| ROUND(x,y)          | 返回一个对x的值进行四舍五入后最接近X的值，并保留到小数点后面Y位 |
| TRUNCATE(x,y)       | 返回数字x截断为y位小数的结果                                 |
| SQRT(x)             | 返回x的平方根。当X的值为负数时，返回NULL                     |

## 2. 进制间的转换

| 函数          | 用法                     |
| ------------- | ------------------------ |
| BIN(x)        | 返回x的二进制编码        |
| HEX(x)        | 返回x的十六进制编码      |
| OCT(x)        | 返回x的八进制编码        |
| CONV(x,f1,f2) | 返回f1进制数变成f2进制数 |

## 3. 字符串函数
* 字符串的位置是从1开始的

| 函数                              | 用法                                                         |
| --------------------------------- | ------------------------------------------------------------ |
| ASCII(S)                          | 返回字符串S中的第一个字符的ASCII码值                         |
| CHAR_LENGTH(s)                    | 返回字符串s的字符数。作用与CHARACTER_LENGTH(s)相同           |
| LENGTH(s)                         | 返回字符串s的字节数，和字符集有关                            |
| CONCAT(s1,s2,......,sn)           | 连接s1,s2,......,sn为一个字符串                              |
| CONCAT_WS(x, s1,s2,......,sn)     | 同CONCAT(s1,s2,...)函数，但是每个字符串之间要加上x           |
| INSERT(str, idx, len, replacestr) | 将字符串str从第idx位置开始，len个字符长的子串替换为字符串replacestr |
| REPLACE(str, a, b)                | 用字符串b替换字符串str中所有出现的字符串a                    |
| UPPER(s) 或 UCASE(s)              | 将字符串s的所有字母转成大写字母                              |
| LOWER(s)  或LCASE(s)              | 将字符串s的所有字母转成小写字母                              |
| LEFT(str,n)                       | 返回字符串str最左边的n个字符                                 |
| RIGHT(str,n)                      | 返回字符串str最右边的n个字符                                 |
| LPAD(str, len, pad)               | 用字符串pad对str最左边进行填充，直到str的长度为len个字符     |
| RPAD(str ,len, pad)               | 用字符串pad对str最右边进行填充，直到str的长度为len个字符     |
| LTRIM(s)                          | 去掉字符串s左侧的空格                                        |
| RTRIM(s)                          | 去掉字符串s右侧的空格                                        |
| TRIM(s)                           | 去掉字符串s开始与结尾的空格                                  |
| TRIM(s1 FROM s)                   | 去掉字符串s开始与结尾的s1                                    |
| TRIM(LEADING s1 FROM s)           | 去掉字符串s开始处的s1                                        |
| TRIM(TRAILING s1 FROM s)          | 去掉字符串s结尾处的s1                                        |
| REPEAT(str, n)                    | 返回str重复n次的结果                                         |
| SPACE(n)                          | 返回n个空格                                                  |
| STRCMP(s1,s2)                     | 比较字符串s1,s2的ASCII码值的大小                             |
| SUBSTR(s,index,len)               | 返回从字符串s的index位置其len个字符                          |
| SUBSTRING(s,n,len)                | 同上                                                         |
| MID(s,n,len)                      | 同上                                                         |
| LOCATE(substr,str)                | 返回字符串substr在字符串str中首次出现的位置                  |
| POSITION(substr IN str)           | 同上                                                         |
| INSTR(str,substr)                 | 同上                                                         |
| ELT(m,s1,s2,…,sn)                 | 返回指定位置的字符串，如果m=2，则返回s2，如果m=n，则返回sn   |
| FIELD(s,s1,s2,…,sn)               | 返回字符串s在字符串列表中第一次出现的位置                    |
| FIND_IN_SET(s1,s2)  | 返回字符串s1在字符串s2中出现的位置。其中，字符串s2是一个以逗号分隔的字符串 |
| REVERSE(s)                        | 返回s反转后的字符串                                          |
| NULLIF(value1,value2)             | 比较两个字符串，如果value1与value2相等，则返回NULL，否则返回value1 |

```
SELECT LENGTH('中国'), CHAR_LENGTH('中国'); # 字符长度和字节长度

SELECT REPLACE('中国人中国', '中国人', '德国人'); # 字符串替换

SELECT LOCATE('中国人', '中国人中国'); # 字符串查找

SELECT ELT(2, '中', '国', '人'); # 返回指定位置的字符串

SELECT FIELD('中',     '中国人', '德国人', '中国人'); # 字符串查找
SELECT FIELD('德国人', '中国人', '德国人', '中国人'); # 字符串查找

SELECT FIND_IN_SET('中',     '中国人,德国人,中国人'); # 字符串在集合查找
SELECT FIND_IN_SET('德国人', '中国人,德国人,中国人'); # 字符串在集合查找

SELECT NULLIF('中国人', '中国人');
SELECT NULLIF('德国人', '中国人');
```

## 4. 日期和时间函数
#### 4.1 获取日期、时间

| 函数                                | 用法                           |
| ----------------------------------- | ------------------------------ |
| **CURDATE()** ，CURRENT_DATE()      | 返回当前日期，只包含年、月、日 |
| **CURTIME()** ， CURRENT_TIME()     | 返回当前时间，只包含时、分、秒 |
| **NOW()**                           | 返回当前系统日期和时间         |
| SYSDATE()                           | 返回当前系统日期和时间         |
| CURRENT_TIMESTAMP()                 | 返回当前系统日期和时间         |
| LOCALTIME()                         | 返回当前系统日期和时间         |
| LOCALTIMESTAMP()                    | 返回当前系统日期和时间         |
| UTC_DATE()                          | 返回UTC（世界标准时间）日期    |
| UTC_TIME()                          | 返回UTC（世界标准时间）时间    |

```
SELECT 
    CURDATE()  AS '年月日',    
    CURTIME()  AS '时分秒',
    NOW()      AS '年月日 时分秒',
    UTC_DATE() AS 'UTC日期',
    UTC_TIME() AS 'UTC时间'
```

#### 4.2 日期与时间戳的转换

| 函数                     | 用法                                                         |
| ------------------------ | ------------------------------------------------------------ |
| UNIX_TIMESTAMP()         | 以UNIX时间戳的形式返回当前时间。SELECT UNIX_TIMESTAMP() ->1634348884 |
| UNIX_TIMESTAMP(date)     | 将时间date以UNIX时间戳的形式返回。                           |
| FROM_UNIXTIME(timestamp) | 将UNIX时间戳的时间转换为普通格式的时间                       |

```
SELECT
    UNIX_TIMESTAMP()      AS '时间戳',
    UNIX_TIMESTAMP(now()) AS '日期 -> 时间戳',
    FROM_UNIXTIME(0)      AS '时间戳 -> 日期';
```

## 4.3 获取月份、星期、星期数、天数等函数

| 函数                                     | 用法                                            |
| ---------------------------------------- | ----------------------------------------------- |
| YEAR(date) / MONTH(date) / DAY(date)     | 返回具体的日期值                                |
| HOUR(time) / MINUTE(time) / SECOND(time) | 返回具体的时间值                                |
| MONTHNAME(date)                          | 返回月份：January，...                          |
| DAYNAME(date)                            | 返回星期几：MONDAY，TUESDAY.....SUNDAY          |
| WEEKDAY(date)                            | 返回周几，注意，周1是0，周2是1，。。。周日是6   |
| QUARTER(date)                            | 返回日期对应的季度，范围为1～4                  |
| WEEK(date) ， WEEKOFYEAR(date)           | 返回一年中的第几周                              |
| DAYOFYEAR(date)                          | 返回日期是一年中的第几天                        |
| DAYOFMONTH(date)                         | 返回日期位于所在月份的第几天                    |
| DAYOFWEEK(date)                          | 返回周几，注意：周日是1，周一是2，。。。周六是7 |

```
SELECT YEAR(CURDATE()) '年', MONTH(CURDATE())  '月', DAY(CURDATE())    '日';
SELECT HOUR(CURTIME()) '时', MINUTE(CURTIME()) '分', SECOND(CURTIME()) '秒';

SELECT MONTHNAME(CURDATE()) '月份', DAYNAME(CURDATE()) '星期';

SELECT QUARTER(now()) '一年第几季度', DAYOFYEAR(now()) '一年第几天', DAYOFMONTH(now()) '一月第几天';

# 一年第几周: 星期从周日开始, 每年的第一个周日为第一周, 之前为第 0 周
SELECT WEEK('2024-01-01')       '2024 第一天 周一',
       WEEK('2024-01-06')       '2024 第六天 周日',
       WEEK('2024-01-07')       '2024 第七天 周日',
       WEEK('2024-01-08')       '2024 第八天 周一'

# 一年第几周: 星期从周一开始, 每年的第一天即为第一周
SELECT WEEKOFYEAR('2024-01-01')       '2024 第一天 周一',
       WEEKOFYEAR('2024-01-06')       '2024 第六天 周日',
       WEEKOFYEAR('2024-01-07')       '2024 第七天 周日',
       WEEKOFYEAR('2024-01-08')       '2024 第八天 周一'

# 一周第几天, 周一为第一天 [0,6]
SELECT  WEEKDAY('2024-01-01') '周一',
        WEEKDAY('2024-01-02') '周二',
        WEEKDAY('2024-01-03') '周三',
        WEEKDAY('2024-01-04') '周四',
        WEEKDAY('2024-01-05') '周五',
        WEEKDAY('2024-01-06') '周六',
        WEEKDAY('2024-01-07') '周日',
        WEEKDAY('2024-01-08') '周一'

# 一周第几天, 周日为第一天 [1,7]
SELECT  DAYOFWEEK('2024-01-01') '周一',
        DAYOFWEEK('2024-01-02') '周二',
        DAYOFWEEK('2024-01-03') '周三',
        DAYOFWEEK('2024-01-04') '周四',
        DAYOFWEEK('2024-01-05') '周五',
        DAYOFWEEK('2024-01-06') '周六',
        DAYOFWEEK('2024-01-07') '周日',
        DAYOFWEEK('2024-01-08') '周一'
```

## 4.4 日期的操作函数
| 函数                    | 用法                                       |
| ----------------------- | ------------------------------------------ |
| EXTRACT(type FROM date) | 返回指定日期中特定的部分，type指定返回的值 |

```
SELECT
    EXTRACT(MINUTE FROM NOW()),
    EXTRACT(WEEK FROM NOW()),
    EXTRACT(QUARTER FROM NOW()),
    EXTRACT(MINUTE_SECOND FROM NOW())
```

## 4.5 时间和秒钟转换的函数

| 函数                 | 用法                                                         |
| -------------------- | ------------------------------------------------------------ |
| TIME_TO_SEC(time)    | 将 time 转化为秒并返回结果值。转化的公式为：`小时*3600+分钟*60+秒` |
| SEC_TO_TIME(seconds) | 将 seconds 描述转化为包含小时、分钟和秒的时间                |


```
SELECT TIME_TO_SEC(NOW());

SELECT SEC_TO_TIME(78774);
```

#### 4.6 计算日期和时间的函数
##### 第1组

| 函数                                    | 用法                                           |
| --------------------------------------- | ---------------------------------------------- |
| DATE_ADD(datetime, INTERVAL  expr type) | 返回与给定日期时间相差INTERVAL时间段的日期时间 |
| ADDDATE(date,INTERVAL expr type)        | 返回与给定日期时间相差INTERVAL时间段的日期时间 |
| DATE_SUB(date,INTERVAL expr type)       | 返回与date相差INTERVAL时间间隔的日期           |
| SUBDATE(date,INTERVAL expr type)        | 返回与date相差INTERVAL时间间隔的日期           |

```
SELECT 
    DATE_ADD(NOW(),                 INTERVAL 1 DAY) AS col1,
    DATE_ADD('2021-10-21 23:32:12', INTERVAL 1 SECOND) AS col2,
    ADDDATE('2021-10-21 23:32:12',  INTERVAL 1 SECOND) AS col3,
    DATE_ADD('2021-10-21 23:32:12', INTERVAL '1_1' MINUTE_SECOND) AS col4,
    DATE_ADD(NOW(),                 INTERVAL -1 YEAR) AS col5, #可以是负数
    DATE_ADD(NOW(),                 INTERVAL '1_1' YEAR_MONTH) AS col6 #需要单引号


SELECT
    DATE_SUB('2021-01-21',          INTERVAL 31 DAY) AS col1,
    SUBDATE('2021-01-21',           INTERVAL 31 DAY) AS col2,
    DATE_SUB('2021-01-21 02:01:01', INTERVAL '1 1' DAY_HOUR) AS col3
```

##### 第2组

| 函数                         | 用法                                                         |
| ---------------------------- | ------------------------------------------------------------ |
| ADDTIME(time1,time2)         | 返回time1加上time2的时间。当time2为一个数字时，代表的是`秒`，可以为负数 |
| SUBTIME(time1,time2)         | 返回time1减去time2后的时间。当time2为一个数字时，代表的是`秒`，可以为负数 |
| DATEDIFF(date1,date2)        | 返回date1 - date2的日期间隔天数                              |
| TIMEDIFF(time1, time2)       | 返回time1 - time2的时间间隔                                  |
| FROM_DAYS(N)                 | 返回从0000年1月1日起，N天以后的日期                          |
| TO_DAYS(date)                | 返回日期date距离0000年1月1日的天数                           |
| LAST_DAY(date)               | 返回date所在月份的最后一天的日期                             |
| MAKEDATE(year,n)             | 针对给定年份与所在年份中的天数返回一个日期                   |
| MAKETIME(hour,minute,second) | 将给定的小时、分钟和秒组合成时间并返回                       |
| PERIOD_ADD(time,n)           | 返回time加上n后的时间                                        |

```
SELECT ADDTIME(NOW(), 20), SUBTIME(NOW(), 30), SUBTIME(NOW(),'1:1:3'); # 时间加减

SELECT DATEDIFF(NOW(),'2021-10-01'), TIMEDIFF(NOW(),'2021-10-25 22:10:10'); # 天数 或 时间间隔

SELECT FROM_DAYS(0); # 0000-01-01 后多少天的日期

SELECT  TO_DAYS('0000-12-25'); # 日期距离 0000-01-01 的天数

SELECT  LAST_DAY(NOW()); # 日期所在月份的最后一天

SELECT MAKEDATE(YEAR(NOW()), 12); # 给定年份和天数, 返回日期

SELECT MAKETIME(10, 21, 23); # 时分秒组成时间

SELECT PERIOD_ADD(20200101010101, 10);
```

#### 4.7 日期的格式化与解析

| 函数                              | 用法                                       |
| --------------------------------- | ------------------------------------------ |
| DATE_FORMAT(date,fmt)             | 按照字符串fmt格式化日期date值              |
| TIME_FORMAT(time,fmt)             | 按照字符串fmt格式化时间time值              |
| GET_FORMAT(date_type,format_type) | 返回日期字符串的显示格式                   |
| STR_TO_DATE(str, fmt)             | 按照字符串fmt对str进行解析，解析为一个日期 |

上述`非GET_FORMAT`函数中fmt参数常用的格式符：

| 格式符 | 说明  | 格式符 | 说明      |
| ------ | -------- | ------ | -------- |
| %Y | 4位数字表示年份                             | %y     | 表示两位数字表示年份               |
| %M | 月名表示月份（January,....）                | %m     | 两位数字表示月份（01,02,03。。。） |
| %b | 缩写的月名（Jan.，Feb.，....）              | %c     | 数字表示月份（1,2,3,...）          |
| %D | 英文后缀表示月中的天数（1st,2nd,3rd,...）   | %d     | 两位数字表示月中的天数(01,02...)   |
| %e | 数字形式表示月中的天数（1,2,3,4,5.....）    |        |                                    |
| %H | 两位数字表示小数，24小时制（01,02..）       | %h和%I | 两位数字表示小时，12小时制（01,02..） |
| %k | 数字形式的小时，24小时制(1,2,3)             | %l     | 数字形式表示小时，12小时制（1,2,3,4....） |
| %i | 两位数字表示分钟（00,01,02）                | %S和%s | 两位数字表示秒(00,01,02...) |
| %W | 一周中的星期名称（Sunday...）               | %a     | 一周中的星期缩写（Sun.，Mon.,Tues.，..） |
| %w | 以数字表示周中的天数(0=Sunday,1=Monday....) |        |    |
| %j | 以3位数字表示年中的天数(001,002...) | %U | 以数字表示年中的第几周（1,2,3。。）其中Sunday为周中第一天 |
| %u | 以数字表示年中的第几周，（1,2,3。。）其中Mon   |  |
| %T | 24小时制                                    | %r     | 12小时制                    |
| %p | AM或PM                                      | %%     | 表示%                       |

```
SELECT DATE_FORMAT(NOW(), '%H:%i:%s');

SELECT STR_TO_DATE('09/01/2009','%m/%d/%Y');

SELECT STR_TO_DATE('20140422154706','%Y%m%d%H%i%s');

SELECT STR_TO_DATE('2014-04-22 15:47:06','%Y-%m-%d %H:%i:%s');

SELECT GET_FORMAT(DATE, 'USA');

SELECT DATE_FORMAT(NOW(),GET_FORMAT(DATE,'USA'));

SELECT STR_TO_DATE('2020-01-01 00:00:00','%Y-%m-%d'); 
```

## 5. 流程控制函数

| 函数                          | 用法                         |
| ----------------------------- | ---------------------------- |
| IF(value,value1,value2)       | 如果value的值为TRUE，返回value1，否则返回value2 |
| IFNULL(value1, value2)        | 如果value1 不为NULL，返回value1，否则返回value2  |
| CASE WHEN 条件1 THEN 结果1 WHEN 条件2 THEN 结果2 ....  [ELSE resultn] END | 相当于 if else      |
| CASE expr WHEN 常量值1 THEN 值1 WHEN 常量值1 THEN 值1 .... [ELSE 值n] END | 相当于 switch case  |

```
SELECT IF(1 > 0,'正确','错误');

SELECT IFNULL(null,'Hello Word')

SELECT
    CASE 
    WHEN  1 > 0 
        THEN '1 > 0'
    WHEN  2 > 0
        THEN '2 > 0'
    ELSE
        '3 > 0'
    END;

SELECT
    CASE 1 
    WHEN 0 
        THEN 0
    WHEN 1
        THEN 1
    ELSE
        -1
    END;
```

## 6. 加密与解密函数

| 函数     | 用法                                                         |
| -------- | ------------------------------------------------------------ |
| PASSWORD(str)  | 返回字符串str的加密版本，41位长的字符串。加密结果`不可逆`，常用于用户的密码加密 |
| MD5(str) | 返回字符串str的md5加密后的值，也是一种加密方式。若参数为NULL，则会返回NULL |
| SHA(str) | 从原明文密码str计算并返回加密后的密码字符串，当参数为NULL时，返回NULL。`SHA加密算法比MD5更加安全`。 |
| ENCODE(value,password_seed) | 返回使用password_seed作为加密密码加密value  |
| DECODE(value,password_seed) | 返回使用password_seed作为加密密码解密value  |

```
SELECT PASSWORD('mysql'); # 900 报错, 该函数应该已被删除了

SELECT SHA('Tom123');

SELECT ENCODE('mysql', 'mysql'); # 900 报错, 该函数应该已被删除了

SELECT DECODE(ENCODE('mysql','mysql'),'mysql'); # 900 报错, 该函数应该已被删除了
```

## 7. MySQL信息函数

| 函数         | 用法     |
| ------------ | -------- |
| VERSION()               | 返回当前MySQL的版本号               |
| CONNECTION_ID()         | 返回当前MySQL服务器的连接数         |
| DATABASE()，SCHEMA()    | 返回MySQL命令行当前所在的数据库     |
| USER()，CURRENT_USER()、SYSTEM_USER()，SESSION_USER() | 返回当前连接MySQL的用户名，返回结果格式为“主机名@用户名” |
| CHARSET(value)          | 返回字符串value自变量的字符集       |
| COLLATION(value)        | 返回字符串value的比较规则           |

```
SELECT VERSION();

SELECT DATABASE();

SELECT USER(), CURRENT_USER(), SYSTEM_USER(),SESSION_USER();

SELECT CHARSET('ABC');

SELECT COLLATION('ABC');
```

## 8. 其他单行函数

| 函数                           | 用法                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| FORMAT(value,n)                | 返回对数字value进行格式化后的结果数据。n表示`四舍五入`后保留到小数点后n位 |
| CONV(value,from,to)            | 将value的值进行不同进制之间的转换                            |
| INET_ATON(ipvalue)             | 将以点分隔的IP地址转化为一个数字                             |
| INET_NTOA(value)               | 将数字形式的IP地址转化为以点分隔的IP地址                     |
| BENCHMARK(n,expr)              | 将表达式expr重复执行n次。用于测试MySQL处理expr表达式所耗费的时间 |
| CONVERT(value USING char_code) | 将value所使用的字符编码修改为char_code                       |

```
SELECT FORMAT(123.123, 2), FORMAT(123.523, 0), FORMAT(123.123, -2); 

SELECT CONV(16, 10, 2), CONV(8888, 10, 16), CONV(NULL, 10, 2);

SELECT INET_ATON('192.168.1.100');
SELECT INET_NTOA(3232235876);

SELECT BENCHMARK(1,       MD5('mysql'));
SELECT BENCHMARK(1000000, MD5('mysql')); 

SELECT CHARSET('mysql'), CHARSET(CONVERT('mysql' USING 'utf8'));
```

## 9. 聚合函数
```
* 不能嵌套

USE  test;
DROP TABLE IF EXISTS student;
CREATE TABLE student (
    id int,
    name VARCHAR(20),
    score DECIMAL
);

INSERT INTO student VALUES(1, '张三', 100);
INSERT INTO student VALUES(2, '李四', 70);
INSERT INTO student VALUES(3, '王五', 80);
INSERT INTO student VALUES(4, '赵六', NULL);
INSERT INTO student VALUES(5, '田七', 70);

SELECT max(score)              FROM student;   # 任意类型 跳过 NULL 行
SELECT min(score)              FROM student;   # 任意类型 跳过 NULL 行
SELECT avg(score)              FROM student;   # 数值类 跳过 NULL 行
SELECT sum(score)/count(score) FROM student;   # 数值类 跳过 NULL 行
SELECT sum(score)/count(*)     FROM student;   # 数值类 包含 NULL 行
SELECT sum(score) FROM student;                # 数值类 跳过 NULL 行
SELECT count(score) FROM student;              # 任意类型 跳过 NULL 行
SELECT count(*) FROM student;                  # 任意类型 包含 NULL 行
```


## 1. 整型
* 一般使用 INT 就足够了
* 如果值不可能是负数, 使用 UNSIGNED

| **整数类型** | **字节** | 有符号数取值范围                         | 无符号数取值范围       |
| ------------ | -------- | ---------------------------------------- | ---------------------- |
| TINYINT      | 1        | -128~127                                 | 0~255                  |
| SMALLINT     | 2        | -32768~32767                             | 0~65535                |
| MEDIUMINT    | 3        | -8388608~8388607                         | 0~16777215             |
| INT、INTEGER | 4        | -2147483648~2147483647                   | 0~4294967295           |
| BIGINT       | 8        | -9223372036854775808~9223372036854775807 | 0~18446744073709551615 |

## 2. 浮点类型
* FLOAT(M,D) ---- 单精度浮点数 --- 4字节
* DOUBLE(M,D) --- 双精度浮点数 --- 8字节
* M=整数位+小数位, D=小数位, D<=M<=255, 0<=D<=30
* 直观看到的值和实际存储的值不一定相同
* 整数超出范围会报错
* 一般不用浮点数, 使用定点数

## 3. 定点数类型
* DECIMAL(M,D) --- M + 2 字节
* M=整数位+小数位, D=小数位, 0<=M<=65, 0<=D<=30

```
DROP TABLE IF EXISTS test_double;
CREATE TABLE test_double(
    f1 DOUBLE(65, 2),
    f2 DECIMAL(65, 2)
);
  
DESC test_double;
  
INSERT INTO test_double
VALUES(4503599627370496.25,4503599627370496.25);

SELECT * FROM test_double;
```

## 4. 位类型
* BIT(M) ---- 1 <= M <= 64 ----- 约为(M + 7)/8个字节
* 很少使用

## 5. 日期与时间类型
* 一般使用 DATETIME 即可
* 涉及计算使用 TIMESTAMP

| 类型      | 名称     | 字节 | 日期格式            | 最小值                  | 最大值                 |
| --------- | -------- | ---- | ------------------- | ----------------------- | ---------------------- |
| YEAR      | 年       | 1    | YYYY或YY            | 1901                    | 2155                   |
| TIME      | 时间     | 3    | HH:MM:SS            | -838:59:59              | 838:59:59              |
| DATE      | 日期     | 3    | YYYY-MM-DD          | 1000-01-01              | 9999-12-03             |
| DATETIME  | 日期时间 | 8    | YYYY-MM-DD HH:MM:SS | 1000-01-01 00:00:00     | 9999-12-31 23:59:59    |
| TIMESTAMP | 日期时间 | 4    | YYYY-MM-DD HH:MM:SS | 1970-01-01 00:00:00 UTC | 2038-01-19 03:14:07UTC |

```
DROP TABLE IF EXISTS test_date;
CREATE TABLE test_date(
    f1 TIME
);
  
DESC test_date;

TRUNCATE TABLE test_date;
INSERT INTO test_date VALUES('1 12:12:12'); --  1 天 12 时 12分 12 秒 -- 天数最小值为0, 最大值为34
INSERT INTO test_date VALUES('1 12:12');    --  相当于 `1 12:12:00`
INSERT INTO test_date VALUES('1 12');       --  相当于 `1 12:00:00`
SELECT * FROM  test_date;

TRUNCATE TABLE test_date;
INSERT INTO test_date VALUES('12:12:12'); -- 12 时 12分 12 秒
INSERT INTO test_date VALUES('12:12');    -- 相当于 `12:12:00`
INSERT INTO test_date VALUES('12');       -- 相当于 `00:00:12`
SELECT * FROM  test_date;

TRUNCATE TABLE test_date;
INSERT INTO test_date VALUES('121212');  -- 12 时 12分 12 秒
INSERT INTO test_date VALUES(  '1212');  -- 相当于 `001212`
INSERT INTO test_date VALUES( '11212');  -- 相当于 `011212`
INSERT INTO test_date VALUES('011212');  -- 
SELECT * FROM test_date;

TRUNCATE TABLE test_date;
INSERT INTO test_date VALUES(121212);  -- 12 时 12分 12 秒
INSERT INTO test_date VALUES(  1212);  -- 相当于 `001212`
INSERT INTO test_date VALUES( 11212);  -- 相当于 `011212`
INSERT INTO test_date VALUES(011212);  -- 
SELECT * FROM test_date;
```

## 6. 文本字符串类型
#### 6.1 CHAR与VARCHAR
* char 默认长度为 1, 会自动去末尾的空格
* 长度明确固定的使用 char, 其他情况使用 VARCHAR

| 字符串(文本)类型 | 特点     | 长度 | 长度范围        | 占用的存储空间        |
| ---------------- | -------- | ---- | --------------- | --------------------- |
| CHAR(M)          | 固定长度 | M    | 0 <= M <= 255   | M个字符               |
| VARCHAR(M)       | 可变长度 | M    | 0 <= M <= 65535 | (实际长度 + 1) 个字符 |

```
DROP TABLE IF EXISTS test_char;
CREATE TABLE test_char(
    c1 CHAR(10),
    c2 VARCHAR(10)
);

INSERT INTO test_char VALUES('   a    ',
                             '   a   ');

SELECT c1, LENGTH(c1), CONCAT('**', c1,'**'), c2, LENGTH(c2), CONCAT('**', c2,'**') FROM test_char;

DROP TABLE IF EXISTS test_char;
CREATE TABLE test_char(
    c1 CHAR(2),
    c2 VARCHAR(2)
);

DESC test_char;
INSERT INTO test_char VALUES('中', '中');
SELECT c1, LENGTH(c1), c2, LENGTH(c2) FROM test_char;
```

#### 6.2 TEXT类型
* 不能做主键
* 很少使用, 非使用不可的话, 建议放到单独的表中

| 文本字符串类型 | 特点               | 长度 | 长度范围                         | 占用的存储空间 |
| -------------- | ------------------ | ---- | -------------------------------- | -------------- |
| TINYTEXT       | 小文本、可变长度   | L    | 0 <= L <= 255                    | L + 2 个字节   |
| TEXT           | 文本、可变长度     | L    | 0 <= L <= 65535                  | L + 2 个字节   |
| MEDIUMTEXT     | 中等文本、可变长度 | L    | 0 <= L <= 16777215               | L + 3 个字节   |
| LONGTEXT       | 大文本、可变长度   | L    | 0 <= L<= 4294967295（相当于4GB） | L + 4 个字节   |

## 7. ENUM类型
* 只允许从成员中取值
* 只允许取一个值
* 可以取 NULL

| 文本字符串类型 | 长度 | 长度范围        | 占用的存储空间 |
| -------------- | ---- | --------------- | -------------- |
| ENUM           | L    | 1 <= L <= 65535 | 1或2个字节     |

```
DROP TABLE IF EXISTS test_enum;
CREATE TABLE test_enum (
season ENUM('春','夏','秋','冬', 'unknow')
);

TRUNCATE TABLE test_enum;
INSERT INTO test_enum VALUES('春'),('秋');
SELECT * FROM test_enum;

TRUNCATE TABLE test_enum;
INSERT INTO test_enum VALUES('UNKNOW'); # 忽略大小写
SELECT * FROM test_enum;

TRUNCATE TABLE test_enum;
INSERT INTO test_enum VALUES('1'),(3);  # 获取指定索引位置的枚举值, 索引从 1 开始
SELECT * FROM test_enum;

INSERT INTO test_enum VALUES('ab'); # 不在枚举范围内, 报错

TRUNCATE TABLE test_enum;
INSERT INTO test_enum VALUES(NULL); # 可以是 NULL 值
SELECT * FROM test_enum;
```

## 8. SET类型
* 只允许从成员中取值
* 允许取多个值
* 可以取 NULL

| 成员个数范围（L表示实际成员个数） | 占用的存储空间 |
| --------------------------------- | -------------- |
| 1 <= L <= 8                       | 1个字节        |
| 9 <= L <= 16                      | 2个字节        |
| 17 <= L <= 24                     | 3个字节        |
| 25 <= L <= 32                     | 4个字节        |
| 33 <= L <= 64                     | 8个字节        |


```
CREATE TABLE test_set(
s SET ('A', 'B', 'C')
);

TRUNCATE TABLE test_set;
INSERT INTO test_set (s) VALUES ('A'), ('A,B');
SELECT * FROM test_set;

TRUNCATE TABLE test_set;
INSERT INTO test_set (s) VALUES ('A,B,C,A'); # 自动去重
SELECT * FROM test_set;

INSERT INTO test_set (s) VALUES ('A,B,C,D'); # 不存在报错

TRUNCATE TABLE test_set;
INSERT INTO test_set (s) VALUES (NULL); # 可以为空
SELECT * FROM test_set;
```

## 9. 二进制字符串类型
#### 9.1 BINARY与VARBINARY
* 类似于CHAR和VARCHAR
* 只是它们存储的是二进制字符串

| 二进制字符串类型 | 特点     | 值的长度             | 占用空间  |
| ---------------- | -------- | -------------------- | --------- |
| BINARY(M)        | 固定长度 | M （0 <= M <= 255）  | M个字节   |
| VARBINARY(M)     | 可变长度 | M（0 <= M <= 65535） | M+1个字节 |

#### 9.2 BLOB类型
* 很少使用, 非使用不可的话, 建议放到单独的表中

| 二进制字符串类型 | 值的长度 | 长度范围                          | 占用空间     |
| ---------------- | -------- | --------------------------------- | ------------ |
| TINYBLOB         | L        | 0 <= L <= 255                     | L + 1 个字节 |
| BLOB             | L        | 0 <= L <= 65535（相当于64KB）     | L + 2 个字节 |
| MEDIUMBLOB       | L        | 0 <= L <= 16777215 （相当于16MB） | L + 3 个字节 |
| LONGBLOB         | L        | 0 <= L <= 4294967295（相当于4GB） | L + 4 个字节 |

## 10. JSON 类型
```
DROP TABLE IF EXISTS test_json;
CREATE TABLE test_json (
js json
);

INSERT INTO test_json (js) 
VALUES ('{"name":"songhk", "age":18, "address":{"province":"beijing", "city":"beijing"}}');

SELECT * FROM test_json;

SELECT
    js -> '$.name' AS NAME,
    js -> '$.age'  AS age ,
    js -> '$.address.province' AS province,
    js -> '$.address.city' AS city
FROM test_json;
```

## 11. 空间类型
* 单值类型：GEOMETRY、POINT、LINESTRING、POLYGON
* 集合类型：MULTIPOINT、MULTILINESTRING、MULTIPOLYGON、GEOMETRYCOLLECTION

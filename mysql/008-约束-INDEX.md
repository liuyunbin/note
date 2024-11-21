
# INDEX --- 索引
## 0. 总结
```
* WHERE    列使用索引 --- 避免全表扫描
* GROUP BY 列使用索引 --- 避免使用临时表
* ORDER BY 列使用索引 --- 避免文件排序
* DISTINCT 列使用索引 --- 避免使用临时表
* 查询时, 一张表中最多使用一个索引
* 联合索引建议
    * 联合索引优于多个单列索引
    * 范围查找建议放到联合索引的右侧 --- 最左前缀原则
    * 建立索引的顺序建议: WHERE, GROUP BY, DISTINCT, DISTINCT
* 索引查找尽量不要使用范围查找(包括不等于)
* 适合建索引
    * WHERE GROUP BY ORDER BY DISTINCT 中频繁使用
    * 区分度大的列
    * 很少变化的列
* 不适合建索引
    * 表很小
* 最左前缀原则
    * 对于联合索引 index(int_1, int_2, int_3)
    * 使用的时候, 只能先使用 int_1 再使用 int_2, int3
    * 直接使用 int_2 或 int_3 不能使用该索引
* 索引覆盖 -- Using index
    * 使用当前索引就可以满足条件, 不需要回表
* 索引下推 -- Using index condition
    * 使用索引表提前判断, 减少回表的情况   
* 隐藏索引 -- INVISIBLE VISIBLE
    * 便于观察删除索引的影响
* 降序索引 -- DESC
    * 如果查找是降序的话, 可以提高效率
    * 对联合索引提高明显
* 唯一索引和普通索引
    * 查询效率, 唯一索引 略强于 普通索引
    * 更新效率, 普通索引   强于 唯一索引
    * 插入效率, 普通索引   强于 唯一索引 
    * 写大于读的情况下, 可以考虑使用普通索引代替唯一索引
    * 归档的库, 不存在冲突了, 可以考虑把唯一索引换成普通索引
```

## 1. 基础
```
# 1.1 创建
# 1.1.1 单列: 不指定索引名称: 索引名称默认是列名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id));
SHOW   INDEX FROM student;

# 1.1.2 单列: 指定索引名称
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;

# 1.1.3 多列: 不指定索引名称: 索引名称默认是第一个列名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX(id, name));
SHOW   INDEX FROM student;

# 1.1.4 多列: 指定索引名称
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX index_name(id, name));
SHOW   INDEX FROM student;

# 1.1.5 单列: 指定降序索引
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id DESC));
SHOW   INDEX FROM student;

# 1.1.6 单列: 指定不可见索引
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id) INVISIBLE);
SHOW   INDEX FROM student;

# 1.2 添加
# 1.2.1 使用 CREATE INDEX 添加 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
CREATE INDEX index_name ON student(id);
SHOW   INDEX FROM student;

# 1.2.2 使用 ALTER 添加
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
ALTER  TABLE student ADD INDEX index_name(id);
SHOW   INDEX FROM student;

# 1.3 修改
# 1.3.1 设置索引是否可见
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name INVISIBLE;
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name VISIBLE;
SHOW   INDEX FROM student;

# 1.4 删除
# 1.4.1 使用 DROP (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
DROP   INDEX index_name ON student;
SHOW   INDEX FROM student;

# 1.4.2 使用 ALTER
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX index_name;
SHOW   INDEX FROM student;

# 1.5 重命名索引
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student RENAME INDEX index_name TO new_index_name;
SHOW   INDEX FROM student;
```

## 2. 准备测试数据
```
# 2.0 设置变量
SET GLOBAL log_bin_trust_function_creators = 1;

# 2.1 创建两张表
DROP   TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id    INT AUTO_INCREMENT PRIMARY KEY, 
    int_1 INT NOT NULL,
    int_2 INT NOT NULL,
    int_3 INT NOT NULL,
    str_1 VARCHAR(20) NOT NULL,
    str_2 VARCHAR(20) NOT NULL,
    str_3 VARCHAR(20) NOT NULL
);

DROP   TABLE IF EXISTS tb2;
CREATE TABLE tb2 (
    id    INT AUTO_INCREMENT PRIMARY KEY, 
    int_1 INT NOT NULL,
    int_2 INT NOT NULL,
    int_3 INT NOT NULL,
    str_1 VARCHAR(20) NOT NULL,
    str_2 VARCHAR(20) NOT NULL,
    str_3 VARCHAR(20) NOT NULL
);

# 2.2 创建帮助函数
# 2.2.1 返回随机字符串
DROP FUNCTION IF EXISTS rand_string;
DELIMITER $
CREATE FUNCTION rand_string(n INT)
	RETURNS VARCHAR(255) 
BEGIN
    DECLARE  chars_str VARCHAR(100) DEFAULT 'abcdefghijklmnopqrstuvwxyzABCDEFJHIJKLMNOPQRSTUVWXYZ';
	DECLARE return_str VARCHAR(255) DEFAULT '';
    DECLARE i          INT          DEFAULT 0;

    WHILE i < n DO
    	SET return_str =CONCAT(return_str,SUBSTRING(chars_str,FLOOR(1+RAND()*52),1));
    	SET i = i + 1;
    END WHILE;
    RETURN return_str;
END $
DELIMITER ;

# 2.2.2 返回随机数字
DROP FUNCTION IF EXISTS rand_num;
DELIMITER $
CREATE FUNCTION rand_num (from_num INT, to_num INT)
RETURNS INT(11)
BEGIN
    DECLARE i INT DEFAULT 0;
    SET i = FLOOR(from_num +RAND()*(to_num - from_num+1)) ;
    RETURN i;
END $
DELIMITER ;

# 2.2.3 插入数据 
DROP   PROCEDURE IF EXISTS insert_table;
DELIMITER $
CREATE PROCEDURE insert_table(max_num INT, table_name VARCHAR(20))
BEGIN
    DECLARE i INT DEFAULT 0;
    SET autocommit = 0;
    REPEAT
        SET i = i + 1;
        
        SET @str = CONCAT("INSERT INTO " , table_name, " (int_1, int_2, int_3, str_1, str_2, str_3) VALUES
            (rand_num(0,10000), rand_num(0,10000), rand_num(0,10000),
             rand_string(6), rand_string(9), rand_string(10))");
        PREPARE sql_str FROM @str ;
        EXECUTE sql_str;
        DEALLOCATE PREPARE sql_str;
    UNTIL i = max_num
    END REPEAT;
    COMMIT;
END $
DELIMITER ;

# 2.2.4 清除除主键外的所有索引
DROP   PROCEDURE IF EXISTS drop_index;
DELIMITER $
CREATE PROCEDURE drop_index (dbname VARCHAR(200), tablename VARCHAR(200))
BEGIN
    DECLARE done INT DEFAULT 0;
    DECLARE current_index VARCHAR(200);
    DECLARE cursor_name CURSOR FOR
        SELECT index_name
        FROM   information_schema.STATISTICS
        WHERE
               table_schema  = dbname AND
               table_name    = tablename AND
               seq_in_index  = 1 AND
               index_name   != 'PRIMARY';
        DECLARE CONTINUE HANDLER FOR NOT FOUND set done = 1; # 无数据时, 设置 done 为 1
    OPEN cursor_name;
    
    FETCH cursor_name INTO current_index;
    WHILE done = 0 DO
        SET @str = CONCAT("DROP INDEX " , current_index , " ON " , tablename );
        PREPARE sql_str FROM @str ;
        EXECUTE sql_str;
        DEALLOCATE PREPARE sql_str;
        FETCH cursor_name INTO current_index;
    END WHILE;
    CLOSE cursor_name;
END $
DELIMITER ;

# 2.3 插入数据
TRUNCATE tb1;
CALL insert_table(1000000, "tb1"); # 100 万数据, 125.408s
SELECT count(*) FROM tb1;

TRUNCATE tb2;
CALL insert_table(2000000, "tb2"); # 200 万数据, 271.414s
SELECT count(*) FROM tb2;
```

## 3. 测试
#### 3.1 只在 WHERE 中使用索引 --- 避免全表扫描
```
# 3.1.1 只使用索引列 (单列索引, 整型)
CALL drop_index("test", "tb1");
CREATE  INDEX index_int_1 ON tb1(int_1);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1;
* key_len = 4 ------------ 使用索引

EXPLAIN SELECT * FROM tb1 WHERE int_1 =  '1';
* key_len = 4 ------------ 使用索引 --- 为什么这个优化了 --- 整型转字符串是一对一的

EXPLAIN SELECT * FROM tb1 WHERE UPPER(int_1) = '1';
* Using where ------ 函数导致索引失效

EXPLAIN SELECT * FROM tb1 WHERE int_1 + 1 = 2;
* Using where ------ 计算导致索引失效 -- 为什么不优化了

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 2 - 1;
* key_len = 4 ------------ 使用索引

EXPLAIN SELECT * FROM tb1 WHERE int_1 != 1;
* Using where ------------ != 导致索引失效

# 3.1.2 只使用索引列 (单列索引, 字符串)
CALL drop_index("test", "tb1");
CREATE  INDEX index_str_1 ON tb1(str_1);

EXPLAIN SELECT * FROM tb1 WHERE str_1 = '1';
* key_len = 82 ------------ 使用索引

EXPLAIN SELECT * FROM tb1 WHERE str_1 =  1;
* Using where ------ 类型转换导致索引失效 --- 为什么这个不优化了 -- 字符串转整型 不是 一对一的

EXPLAIN SELECT * FROM tb1 WHERE UPPER(str_1) = '1';
* Using where ------ 函数导致索引失效

EXPLAIN SELECT * FROM tb1 WHERE str_1 LIKE '%1';
EXPLAIN SELECT * FROM tb1 WHERE str_1 LIKE '%1';
* Using where ------ like % 开头导致索引失效

EXPLAIN SELECT * FROM tb1 WHERE str_1 LIKE '1%';
EXPLAIN SELECT * FROM tb1 WHERE str_1 LIKE '.1';
EXPLAIN SELECT * FROM tb1 WHERE str_1 LIKE '.1';
* Using index condition --- like 非 % 开头 使用索引下推

# 3.1.3 只使用索引列 (联合索引)
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2, int_3);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1; 
* key_len = 4 ----- 使用部分索引
                                                       
EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1;
* key_len = 0 ----- 不满足最左前缀原则
* Using where ----- 使用全表扫描

EXPLAIN SELECT * FROM tb1 WHERE int_3 = 1;
* key_len = 0 ----- 不满足最左前缀原则
* Using where ----- 使用全表扫描

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2 = 2;
* key_len = 8 ----- 使用部分索引

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_3 = 3;
* key_len = 4 ------------- 使用部分索引
* Using index condition --- 索引下推

EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1 AND int_3 = 1;
* key_len = 0 ----- 不满足最左前缀原则
* Using where ----- 使用全表扫描

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2 = 1 AND int_3 = 1;
* key_len = 8 ------------- 使用全部索引

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2  > 1 AND int_3 = 1;
* key_len = 8 ------------- 范围查找导致右侧索引实现, 不是书写的右侧, 而是联合索引的右侧
* Using index condition --- 使用索引下推
* 建立联合索引时, 建议将范围查找放到末尾

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2  = 1 AND int_3 > 1;
* key_len = 12 ------------ 使用完整索引
* Using index condition --- 使用索引下推
* 建立联合索引时, 建议将范围查找放到末尾

# 3.1.4 包含非索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_int_1 ON tb1(int_1);
CREATE  INDEX index_int_2 ON tb1(int_2);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 OR int_2 = 1;
* Using union(index_int_1,index_int_2) --- OR 两侧的列都包含索引, 所以使用两个索引
* Using where ---------------------------- 拆成两个查询然后合并

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 OR int_3 = 1;
* Using where --- OR 一侧不包含索引, 所以使用全表扫描

EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1 OR int_3 = 1;
* Using where --- OR 一侧不包含索引, 所以使用全表扫描
```

#### 3.2 只在 GROUP BY 中使用索引 -- 避免使用临时表
```
# 3.2.1 只使用索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2, int_3);

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1;
* key_len = 12
* Using index --- 索引覆盖

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_2;
* key_len = 12
* Using index -------- 索引覆盖
* Using temporary ---- 使用临时表

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_3;
* key_len = 12
* Using index -------- 索引覆盖
* Using temporary ---- 使用临时表

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1, int_2;
* key_len = 12
* Using index --- 索引覆盖

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1, int_3;
* key_len = 12
* Using index -------- 索引覆盖
* Using temporary ---- 使用临时表

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_2, int_3;
* key_len = 12
* Using index -------- 索引覆盖
* Using temporary ---- 使用临时表

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1, int_2, int_3;
* key_len = 12
* Using index --- 索引覆盖

# 3.2.2 包含非索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1);

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1, int_2;
* Using temporary ------ 使用临时表
```

#### 3.3 只在 ORDER BY 中使用索引 --- 避免文件排序
```
# 3.3.1 只使用索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2, int_3);

EXPLAIN SELECT * FROM tb1 ORDER BY int_1 LIMIT 10;
* key_len = 12 --- 使用完整索引

EXPLAIN SELECT * FROM tb1 ORDER BY int_2 LIMIT 10;
* Using filesort ---- 不满足最左前缀原则, 文件排序

EXPLAIN SELECT * FROM tb1 ORDER BY int_3 LIMIT 10;
* Using filesort ---- 不满足最左前缀原则, 文件排序

EXPLAIN SELECT * FROM tb1 ORDER BY int_1, int_2 LIMIT 10;
* key_len = 12 --- 使用完整索引

EXPLAIN SELECT * FROM tb1 ORDER BY int_1, int_3 LIMIT 10;
* Using filesort ---- 回表太多, 所以直接使用文件排序 (不一定)

EXPLAIN SELECT * FROM tb1 ORDER BY int_2, int_3 LIMIT 10;
* Using filesort ---- 不满足最左前缀原则, 文件排序

EXPLAIN SELECT * FROM tb1 ORDER BY int_1, int_2, int_3 LIMIT 10;
* key_len = 12 --- 使用完整索引

# 3.3.2 包含非索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1);

EXPLAIN SELECT * FROM tb1 ORDER BY int_1, int_2 LIMIT 10;
* Using filesort ---- 使用文件排序
```

#### 3.4 只在 distinct 中使用索引
```
# 3.4.1 只使用索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2, int_3);

EXPLAIN SELECT DISTINCT int_1 FROM tb1;
* key_len = 4 ----------------- 使用部分索引
* Using index for group-by ---- 使用索引分组

EXPLAIN SELECT DISTINCT int_2 FROM tb1;
* key_len = 12 ------------- 使用全部索引
* Using index -------------- 使用索引覆盖
* Using temporary ---------- 使用临时表

EXPLAIN SELECT DISTINCT int_3 FROM tb1;
* key_len = 12 ------------- 使用全部索引
* Using index -------------- 使用索引覆盖
* Using temporary ---------- 使用临时表

EXPLAIN SELECT DISTINCT int_1, int_2 FROM tb1;
* key_len = 12 ------------- 使用全部索引
* Using index -------------- 使用索引覆盖

EXPLAIN SELECT DISTINCT int_1, int_3 FROM tb1;
* key_len = 12 ------------- 使用全部索引
* Using index -------------- 使用索引覆盖
* Using temporary ---------- 使用临时表

EXPLAIN SELECT DISTINCT int_2, int_3 FROM tb1;
* key_len = 12 ------------- 使用全部索引
* Using index -------------- 使用索引覆盖
* Using temporary ---------- 使用临时表

EXPLAIN SELECT DISTINCT int_1, int_2, int_3 FROM tb1;
* key_len = 12 ------------- 使用全部索引
* Using index -------------- 使用索引覆盖

# 3.4.2 包含非索引列
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1);

EXPLAIN SELECT DISTINCT int_1, int_2 FROM tb1;
* Using temporary ---------- 使用临时表
```

#### 3.5 where 和 group by 中同时使用
```
# 3.5.1 同时使用联合索引
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2);

EXPLAIN SELECT count(*) FROM tb1 WHERE int_1 = 1 GROUP BY int_2;
* key_len = 4 ---------- 使用索引
* Using index ---------- 使用索引覆盖

EXPLAIN SELECT count(*) FROM tb1 WHERE int_1 > 1 GROUP BY int_2;
* key_len = 4 ---------- 使用索引
* Using where ---------- 存在联合索引, 但只能使用部分, int_2 不能使用
* Using index ---------- 使用索引覆盖
* Using temporary ------ 使用临时表

# 3.5.2 WHERE 有索引, GROUP BY 没索引
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1);

EXPLAIN SELECT count(*) FROM tb1 WHERE int_1 = 1 GROUP BY int_2;
* key_len = 4 ---------- 使用索引
* Using temporary ------ 使用临时表

# 3.5.3 WHERE 没有索引, GROUP BY 有索引
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_2);

EXPLAIN SELECT count(*) FROM tb1 WHERE int_1 = 1 GROUP BY int_2;
* 优化成, 先分组, 再 WHERE
* key_len = 4 ---------- 使用索引
* Using where ---------- WHERE 不使用索引

其他组合类似, 就不一个一个测试了
```

#### 3.6 测试降序索引
```
# 3.6.1 单列使用 效果不明显
CALL drop_index("test", "tb1");
CREATE  INDEX index_name_1 ON tb1(int_1);
CREATE  INDEX index_name_2 ON tb1(int_2 DESC);

EXPLAIN SELECT * FROM tb1 ORDER BY int_1      LIMIT 10; # 0.174s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1 DESC LIMIT 10; # 0.181s
EXPLAIN SELECT * FROM tb1 ORDER BY int_2      LIMIT 10; # 0.181s
EXPLAIN SELECT * FROM tb1 ORDER BY int_2 DESC LIMIT 10; # 0.179s

# 3.6.2 联合索引 效果明显
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2);

EXPLAIN SELECT * FROM tb1 ORDER BY int_1,      int_2      LIMIT 10; # 0.178s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1,      int_2 DESC LIMIT 10; # 0.511s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1 DESC, int_2      LIMIT 10; # 0.505s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1 DESC, int_2 DESC LIMIT 10; # 0.176s

CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2 DESC);

EXPLAIN SELECT * FROM tb1 ORDER BY int_1,      int_2      LIMIT 10; # 0.508s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1,      int_2 DESC LIMIT 10; # 0.183s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1 DESC, int_2      LIMIT 10; # 0.181s
EXPLAIN SELECT * FROM tb1 ORDER BY int_1 DESC, int_2 DESC LIMIT 10; # 0.512s
```

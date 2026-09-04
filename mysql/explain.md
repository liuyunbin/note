
## 1. 准备测试数据
```
# 1.1 创建三张表
DROP   TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id    INT AUTO_INCREMENT PRIMARY KEY, 
    int_1 INT,
    int_2 INT NOT NULL,
    int_3 INT,
    str_1 VARCHAR(20) NOT NULL,
    str_2 VARCHAR(20) NOT NULL,
    str_3 VARCHAR(20) NOT NULL
);

DROP   TABLE IF EXISTS tb2;
CREATE TABLE tb2 (
    id    INT AUTO_INCREMENT PRIMARY KEY, 
    int_1 INT,
    int_2 INT NOT NULL,
    int_3 INT,
    str_1 VARCHAR(20) NOT NULL,
    str_2 VARCHAR(20) NOT NULL,
    str_3 VARCHAR(20) NOT NULL
);

DROP   TABLE IF EXISTS tb3;
CREATE TABLE tb3 (
    id    INT AUTO_INCREMENT PRIMARY KEY, 
    int_1 INT,
    int_2 INT NOT NULL,
    int_3 INT,
    str_1 VARCHAR(20) NOT NULL,
    str_2 VARCHAR(20) NOT NULL,
    str_3 VARCHAR(20) NOT NULL
);

# 1.2 创建帮助函数
# 1.2.1 返回随机字符串
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

# 1.2.2 返回随机数字
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

# 1.2.3 插入数据 
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

# 1.2.4 清除除主键外的所有索引
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

# 1.3 插入数据
TRUNCATE tb1;
CALL insert_table(1000000, "tb1"); # 100 万数据, 140.456s
SELECT count(*) FROM tb1;

TRUNCATE tb2;
CALL insert_table(2000000, "tb2"); # 200 万数据, 262.668s
SELECT count(*) FROM tb2;

TRUNCATE tb3;
CALL insert_table(3000000, "tb3"); # 300 万数据, 393.302s
SELECT count(*) FROM tb3;
```

## 2. 输出的各个字段的值
#### 2.1 id -- 每个 SELECT 关键字都对应一个唯一的id, 临时表也会有
```
EXPLAIN SELECT * FROM tb1;                                                # 一张表
EXPLAIN SELECT * FROM tb1, tb2;                                           # 两张表
EXPLAIN SELECT * FROM tb1 UNION     SELECT * FROM tb2;                    # 两张表 + 临时表
EXPLAIN SELECT * FROM tb1 UNION ALL SELECT * FROM tb2;                    # 两张表
EXPLAIN SELECT * FROM tb1 WHERE id = (SELECT id FROM tb2 WHERE id = 123); # 两张表, 子查询
```

#### 2.2 select_type -- 查询的类型
```
# 2.2.1 SIMPLE --------- 不包含 UNION 或者子查询
EXPLAIN SELECT * FROM tb1;
EXPLAIN SELECT * FROM tb1, tb2;

# 2.2.2 PRIMARY -------- 包含 UNION 和 UNION ALL 和 子查询的主查询
EXPLAIN SELECT * FROM tb1 UNION     SELECT * FROM tb2;
EXPLAIN SELECT * FROM tb1 UNION ALL SELECT * FROM tb2;
EXPLAIN SELECT * FROM tb1 WHERE id = (SELECT id FROM tb2 WHERE id = 123);

# 2.2.3 UNION  --------- UNION 和 UNION ALL 的非第一个查询 (不相关)
EXPLAIN SELECT * FROM tb1 UNION     SELECT * FROM tb2;
EXPLAIN SELECT * FROM tb1 UNION ALL SELECT * FROM tb2;

# 2.2.4 DEPENDENT UNION ------- UNION 和 UNION ALL 的非第一个查询 (相关)
EXPLAIN
SELECT * FROM tb1 WHERE id IN (
    SELECT id FROM tb2 WHERE tb1.id = tb2.id
    UNION ALL
    SELECT id FROM tb3 WHERE tb1.id = tb3.id
);
   
# 2.2.5 UNION RESULT --- UNION 去重的临时表
EXPLAIN SELECT * FROM tb1 UNION     SELECT * FROM tb2;

# 2.2.6 SUBQUERY ------------ 子查询中的小查询 (不相关)
EXPLAIN
SELECT * FROM tb1 WHERE id = (SELECT id FROM tb2 WHERE tb2.id = 123);

# 2.2.7 DEPENDENT SUBQUERY ---- 子查询中的小查询 (相关)
EXPLAIN
SELECT * FROM tb1 WHERE id = (SELECT id FROM tb2 WHERE tb2.id = tb1.id);

# 2.2.8 DERIVED ---------------- 派生表 (不相关)
EXPLAIN SELECT * FROM (SELECT * FROM tb1 UNION SELECT * FROM tb2) t1;

# 2.2.9 DEPENDENT DERIVED ---------------- 派生表 (相关)
EXPLAIN SELECT * FROM tb1 WHERE id in (
    SELECT id FROM (
        SELECT * FROM tb2 WHERE tb2.id = tb1.id
        UNION ALL
        SELECT * FROM tb3 WHERE tb3.id = tb1.id
    ) t1);

# 2.2.10 MATERIALIZED ----------- 把子查询优化成连接查询
EXPLAIN SELECT * FROM tb1 WHERE int_1 IN (SELECT int_1 FROM tb2);

# 2.2.11 UNCACHEABLE SUBQUERY --- 是否可以缓存子查询

# 2.2.12 UNCACHEABLE UNION ------ 是否可以缓存 union
```

#### 2.3 table -- 表名, 每张表一行记录, 临时表也会记录
```
EXPLAIN SELECT * FROM tb1;                                                # 一张表 
EXPLAIN SELECT * FROM tb1, tb2;                                           # 两张表
EXPLAIN SELECT * FROM tb1 UNION     SELECT * FROM tb2;                    # 两张表 + 临时表
EXPLAIN SELECT * FROM tb1 UNION ALL SELECT * FROM tb2;                    # 两张表
EXPLAIN SELECT * FROM tb1 WHERE id = (SELECT id FROM tb2 WHERE id = 123); # 两张表, 子查询
```

#### 2.4 partitions --- 分区表中的命中情况

#### 2.5 type -- 针对单表的访问方法
```
# 2.5.1 system --- 只有一条记录, 精确
DROP    TABLE IF EXISTS student;
CREATE  TABLE student (id INT, name VARCHAR(20));
INSERT  INTO  student VALUES(1, 'abc');
EXPLAIN SELECT * FROM student;   # InnoDB 不使用
ALTER  TABLE student ENGINE = MyISAM;
EXPLAIN SELECT * FROM student;   # MyISAM 使用

# 2.5.2 const ---- 常量 与主键或唯一键 等值匹配 --- 最多取一个
EXPLAIN SELECT * FROM tb1 WHERE id = 1;

# 2.5.3 eq_ref --- 连接查询 或 子查询时，被驱动表 使用主键 或 唯一键 进行字段等值匹配
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.id    = tb2.id;
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.id;
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.id    = tb2.int_1;

# 2.5.4 ref ------ 常数或另一表中的字段 与普通索引等值匹配 
CALL drop_index("test", "tb1");
CREATE INDEX index_name on tb1(int_1);

EXPLAIN SELECT * FROM tb1      WHERE tb1.int_1 = 123; 
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1;

CALL drop_index("test", "tb1");

# 2.5.5 fulltext ----- 全文索引

# 2.5.6 ref_or_null -- 常数或另一表中的字段 与普通索引等值匹配 或 NULL
CALL drop_index("test", "tb1");
CREATE INDEX index_name on tb1(int_1);

EXPLAIN SELECT * FROM tb1      WHERE tb1.int_1 = 123       OR tb1.int_1 IS NULL;
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1 OR tb1.int_1 IS NULL;

CALL drop_index("test", "tb1");

# 2.5.7 index_merge -- 索引合并
CALL drop_index("test", "tb1");
CREATE INDEX index_int_1 on tb1(int_1);
CREATE INDEX index_int_2 on tb1(int_2);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 123 OR  int_2 = 123;
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 123 AND int_2 = 123;

CALL drop_index("test", "tb1");

# 2.5.8 unique_subquery --- (IN  + 子查询) 转化成 (EXISTS + 子查询) (主键或唯一键)
EXPLAIN SELECT * FROM tb1 WHERE int_1 NOT IN (SELECT id FROM tb2 WHERE tb1.str_1 LIKE '123%');
EXPLAIN SELECT * FROM tb1 WHERE int_1 NOT IN (SELECT id FROM tb2 WHERE tb1.id != 123);

# 2.5.9 index_subquery ---- (IN  + 子查询) 转化成 (EXISTS + 子查询) (普通索引)
CALL drop_index("test", "tb2");
CREATE INDEX index_int_1 on tb2(int_1);
EXPLAIN SELECT * FROM tb1 WHERE int_1 NOT IN (SELECT int_1 FROM tb2 WHERE tb1.id != 123);

CALL drop_index("test", "tb2");

# 2.5.10 range --- 使用索引范围查找
EXPLAIN SELECT * FROM tb1 WHERE id IN (1, 2, 3);
EXPLAIN SELECT * FROM tb1 WHERE id > 1 AND id < 3;

# 2.5.11 index
* 复合索引
* 查找时索引不是第一个字段
* 不需要回表, 只用索引就能满足要求

CALL drop_index("test", "tb1");
CREATE INDEX index_int_1_2_3 on tb1(int_1, int_2, int_3);

EXPLAIN SELECT int_2 FROM tb1 WHERE int_3 = 123;

CALL drop_index("test", "tb1");

# 2.5.12 ALL: 全表扫描
EXPLAIN SELECT * FROM tb1;
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 123;

# 2.5.13 结果值从最好到最坏依次是
system > const > eq_ref > ref > ref_or_null > index_merge 
> unique_subquery > index_subquery > range > index > ALL 

至少要达到 range 级别，要求是 ref 级别，最好是 consts级别
```

### 2.6 possible_keys --- 可能用到的索引

### 2.7 key ------------- 实际上使用的索引

### 2.8 key_len ------------- 实际使用到的索引长度 (对联合索引意义比较大)

### 2.9 ref ----------------- 比较时, 对方的类型
```
EXPLAIN SELECT * FROM tb1 WHERE id = 123;
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.id = tb2.id;
```

### 2.10 rows --------------- 预估的需要读取的记录条数

### 2.11 filtered ----------- 某个表经过搜索条件过滤后剩余记录条数的百分比

### 2.12 Extra -------------- 一些额外的信息
```
# 2.12.1 Backward index scan -- 索引是正序的, 但以降序排序查找使用 -- 貌似对效率影响不大
CALL drop_index("test", "tb1");
CREATE INDEX index_name on tb1(int_1);

EXPLAIN SELECT * FROM tb1 ORDER BY id;      # 1.608s
EXPLAIN SELECT * FROM tb1 ORDER BY id DESC; # 1.592s

EXPLAIN SELECT * FROM tb1 ORDER BY int_1      LIMIT 10; # 0.189
EXPLAIN SELECT * FROM tb1 ORDER BY int_1 DESC LIMIT 10; # 0.188s

CALL drop_index("test", "tb1");

# 2.12.2 Child of 'table' pushed join@1 -- NDB tables only

# 2.12.3 const row not found -- 空表 -- 未复现

# 2.12.4 Deleting all rows --- 删除所有行 -- 未复现

# 2.12.5 Distinct ---- 没看懂

# 2.12.6 FirstMatch(tbl_name) --- 没看懂

# 2.12.7 Full scan on NULL key -- 没看懂

# 2.12.8 Impossible HAVING --- 不可能的 HAVING
EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1 HAVING 1 = 0;

# 2.12.9 Impossible WHERE --- 不可能的 WHERE
EXPLAIN SELECT count(*) FROM tb1 WHERE 1 = 0;

# 2.12.10 Impossible WHERE noticed after reading const tables 
                 -- 使用 const 或 system 扫描表后, 发现 WHERE 不可能

EXPLAIN SELECT * FROM tb1 WHERE id = 111 AND int_1 = 111;

# 2.12.11 LooseScan(m..n) ---- 没看懂

# 2.12.12 No matching min/max row -- 有 MIN 或者 MAX 聚合函数，但是没有符合 WHERE的搜索条件的记录
EXPLAIN SELECT max(id) FROM tb1 WHERE id < 0;

# 2.12.13 no matching row in const table --- 唯一键或主键比较时, 匹配不到数据
EXPLAIN SELECT * FROM tb1 JOIN tb2 ON tb1.id = tb2.int_2 AND tb2.int_2 = NULL;
EXPLAIN SELECT id FROM tb1 WHERE id = -1;

# 2.12.14 No matching rows after partition pruning --- 没看懂

# 2.12.15 No tables used --- 未选择表
EXPLAIN SELECT 1;

# 2.12.16 Not exists --- 左连接 条件不可能满足
EXPLAIN SELECT * FROM tb1  LEFT JOIN tb2 ON tb1.int_1 = tb2.int_1 WHERE tb2.id IS NULL;

# 2.12.17 Plan is not ready yet --- 优化器还未准备好, 未复现

# 2.12.18 Range checked for each record (index map: N) --- 索引不可以, 尝试转化为范围查找 --- 未复现

# 2.12.19 Recursive --- 递归共同用表表达式
EXPLAIN
WITH RECURSIVE cte 
AS 
(
    SELECT id, int_1, 1 AS n FROM tb1 WHERE id = 123
    UNION ALL
    SELECT a.id, a.int_1, n + 1
    FROM tb1 AS a JOIN cte
    ON (a.int_1 = cte.int_1)
)
SELECT id FROM cte WHERE n = 4;

# 2.12.20 Rematerialize --- 没看懂

# 2.12.21 Scanned N databases --- 没看懂

# 2.12.22 Select tables optimized away
* 返回的行数最多一行
* 处理的行数是确定的
* 单独的可以只通过索引实现, 不需要回表

CALL drop_index("test", "tb1");
CREATE INDEX index_int_1 on tb1(int_1);
CREATE INDEX index_int_2 on tb1(int_2);

EXPLAIN SELECT max(id), min(int_1), min(int_2) FROM tb1; # 可以优化成只使用 索引表 实现
                                                         # 先单独求, 然后合并
EXPLAIN SELECT max(id), min(int_1), min(int_2) FROM tb1 WHERE int_1 > 100;
                                                         # 这个不行, 因为每组的结果不确定
CALL drop_index("test", "tb1");

CREATE INDEX index_int_1_int_2 on tb1(int_1, int_2);
EXPLAIN SELECT max(int_2) FROM tb1 WHERE int_1 = 100; # 这个也可以

CALL drop_index("test", "tb1");

# 2.12.23 Skip_open_table, Open_frm_only, Open_full_table --- 没看懂

# 2.12.24 Start temporary, End temporary -- 没看懂

# 2.12.25 unique row not found -- 没看懂

# 2.12.26 Using filesort -- 使用文件排序, 使用内存或磁盘排序 --- 尽量避免
EXPLAIN SELECT * FROM tb1 ORDER BY int_1;

# 2.12.27 Using index ----- 使用索引即可完成要求, 不需要回表
CALL drop_index("test", "tb1");
CREATE INDEX index_name ON tb1(int_1);
EXPLAIN SELECT int_1 FROM tb1 WHERE int_1 = 123;
CALL drop_index("test", "tb1");

# 2.12.28 Using index condition --  Index Condition Pushdown 索引条件下推
* 通过索引列的判断, 减少回表的次数 (不包括主键和唯一键)

CALL drop_index("test", "tb1");
CREATE INDEX index_name ON tb1(int_1);

EXPLAIN SELECT * FROM tb1 WHERE int_1 > 1000 AND int_1 < 2000;

CALL drop_index("test", "tb1");

EXPLAIN SELECT * FROM tb1 WHERE id > 1000 AND id < 2000; # 主键不会 

# 2.12.29 Using index for group-by --- GROUP BY 中使用索引优化
CALL drop_index("test", "tb1");
CREATE INDEX index_name ON tb1(int_1);

EXPLAIN SELECT int_1 FROM tb1 GROUP BY int_1;

CALL drop_index("test", "tb1");

# 2.12.30 Using index for skip scan --- 使用索引跳过扫描

# 2.12.31  连接查询执行过程中, 可能分配新内存提高效率
# 2.12.31.1 Using join buffer (Block Nested Loop)
# 2.12.31.2 Using join buffer (Batched Key Access)
# 2.12.31.3 Using join buffer (hash join) 

# 2.12.32 Using MRR --- 没看懂

# 2.12.33 多个索引同时使用
# 2.12.33.1 Using intersect(...) --- 交集
CALL drop_index("test", "tb1");
CREATE INDEX index_int_1 on tb1(int_1);
CREATE INDEX index_int_2 on tb1(int_2);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 123 AND int_2 = 123;

CALL drop_index("test", "tb1");

# 2.12.33.2 Using union(...) --- 并集
CALL drop_index("test", "tb1");
CREATE INDEX index_int_1 on tb1(int_1);
CREATE INDEX index_int_2 on tb1(int_2);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 123 OR int_2 = 123;

CALL drop_index("test", "tb1");

# 2.12.33.3 Using sort_union(...) --- 包含范围查找的并集
CALL drop_index("test", "tb1");
CREATE INDEX index_int_1 on tb1(int_1);
CREATE INDEX index_int_2 on tb1(int_2);

EXPLAIN SELECT * FROM tb1 WHERE int_1 < 123 OR int_2 = 123;

CALL drop_index("test", "tb1");

# 2.12.34 Using temporary --- 使用临时表 -- 这个尽量少
EXPLAIN
SELECT * FROM tb1
UNION
SELECT * FROM tb2;

# 2.12.35 Using where ----- WHERE 包含非索引列
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 111;
EXPLAIN SELECT * FROM tb1 WHERE id = 111 OR  int_1 = 111;

# 2.12.36 Using where with pushed condition -- NDB tables only

# 2.12.37 Zero limit -- 取零项
EXPLAIN SELECT * FROM tb1 LIMIT 0;
```

## 3. 输出格式
```
EXPLAIN             SELECT * FROM teacher1;
EXPLAIN FORMAT=JSON SELECT * FROM teacher1; # JSON
EXPLAIN FORMAT=tree SELECT * FROM teacher1; # TREE
```

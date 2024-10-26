
# INDEX --- 索引
## 0. 总结
```
* 类型
    * 普通索引 --- 无任何限制
    * 唯一索引 --- 和 唯一键 对应
    * 主键索引 --- 和   主键 对应 -- 最好保持全局的唯一性(不单是该表中)
    * 全文索引 --- 很少使用
    * 空间索引 --- 很少使用
* 范围
    * 单列索引
    * 多列索引
        * 最左前缀原则
        * 最常用的放最左边
        * 范围查找放最右边
    * 联合索引好于多个单列索引
* 实现
  * 聚簇索引 ----- 主键 -- 只有一个
  * 非聚簇索引 --- 可以多个. 需要回表
* 新特性
  * 降序索引 ----- 如果查找是降序的话, 可以提高效率 --- DESC
  * 隐藏索引 ----- 便于观察删除索引的影响 --- INVISIBLE VISIBLE
* 适合建索引
    * WHERE GROUP BY ORDER BY 中频繁使用
    * 区分度大的列
    * DISTINCT 列
    * 很少变化的列
* 不适合建索引
    * 表很小
* 删除无用或冗余的索引
* WHERE 中使用索引 ------ 避免全表扫描
* ORDER BY 中使用索引 --- 避免文件排序
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

## 3. 测试 WHERE 中使用索引 --- 避免全表扫描
```
# 3.1 最左前缀原则
CALL drop_index("test", "tb1");
CREATE  INDEX index_name ON tb1(int_1, int_2, int_3);     # 
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1;                # 使用部分索引 (key_len = 4)
EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1;                # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE int_3 = 1;                # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2 = 2;  # 使用部分索引 (key_len = 8)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_3 = 3;  # 使用部分索引 (key_len = 4)
EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1 AND int_3 = 1;  # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2 = 1 AND int_3 = 1;
                                                          # 使用全部索引 (key_len = 12)

# 3.2 使用计算, 函数和类型转换导致索引失效
CALL drop_index("test", "tb1");
EXPLAIN SELECT * FROM tb1 WHERE str_1 = '1';          #
CREATE  INDEX index_name ON tb1(str_1);               #
EXPLAIN SELECT * FROM tb1 WHERE str_1 = '1';          #
EXPLAIN SELECT * FROM tb1 WHERE str_1 =  1;           # 类型转换导致索引失效
EXPLAIN SELECT * FROM tb1 WHERE UPPER(str_1) = '1';   # 函数导致索引失效

CALL drop_index("test", "tb1");
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1;     #
CREATE  INDEX index_t1 ON tb1(int_1);          #
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1;     #
EXPLAIN SELECT * FROM tb1 WHERE int_1 + 1 = 2; # 计算导致索引失效

CALL drop_index("test", "tb1");

# 3.3 范围查找导致右侧的索引失效 (> >= < <= != LIKE)
CALL drop_index("test", "tb1");
CREATE  INDEX index_t1_t2_t3 ON tb1(int_1, int_2, int_3);              #
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2  = 1 AND int_3 = 1; # 使用全部索引(key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2  > 1 AND int_3 = 1; # 使用部分索引(key_len = 8)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2 != 1 AND int_3 = 1; # 使用部分索引(key_len = 8)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_3  = 1 AND int_2 > 1; # 使用部分索引(key_len = 8)
                                                         # 联合索引按照声明的顺序使用
CALL drop_index("test", "tb1");                                       
CREATE  INDEX index_t1_t2_t3 ON tb1(int_1, int_3, int_2);              # 修改联合索引声明的顺序
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2  = 1 AND int_3 = 1; # 使用全部索引(key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2  > 1 AND int_3 = 1; # 使用全部索引(key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_2 != 1 AND int_3 = 1; # 使用部分索引(key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1 AND int_3  = 1 AND int_2 > 1; # 使用全部索引(key_len = 12)
                                                         # 建立联合索引时, 将范围查找的字段放到末尾
CALL drop_index("test", "tb1");

# 3.4 测试 OR, 一边不包含索引时, 导致索引失效
CALL drop_index("test", "tb1");

CREATE INDEX index_t1 ON tb1(int_1);
CREATE INDEX index_t2 ON tb1(int_2);

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1000;
EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1000;
EXPLAIN SELECT * FROM tb1 WHERE int_3 = 1000;

EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1000 OR int_2 = 1000; #   联合索引
EXPLAIN SELECT * FROM tb1 WHERE int_1 = 1000 OR int_3 = 1000; # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE int_2 = 1000 OR int_3 = 1000; # 不使用索引

CALL drop_index("test", "tb1");
```

## 3. 测试 group by 分组优化
```
CALL drop_index("test", "tb1");

EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1, int_2, int_3;
CREATE INDEX index_t1_t2_t3 ON tb1(int_1, int_2, int_3);
EXPLAIN SELECT count(*) FROM tb1 GROUP BY int_1, int_2, int_3;
EXPLAIN SELECT count(*) FROM tb1 GROUP BY        int_2, int_3; # 这个也会使用

CALL drop_index("test", "tb1");
```

## 4. 测试 order by 中使用索引 --- 避免文件排序
```
CALL drop_index("test", "tb1");

EXPLAIN SELECT * FROM tb1 ORDER BY int_1, int_2, int_3 LIMIT 10; # 文件排序
CREATE INDEX index_t1_t2_t3 ON tb1(int_1, int_2, int_3);
EXPLAIN SELECT * FROM tb1 ORDER BY int_1, int_2, int_3 LIMIT 10; # 索引排序
EXPLAIN SELECT * FROM tb1 ORDER BY        int_2, int_3 LIMIT 10; # 不满足最左前缀原则, 文件排序

CALL drop_index("test", "tb1");
```

## 5. 测试 distinct 中使用索引
```
CALL drop_index("test", "tb1");

EXPLAIN SELECT DISTINCT int_1, int_2, int_3 FROM tb1; # 临时表
CREATE INDEX index_t1 ON tb1(int_1, int_2, int_3);
EXPLAIN SELECT DISTINCT int_1, int_2, int_3 FROM tb1; # 索引
EXPLAIN SELECT DISTINCT        int_2, int_3 FROM tb1; # 索引 + 临时表

CALL drop_index("test", "tb1");
```

## 6. 索引覆盖 -- 不需要回表
```
CALL drop_index("test", "tb1");

CREATE INDEX index_t1 ON tb1(int_1, int_2, int_3);
EXPLAIN SELECT int_1, int_2, int_3        FROM tb1 WHERE int_1 = 1; # 索引覆盖, 不需要回表
EXPLAIN SELECT int_1, int_2, int_3, str_1 FROM tb1 WHERE int_1 = 1; # 需要回表

CALL drop_index("test", "tb1");
```

## 7. 测试多表查询 (左连接 或 右连接)
```
CALL drop_index("test", "tb1");
CALL drop_index("test", "tb2");

EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.int_1 = tb2.int_1;
                                                    # 1. 查看左连接 (全表扫描)
CREATE  INDEX index_t1 ON tb1(int_1);               # 2. 在驱动表上建立索引, 意义不大 (可能被优化成内连接)
EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.int_1 = tb2.int_1;
                                                    # 3. 查看左连接 (全表扫描)
CREATE  INDEX index_t1 ON tb2(int_1);               # 4. 在被驱动表上建立索引, 有用
EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.int_1 = tb2.int_1;
                                                    # 5. 查看左连接 (被驱动表使用 ref)
DROP    INDEX index_t1 ON tb1;                      # 6. 删除驱动表上的索引
EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.int_1 = tb2.int_1;
                                                    # 7. 查看左连接 (被驱动表使用 ref)
                                                    
CALL drop_index("test", "tb1");
CALL drop_index("test", "tb2");
```

## 8. 测试多表查询 (内连接) (最好小表驱动大表) (没索引的驱动有索引的)
```
CALL drop_index("test", "tb1");
CALL drop_index("test", "tb2");

EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1;
                                                    # 1. 查看内连接 (全表扫描)
CREATE  INDEX index_t1 ON tb1(int_1);               # 2. 在 tb1 建立索引 (小表)
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1;
                                                    # 3. 查看内连接 (大表驱动小表)
CREATE  INDEX index_t1 ON tb2(int_1);               # 4. 在 tb2 建立索引 (大表)
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1;
                                                    # 5. 查看内连接 (大表驱动小表) (why)
DROP    INDEX index_t1 ON tb1;                      # 6. 删除 tb1 上的索引 (小表)
EXPLAIN SELECT * FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1;
                                                    # 7. 查看内连接 (小表驱动大表)
CALL drop_index("test", "tb1");
CALL drop_index("test", "tb2");
```

## 10. 子查询优化
```
EXPLAIN SELECT tb1.* FROM tb1 WHERE int_2 = (SELECT int_2 FROM tb2 WHERE tb2.int_1 = tb1.int_1); # 子查询
EXPLAIN SELECT tb1.* FROM tb1, tb2 WHERE tb1.int_1 = tb2.int_1 AND tb1.int_2 = tb2.int_2; # 多表查询 (建议)
```

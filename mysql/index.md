
## INDEX --- 索引
```
* 类型
  * 普通索引 ----- 无任何限制
  * 唯一索引 ----- 和 唯一键 对应
  * 主键索引 ----- 和   主键 对应
  * 全文索引 ----- 很少使用
  * 空间索引 ----- 很少使用
* 范围
  * 单列索引 -----
  * 多列索引 ----- 最左前缀原则 -- 最常用的放最左边
* 实现
  * 聚簇索引 ----- 主键 -- 只有一个
  * 非聚簇索引 --- 可以多个
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
* 联合索引好于多个单列索引
* 删除无用或冗余的索引
* 联合索引
    * 区分度大的列放到前面
    * 范围查找的列放最后
```

## 1. 基础
```
# 1. 创建
# 1.1 单列: 不指定索引名称: 索引名称默认是列名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id));
SHOW   INDEX FROM student;

# 1.2 单列: 指定索引名称
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;

# 1.3 多列: 不指定索引名称: 索引名称默认是第一个列名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX(id, name));
SHOW   INDEX FROM student;

# 1.4 多列: 指定索引名称
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX index_name(id, name));
SHOW   INDEX FROM student;

# 1.5 单列: 指定降序索引
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id DESC));
SHOW   INDEX FROM student;

# 1.6 单列: 指定不可见索引
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id) INVISIBLE);
SHOW   INDEX FROM student;

# 2. 添加
# 2.1 使用 CREATE INDEX 添加 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
CREATE INDEX index_name ON student(id);
SHOW   INDEX FROM student;

# 2.2 使用 ALTER 添加
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
ALTER  TABLE student ADD INDEX index_name(id);
SHOW   INDEX FROM student;

# 3. 修改
# 3.1 设置索引是否可见
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name INVISIBLE;
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name VISIBLE;
SHOW   INDEX FROM student;

# 4. 删除
# 4.1 使用 DROP (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
DROP   INDEX index_name ON student;
SHOW   INDEX FROM student;

# 4.2 使用 ALTER
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX index_name;
SHOW   INDEX FROM student;

# 5. 重命名索引
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student RENAME INDEX index_name TO new_index_name;
SHOW   INDEX FROM student;
```

## 2. 测试最左前缀原则
```
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id INT PRIMARY KEY AUTO_INCREMENT,
    t1 INT NOT NULL,
    t2 INT NOT NULL,
    t3 INT NOT NULL,
    t4 INT);

CREATE INDEX index_t1_t2_t3 ON tb1(t1, t2, t3);
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1;                       # 使用部分索引, t1 的索引 (key_len = 4)
EXPLAIN SELECT * FROM tb1 WHERE t2 = 1;                       # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE t3 = 1;                       # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t2 = 1;            # 使用部分索引, t1 t2 的索引 (key_len = 8)
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t3 = 1;            # 使用部分索引, t1 的索引 (key_len = 4)
EXPLAIN SELECT * FROM tb1 WHERE t2 = 1 AND t3 = 1;            # 不使用索引
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t2 = 1 AND t3 = 1; # 使用全部索引 (key_len = 12)
```

## 3. 使用计算, 函数和类型转换导致索引失效
```
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id INT PRIMARY KEY AUTO_INCREMENT,
    t1 VARCHAR(10) NOT NULL,
    t2 INT NOT NULL
    );

CREATE INDEX index_t1 ON tb1(t1);
EXPLAIN SELECT * FROM tb1 WHERE t1 = '1';
EXPLAIN SELECT * FROM tb1 WHERE t1 =  1;           # 类型转换导致索引失效
EXPLAIN SELECT * FROM tb1 WHERE UPPER(t1) = '1';   # 函数导致索引失效

CREATE INDEX index_t2 ON tb1(t2);
EXPLAIN SELECT * FROM tb1 WHERE t2 = 1;
EXPLAIN SELECT * FROM tb1 WHERE t2 + 1 = 1; # 计算导致索引失效
```

# 3. 范围查找导致右侧的索引失效
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id INT PRIMARY KEY AUTO_INCREMENT,
    t1 INT NOT NULL,
    t2 INT NOT NULL,
    t3 INT NOT NULL,
    t4 INT);

CREATE INDEX index_t1_t2_t3 ON tb1(t1, t2, t3);
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t2 = 1 AND t3 = 1; # 使用全部索引 (key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t2 > 1 AND t3 = 1; # 使用部分索引, 范围查找 t3 上的索引失效 (key_len = 8)
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t3 = 1 AND t2 > 1; # 系统会按照联合索引声明的方式使用, 所以还是失效

DROP   INDEX index_t1_t2_t3 ON tb1;                                       
CREATE INDEX index_t1_t2_t3 ON tb1(t1, t3, t2);               # 修改联合索引声明的顺序
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t2 = 1 AND t3 = 1; # 使用全部索引 (key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t2 > 1 AND t3 = 1; # 使用全部索引 (key_len = 12)
EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 AND t3 = 1 AND t2 > 1; # 使用全部索引 (key_len = 12)
                                                              # 建立联合索引时, 将范围查找的字段放到末尾
                                                              
# 3. 测试 !=  和 IS NULL 和 IS NOT NULL, 索引不一定失效
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id INT PRIMARY KEY AUTO_INCREMENT,
    t1 INT);
    
CREATE INDEX index_t1 ON tb1(t1);
EXPLAIN SELECT * FROM tb1 WHERE t1 != 2; 
EXPLAIN SELECT * FROM tb1 WHERE t1 IS NULL;
EXPLAIN SELECT * FROM tb1 WHERE t1 IS NOT NULL;

# 4. 测试 LIKE, 索引不一定失效
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id INT PRIMARY KEY AUTO_INCREMENT,
    t1 VARCHAR(20));
    
CREATE INDEX index_t1 ON tb1(t1);
EXPLAIN SELECT * FROM tb1 WHERE t1 LIKE 'abc%';
EXPLAIN SELECT * FROM tb1 WHERE t1 LIKE '%bc'; 
EXPLAIN SELECT * FROM tb1 WHERE t1 LIKE 'abc_'; 
EXPLAIN SELECT * FROM tb1 WHERE t1 LIKE '_bc%'; 

# 5. 测试 OR, 一边不包含索引时, 导致索引失效   
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (
    id INT PRIMARY KEY AUTO_INCREMENT,
    t1 INT,
    t2 INT);
    
CREATE INDEX index_t1 ON tb1(t1);

EXPLAIN SELECT * FROM tb1 WHERE t1 = 1 OR t2 = 1;

# 6. 测试多表查询
DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1 (t1 INT);
    
DROP TABLE IF EXISTS tb2;
CREATE TABLE tb2 (t1 INT);

DROP INDEX index_t1 ON tb1;
DROP INDEX index_t1 ON tb2;  
EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.t1 = tb2.t1; # 1. 查看左连接
CREATE INDEX index_t1 ON tb1(t1);                           # 2. 在驱动表上建立索引, 意义不大
EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.t1 = tb2.t1; # 3. 查看左连接
DROP INDEX index_t1 ON tb1;                                 # 4. 删除驱动表上的索引
CREATE INDEX index_t1 ON tb2(t1);                           # 5. 在被驱动表上建立索引, 有用
EXPLAIN SELECT * FROM tb1 LEFT JOIN tb2 ON tb1.t1 = tb2.t1; # 6. 查看左连接
DROP INDEX index_t1 ON tb2;                                 # 7. 删除被驱动表上的索引

SHOW INDEX FROM tb1;

DROP INDEX index_t1 ON tb1;
DROP INDEX index_t1 ON tb2;
EXPLAIN SELECT * FROM tb1 JOIN tb2 ON tb1.t1 = tb2.t1; # 1. 查看内连接
CREATE INDEX index_t1 ON tb1(t1);                      # 2. 表 t1 建立索引
EXPLAIN SELECT * FROM tb1 JOIN tb2 ON tb1.t1 = tb2.t1; # 3. 查看内连接, 有索引的表可以做被驱动表
CREATE INDEX index_t1 ON tb2(t1);                      # 4. 表 t2 建立索引
EXPLAIN SELECT * FROM tb1 JOIN tb2 ON tb1.t1 = tb2.t1; # 5. 查看内连接, 有索引的表可以做被驱动表
INSERT INTO tb1 VALUES(1);                             # 6. t1 插入数据
INSERT INTO tb1 VALUES(2);
INSERT INTO tb1 VALUES(3);
EXPLAIN SELECT * FROM tb1 JOIN tb2 ON tb1.t1 = tb2.t1; # 7. t1 和 t2 都有索引
                                                       #    t1 比 t2 大
                                                       #    小表驱动大表, 所以使用 t1 的索引




```

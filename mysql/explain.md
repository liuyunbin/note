
## 1. 造数据
```
DROP   TABLE IF EXISTS teacher1;
CREATE TABLE teacher1 (id INT PRIMARY KEY, name VARCHAR(20) unique, addr VARCHAR(20), extra varchar(20));
INSERT INTO  teacher1 VALUES(1, "中神通", "全真教", "111");
INSERT INTO  teacher1 VALUES(2, "东邪",   "桃花岛", "222");
INSERT INTO  teacher1 VALUES(3, "西毒",   "西域", "333");
INSERT INTO  teacher1 VALUES(4, "南帝",   "大理", "444");
INSERT INTO  teacher1 VALUES(5, "北丐",   "宋", "555");
INSERT INTO  teacher1 VALUES(6, "中顽童", "全真教", "666");
INSERT INTO  teacher1 VALUES(7, "北侠",   "蒙古", "777");
INSERT INTO  teacher1 VALUES(8, "西狂",   "大宋", "888");

CREATE INDEX index_addr ON teacher1(addr);

DROP   TABLE IF EXISTS teacher2;
CREATE TABLE teacher2 (id INT PRIMARY KEY, name VARCHAR(20) unique, addr VARCHAR(20), extra varchar(20));
INSERT INTO  teacher2 VALUES(7,  "北侠",     "蒙古", "777");
INSERT INTO  teacher2 VALUES(10, "金轮法王", "蒙古", "999");
INSERT INTO  teacher2 VALUES(11, "潇湘子",   "蒙古", "123");
INSERT INTO  teacher2 VALUES(12, "尼摩星",   "蒙古", "456");
INSERT INTO  teacher2 VALUES(13, "尹克西",   "蒙古", "789");

CREATE INDEX index_addr ON teacher2(addr);

DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20) unique, addr VARCHAR(20), teacher_id int);
INSERT INTO  student VALUES(1, "马钰",   "全真教", 1);
INSERT INTO  student VALUES(2, "丘处机", "全真教", 1);
INSERT INTO  student VALUES(3, "王处一", "全真教", 1);
INSERT INTO  student VALUES(4, "黄蓉",   "桃花岛", 2);
INSERT INTO  student VALUES(5, "欧阳克",   "西域", 3);
INSERT INTO  student VALUES(6, "朱子柳",   "大理", 4);
INSERT INTO  student VALUES(7, "路人甲",   "大宋", 111);

CREATE INDEX index_addr ON student(addr);
```

## 2. 输出的各个字段的值
### 2.1 table -- 表名, 临时表也会记录
```
EXPLAIN SELECT * FROM teacher1;                                  # 一张表 
EXPLAIN SELECT * FROM teacher1, teacher2;                        # 两张表
EXPLAIN SELECT * FROM teacher1 UNION     SELECT * FROM teacher2; # 两张表 + 临时表
EXPLAIN SELECT * FROM teacher1 UNION ALL SELECT * FROM teacher2; # 两张表
EXPLAIN SELECT * FROM teacher1 WHERE id = (SELECT teacher_id FROM student WHERE name = '马钰');
                                                                 # 两张表, 子查询
```

### 2.2 id -- 每个 SELECT 关键字都对应一个唯一的id, 临时表也会有
```
EXPLAIN SELECT * FROM teacher1;                                  # 一张表 
EXPLAIN SELECT * FROM teacher1, teacher2;                        # 两张表
EXPLAIN SELECT * FROM teacher1 UNION     SELECT * FROM teacher2; # 两张表 + 临时表
EXPLAIN SELECT * FROM teacher1 UNION ALL SELECT * FROM teacher2; # 两张表
EXPLAIN SELECT * FROM teacher1 WHERE id = (SELECT teacher_id FROM student WHERE name = '马钰');
                                                                 # 两张表, 子查询
```

### 2.3 select_type -- 查询的类型
```
# 1. SIMPLE --------- 不包含 UNION 或者子查询
EXPLAIN SELECT * FROM teacher1;
EXPLAIN SELECT * FROM teacher1, teacher2;

# 2. PRIMARY -------- UNION 和 UNION ALL 的左边, 子查询的大查询
EXPLAIN SELECT * FROM teacher1 UNION     SELECT * FROM teacher2;
EXPLAIN SELECT * FROM teacher1 UNION ALL SELECT * FROM teacher2;
EXPLAIN SELECT * FROM teacher1 WHERE id = (SELECT teacher_id FROM student WHERE name = '马钰');

# 3. UNION  --------- UNION 和 UNION ALL 的右边 (不相关)
EXPLAIN SELECT * FROM teacher1 UNION     SELECT * FROM teacher2;
EXPLAIN SELECT * FROM teacher1 UNION ALL SELECT * FROM teacher2;
   
# 4. UNION RESULT --- UNION 去重的临时表
EXPLAIN SELECT * FROM teacher1 UNION     SELECT * FROM teacher2;

# 5. SUBQUERY ------------ 不相关子查询中的小查询
EXPLAIN SELECT * FROM teacher1 WHERE id = (SELECT teacher_id FROM student WHERE name = '马钰');

# 6. DEPENDENT SUBQUERY ---- 相关子查询中的小查询
EXPLAIN SELECT *, (SELECT name FROM teacher1 WHERE teacher1.id = student.teacher_id)
FROM student;

# 7. DEPENDENT UNION ------- UNION 和 UNION ALL 的右边 (相关)
EXPLAIN
SELECT * FROM student WHERE teacher_id IN (
    SELECT id FROM teacher1 WHERE teacher1.id = student.teacher_id
    UNION ALL
    SELECT id FROM teacher2 WHERE teacher2.id = student.teacher_id
);

# 8. DERIVED ---------------- 派生表
EXPLAIN SELECT * FROM (SELECT * FROM teacher1 UNION ALL SELECT * FROM teacher2) t1;

# 9. MATERIALIZED ----------- 把子查询优化成连接查询
EXPLAIN SELECT * FROM teacher1 WHERE id IN (SELECT teacher_id FROM student);
   
# 10. UNCACHEABLE SUBQUERY --- 不常用

# 11. UNCACHEABLE UNION ------ 不常用
```

### 2.4 partitions --- 分区表中的命中情况

### 2.5 type -- 针对单表的访问方法
```
# 1. system --- 只有一条记录, 精确

# 2. const ---- 常数与主键或唯一键等值匹配
EXPLAIN SELECT * FROM teacher1 WHERE id = 1;
EXPLAIN SELECT * FROM teacher1 WHERE name = '中神通';

# 3. eq_ref --- 连接查询 或 子查询时，被驱动表 使用主键或唯一键 常量等值匹配
EXPLAIN SELECT *, (SELECT name FROM teacher1 WHERE id = student.teacher_id) FROM student;

# 4. ref ------ 常数与普通索引等值匹配
EXPLAIN SELECT * FROM teacher1 WHERE addr = '大元';

# 5. fulltext ----- 全文索引

# 6. ref_or_null -- 常数与普通索引等值匹配 或 NULL
EXPLAIN SELECT * FROM teacher1 WHERE addr = '大元' OR addr IS NULL;

# 7. index_merge -- 单表多字段查询, 查询之间使用 OR, 可能索引合并
EXPLAIN SELECT * FROM teacher1 WHERE name = '北侠' OR  addr = '蒙古';
EXPLAIN SELECT * FROM teacher1 WHERE name = '北侠' AND addr = '蒙古'; # const

# 8. unique_subquery --- 子查询 IN 转化成 EXISTS, 并且子查询使用 主键进行等值匹配 --- 没复现
EXPLAIN SELECT * FROM student WHERE id IN (SELECT id FROM teacher1 WHERE teacher1.id = student.teacher_id);

# 9. index_subquery ---- 与 unique_subquery 类似，只不过子查询中的表时使用的是普通的索引 --- 没复现

# 10. range --- 范围查找
EXPLAIN SELECT * FROM teacher1 WHERE id IN (1, 2, 3);
EXPLAIN SELECT * FROM teacher1 WHERE id > 1 AND id < 3;

# 11. index
* 复合索引
* 查找时索引不是第一个字段
* 不需要回表, 只用索引就能满足要求

DROP TABLE IF EXISTS tb1;
CREATE TABLE tb1(t1 INT, t2 INT,  t3 int, t4 int);
CREATE INDEX index_123 ON tb1(t1, t2, t3);

EXPLAIN SELECT t2 FROM tb1 WHERE t3 = 123;

# 12. ALL: 全表扫描
EXPLAIN SELECT * FROM teacher1;

# 13. 结果值从最好到最坏依次是
system > const > eq_ref > ref** > ref_or_null > index_merge > unique_subquery > index_subquery > range > index > ALL 

至少要达到 range 级别，要求是 ref 级别，最好是 consts级别
```

### 2.6 possible_keys --- 可能用到的索引

### 2.7 key ------------- 实际上使用的索引

### 2.8 key_len ------------- 实际使用到的索引长度

### 2.9 ref ----------------- 比较时, 对方的类型
```
EXPLAIN SELECT * FROM teacher1 WHERE addr = '大元';
EXPLAIN SELECT *, (SELECT name FROM teacher1 WHERE id = student.teacher_id) FROM student;
```

### 2.10 rows --------------- 预估的需要读取的记录条数

### 2.11 filtered ----------- 某个表经过搜索条件过滤后剩余记录条数的百分比

### 2.12 Extra -------------- 一些额外的信息
```
# 1. No tables used --- 没有 FROM 子句
EXPLAIN SELECT 1;

# 2. Impossible WHERE ---- WHERE 子句永远为 FALSE
EXPLAIN SELECT * FROM teacher1 WHERE 1 = 2;

# 3. Using where ----- WHERE 使用非索引列
EXPLAIN SELECT * FROM teacher1 WHERE extra = '111';

# 4. No matching min/max row -- 有 MIN 或者 MAX 聚合函数，但是没有符合 WHERE的搜索条件的记录
EXPLAIN SELECT max(id) FROM teacher1 WHERE id > 1000;

# 5. Select tables optimized away -- 有 MIN 或者 MAX 聚合函数, 有符合 WHERE的搜索条件的记录
EXPLAIN SELECT max(id) FROM teacher1;

# 6. Using index ----- 不需要回表
EXPLAIN SELECT id FROM teacher1 WHERE name = '北侠';

# 7. Using index condition -- 搜索条件中虽然出现了索引列，但却有不能使用索引的情况
EXPLAIN SELECT * FROM teacher1 WHERE name >= '北侠' AND name LIKE '%北侠%';

# 8. Using join buffer (Block Nested Loop) -- 连接查询执行过程中, 可能分配新内存提高效率

# 9. Not exists --- 左连接要求被驱动表的字段为 NULL, 但该字段不可能为 NULL
EXPLAIN SELECT * FROM teacher1 LEFT JOIN teacher2 ON teacher1.name = teacher2.name WHERE teacher2.id IS NULL;

# 10. Using intersect(...) 、 Using union(...) 和 Using sort_union(...) --- 多个索引同时使用
EXPLAIN SELECT id FROM teacher1 WHERE name = '北侠' OR addr = '大宋';

# 11. Zero limit -- 压根不读表
EXPLAIN SELECT * FROM teacher1 LIMIT 0;

# 12. Using filesort -- 排序无法使用索引, 使用内存或磁盘排序
EXPLAIN SELECT * FROM teacher1 ORDER BY addr;

# 13. Using temporary -- 使用临时表
EXPLAIN
SELECT * FROM teacher1
UNION
SELECT * FROM teacher2;
```

## 3. 输出格式
```
EXPLAIN             SELECT * FROM teacher1;
EXPLAIN FORMAT=JSON SELECT * FROM teacher1; # JSON
EXPLAIN FORMAT=tree SELECT * FROM teacher1; # TREE
```

## 4. 查看进一步的优化
```
EXPLAIN
SELECT * FROM teacher1 WHERE id in (SELECT teacher_id FROM student);
SHOW WARNINGS;

select `test`.`teacher1`.`id` AS `id`,
       `test`.`teacher1`.`name` AS `name`,
       `test`.`teacher1`.`addr` AS `addr`,
       `test`.`teacher1`.`extra` AS `extra` 
from `test`.`teacher1` semi 
join (`test`.`student`)
where (`test`.`teacher1`.`id` = `<subquery2>`.`teacher_id`)
```

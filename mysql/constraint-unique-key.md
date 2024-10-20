
## UNIQUE --- 唯一键
```
* 会创建唯一索引
* 可以存储 NULL
* 存储的值不能相同, 但 NULL 可以多个
* 默认的索引名和约束名是第一列的列名
* 可以存在多个唯一键
* 可以对多列定义一个唯一键
* 只能通过删除唯一索引的方式删除唯一键
* 删除唯一约束名报错
```

### 1. 创建
```
# 1. 列级约束(单列): 约束名和索引名默认和列名相同 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 2. 列级约束(多列): 约束名和索引名默认和列名相同 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20) UNIQUE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 3. 表级约束(单列), 不指定约束名和索引名: 约束名和索引名都是列名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 4. 表级约束(单列), 同时指定约束名和索引名: 约束名没意义, 约束名和索引名都变成索引名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name UNIQUE index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.  表级约束(单列), 只指定约束名: 约束名和索引名都变成约束名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name UNIQUE(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6. 表级约束(单列), 只指定索引名: 约束名和索引名都变成索引名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7. 表级约束(多列): 约束名和索引名默认和第一列的列名相同 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 2. 添加
```
# 1. 可以添加表级或列级唯一约束 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD UNIQUE (id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 2. 只能添加列级唯一约束
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student MODIFY id INT UNIQUE;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 3. 删除
```
# 1. 删除唯一索引: 使用 ALTER
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX id;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 2. 删除唯一索引: 使用 DROP
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
DROP   INDEX id ON student;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 3. 删除唯一约束名: 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINTS id;
```

### 4. 可以存储 NULL, NULL 可以重复, 其他不行
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20) UNIQUE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
INSERT INTO student VALUES(NULL, "BOB");
SELECT * FROM student;
INSERT INTO student VALUES(NULL, "TOM");
SELECT * FROM student;
INSERT INTO student VALUES(NULL, "BOB"); # 报错
```

## PRIMARY KEY --- 主键
```
* 会自动创建主键索引
* 不可以存储 NULL
* 存储的值不能相同
* 索引名和约束名是 PRIMARY
* 设置或修改索引名和约束名没意义
* 最多只存在一个主键
* 可以对多列定义一个主键
* 删除主键约束只能通过删除主键来实现, 删除主键索引或主键约束名报错
* 删除主键约束后, 主键索引也会删除, 但非空约束还在
* 和唯一键的区别: 非空 + 最多只有一个
* 主键不能是不可见的
```

### 1. 创建
#### 1.1 列级约束(单列): 约束名和索引名为 PRIMARY (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.2 列级约束(多列): 报错
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20) PRIMARY KEY);
```

#### 1.3 表级约束, 不指定约束名和索引名: 约束名和索引名都为 PRIMARY (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.4 表级约束, 指定约束名和索引名: 约束名和索引名都为 PRIMARY
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name PRIMARY KEY index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.5 表级约束, 只指定约束名: 约束名和索引名都为 PRIMARY
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name PRIMARY KEY(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.6 表级约束, 只指定索引名: 约束名和索引名都为 PRIMARY
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.7 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.8 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 1.9 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐) --- 主键不能不可见
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name) INVISIBLE);
```

### 2. 添加
#### 2.1 可以添加表级或列级主键约束 (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD PRIMARY KEY(id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.2 只能添加列级主键约束
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student MODIFY id INT PRIMARY KEY;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 3. 删除
#### 3.1 删除主键: 会删除对应的索引, 但非空约束还在
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP PRIMARY KEY;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 3.2 删除主键约束名: 报错
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINT PRIMARY;
```

#### 3.3 删除主键索引: 报错
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX PRIMARY;
```

### 4. 不可以存储 NULL, 不可以重复
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
INSERT INTO student VALUES(NULL, "BOB"); # 报错
INSERT INTO student VALUES(1,    "TOM");
SELECT * FROM student;
INSERT INTO student VALUES(1,    "BOB"); # 报错
```

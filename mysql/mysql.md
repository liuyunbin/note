
## 汇总
```
SET  @@GLOBAL.log_bin_trust_function_creators = 1; # 设置全局系统变量, 服务器重启失效
SET @@PERSIST.log_bin_trust_function_creators = 1; # 设置全局系统变量, 服务器重启依然保留
SET @@SESSION.log_bin_trust_function_creators = 1; # 设置会话系统变量, 服务器重启失效
SET @name = 'Tom'; # 设置会话用户变量
SET  name = 'Tom'; # 设置局部变量


```

# 常用数据类型
```
INT --------------- 整形 ------------------- 4     个字节
BIGINT UNSIGNED --- 大整形 ----------------- 8     个字节
DECIMAL(M,D) ------ 定点数 ----------------- M + 2 个字节
DATETIME ---------- 日期和时间 ------------- 8     个字节
TIMESTAMP --------- 时间戳 ----------------- 4     个字节
CHAR(M) ----------- 固定长度, M 为字符数 ---
VARCHAR(M) -------- 可变长度, M 为字符数 ---
```

# 约束
## 0. 准备库
```
SHOW   DATABASES;
CREATE DATABASE IF NOT EXISTS test;
SHOW   DATABASES;
```

## 1. NOT NULL
* 只能作用在单列上

### 1.1 创建
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
```

### 1.2 添加
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
DESC   student;
ALTER  TABLE student MODIFY id INT NOT NULL;
DESC   student;
```

### 1.3 删除
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
ALTER  TABLE student MODIFY id INT;
DESC   student;
```

## 2. UNIQUE --- 唯一键
* 会创建唯一索引
* 可以存储 NULL
* 存储的值不能相同, 但 NULL 可以多个
* 默认的索引名和约束名是第一列的列名
* 可以存在多个唯一键
* 可以对多列定义一个唯一键
* 只能通过删除唯一索引的方式删除唯一键
* 删除唯一约束名报错

### 2.1 创建
#### 2.1.1 列级约束(单列): 约束名和索引名默认和列名相同 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.1.2 列级约束(多列): 约束名和索引名默认和列名相同 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20) UNIQUE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.1.3 表级约束(单列), 不指定约束名和索引名: 约束名和索引名都是列名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.1.4 表级约束(单列), 同时指定约束名和索引名: 约束名没意义, 约束名和索引名都变成索引名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name UNIQUE index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.1.5  表级约束(单列), 只指定约束名: 约束名和索引名都变成约束名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name UNIQUE(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.1.6 表级约束(单列), 只指定索引名: 约束名和索引名都变成索引名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.1.7 表级约束(多列): 约束名和索引名默认和第一列的列名相同 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 2.2 添加
#### 2.2.1 可以添加表级或列级唯一约束 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD UNIQUE (id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.2.2 只能添加列级唯一约束
```
USE    test;
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

### 2.3 删除
#### 2.3.1 删除唯一索引: 使用 ALTER
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX id;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.3.2 删除唯一索引: 使用 DROP
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
DROP   INDEX id ON student;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 2.3.3 删除唯一约束名: 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINTS id;
```

### 2.4 可以存储 NULL, NULL 可以重复, 其他不行
```
USE    test;
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

## 3 PRIMARY KEY --- 主键
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

### 3.1 创建
#### 3.1.1 列级约束(单列): 约束名和索引名为 PRIMARY (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 3.1.2 列级约束(多列): 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20) PRIMARY KEY);
```

#### 3.1.3 表级约束, 不指定约束名和索引名: 约束名和索引名都为 PRIMARY (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 3.1.4 表级约束, 指定约束名和索引名: 约束名和索引名都为 PRIMARY
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name PRIMARY KEY index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 3.1.5 表级约束, 只指定约束名: 约束名和索引名都为 PRIMARY
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name PRIMARY KEY(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 3.1.6 表级约束, 只指定索引名: 约束名和索引名都为 PRIMARY
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 3.1.7 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 3.2 添加
#### 3.2.1 可以添加表级或列级主键约束 (推荐)
```
USE    test;
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

#### 3.2.2 只能添加列级主键约束
```
USE    test;
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

### 3.3 删除
#### 3.3.1 删除主键: 会删除对应的索引, 但非空约束还在
```
USE    test;
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

#### 3.3.2 删除主键约束名: 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINT PRIMARY;
```

#### 3.3.3 删除主键索引: 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX PRIMARY;
```

### 3.4 不可以存储 NULL, 不可以重复
```
USE    test;
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

## 4. FOREIGN KEY --- 外键
* 会自动创建索引
* 从表的外键必须是主表的主键或唯一键
* 先创建主表, 再创建从表
* 先删除从表或外键, 再删除主表
* 默认外键的外键名不是列名, 默认的索引名是列名
* 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
* 通过删除外键约束名或外键可以删除外键, 不能通过删除外键索引来删除外键
* 删除外键后, 外键索引还存在

### 4.1 创建
#### 4.1.1 不指定约束名和索引名: 约束名不是列名, 由系统生成, 索引名是列名 (建议)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 4.1.2 同时指定约束名和索引名: 索引名没意义, 约束名和索引名都变成指定的约束名
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY index_name(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 4.1.3 只指定约束名: 约束名和索引名都变成指定的约束名
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 4.1.4 只指定索引名: 约束名不是列名, 由系统生成, 索引名是指定名
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY index_name(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 4.1.5 不指定约束名和索引名(多个外键) (建议)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20) UNIQUE);
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  teacher_name VARCHAR(20),
  FOREIGN KEY(teacher_id) REFERENCES teacher(id),
  FOREIGN KEY(teacher_name) REFERENCES teacher(name)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 4.2 添加
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD FOREIGN KEY(teacher_id) REFERENCES teacher(id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 4.3 删除
#### 4.3.1 删除外键, 索引不会自动删除 (建议)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP FOREIGN KEY constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

#### 4.3.2 删除索引, 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX constraint_name;
```

#### 4.3.3 删除约束名, 和删除外键相同, 索引不会自动删除
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINT constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
```

### 4.4 约束等级
#### 4.4.1 CASCADE --- 父表更新时, 同步更新子表
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE CASCADE
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 2 WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 4.4.2 CASCADE --- 父表删除时, 同步删除子表对应的行
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON DELETE CASCADE
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 4.4.3 SET NULL --- 父表更新时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE SET NULL
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 2 WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 4.4.4 SET NULL --- 父表删除时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON DELETE SET NULL
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 4.4.5 NO ACTION (同 RESTRICT) --- 父表更新时, 如果子表对应字段已使用, 报错, 未使用时, 更新成功 (默认)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE NO ACTION
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO teacher VALUES(2, "丘处机");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 11 WHERE id = 1; # 报错
UPDATE teacher SET id = 22 WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 4.4.6 NO ACTION (同 RESTRICT) --- 父表删除时, 如果子表对应字段已使用, 报错, 未使用时, 删除成功 (默认)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON DELETE NO ACTION
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO teacher VALUES(2, "丘处机");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 1; # 报错
DELETE FROM teacher WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 4.4.7 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE CASCADE ON DELETE RESTRICT
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO teacher VALUES(2, "丘处机");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 11 WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 11; # 报错
DELETE FROM teacher WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

## 5. `AUTO_INCREMENT` --- 自动递增
* 只能作用于整形
* 最多只有一列
* 列必须是主键或唯一键

### 5.1 创建
#### 5.1.1 单列 (整形): 作用于主键
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
```

#### 5.1.2 单列 (整形): 作用于唯一键, 非空, 无主键时, 该列会变成主键
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idD INT);
DESC   student;
```

#### 5.1.3 单列 (整形): 作用于唯一键, 非空, 有其他主键时, 该列还是唯一键
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idD INT PRIMARY KEY );
DESC   student;
```

#### 5.1.4 单列 (非整形) -- 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) UNIQUE AUTO_INCREMENT);
```

#### 5.1.5 多列 (整形) -- 报错
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idD INT UNIQUE AUTO_INCREMENT);
```

#### 5.1.6 单列 -- 默认初始值为 1
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

#### 5.1.7 单列 -- 设置初始值为 10
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20)) AUTO_INCREMENT = 10;
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

### 5.2 添加
#### 5.2.1 初始值为 1
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
ALTER  TABLE student MODIFY id INT AUTO_INCREMENT;
DESC   student;
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

#### 5.2.2 设置初始值为 10
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student AUTO_INCREMENT = 10;
DESC   student;
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

### 5.3 删除
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
ALTER  TABLE student MODIFY id INT;
DESC   student;
```

## 6. CHECK --- 检查
* 只能通过删除 CHECK 约束名来删除 CHECK 约束
* 可以使 CHECK 不生效

### 6.1 创建
#### 6.1.1 列级约束: 约束名由系统生成 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT CHECK(id > 0), name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 6.1.2 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 6.1.3 表级约束(单列): 指定约束名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  id INT,
  name VARCHAR(20),
  CONSTRAINT constraint_name CHECK(id > 0)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 6.1.4 表级约束(多列): (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0 AND LENGTH(name) > 1));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 6.2 添加
#### 6.2.1 可以添加列级和表级约束 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ADD CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 6.2.2 只能添加列级约束
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 6.3 删除
#### 6.3.1 删除 CHECK 约束名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student DROP CHECK constraint_name;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 6.3.2 通过 ALTER ... MODIFY ... ------ 没用
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 6.4 使 CHECK 不生效
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student VALUES(-1, 'BOB'); # 报错
ALTER  TABLE student ALTER CHECK constraint_name NOT ENFORCED;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student VALUES(-1, 'BOB');
SELECT * FROM student;
```

## 7. DEFAULT --- 默认值
### 7.1 创建
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
```

### 7.2 添加
#### 7.2.1 方式一
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student ALTER name SET DEFAULT 'TOM';
DESC   student;
```

#### 7.2.2 方式二 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20) DEFAULT 'TOM';
DESC   student;
```

### 7.3 删除
#### 7.3.1 方式一
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
ALTER  TABLE student ALTER name DROP DEFAULT;
DESC   student;
```

#### 7.3.2 方式二 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20);
DESC   student;
```

## 8. INDEX --- 索引
* 类型
  * 普通索引 ----- 无任何限制
  * 唯一索引 ----- 和 UNIQUE 对应
  * 主键索引 ----- 和 PRIMARY KEY 对应
  * 全文索引 ----- 很少使用
  * 空间索引 ----- 很少使用
* 范围
  * 单列索引 -----
  * 多列索引 ----- 最左前缀原则 -- 最常用的放最左边
* 实现
  * 聚簇索引 -----
  * 非聚簇索引 ---
* 新特性
  * 降序索引 ----- 如果查找是降序的话, 可以提高效率 --- ASC DESC
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

### 8.1 创建
#### 8.1.1 单列: 不指定索引名称: 索引名称默认是列名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id));
SHOW   INDEX FROM student;
```

#### 8.1.2 单列: 指定索引名称
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
```

#### 8.1.3 多列: 不指定索引名称: 索引名称默认是第一个列名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX(id, name));
SHOW   INDEX FROM student;
```

#### 8.1.4 多列: 指定索引名称
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX index_name(id, name));
SHOW   INDEX FROM student;
```

#### 8.1.5 降序索引
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id));
SHOW   INDEX FROM student;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id DESC));
SHOW   INDEX FROM student;
```

#### 8.1.6 不可见索引
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id) VISIBLE);
SHOW   INDEX FROM student;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id) INVISIBLE);
SHOW   INDEX FROM student;
```

### 8.2 添加 或 修改
#### 8.2.1 使用 CREATE INDEX 添加 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
CREATE INDEX index_name ON student(id);
SHOW   INDEX FROM student;
```

#### 8.2.2 使用 ALTER 添加
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
ALTER  TABLE student ADD INDEX index_name(id);
SHOW   INDEX FROM student;
```

#### 8.2.3 设置索引是否可见
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name INVISIBLE;
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name VISIBLE;
SHOW   INDEX FROM student;
```

### 8.3 删除
#### 8.3.1 使用 DROP (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
DROP   INDEX index_name ON student;
SHOW   INDEX FROM student;
```

#### 8.3.2 使用 ALTER
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX index_name;
SHOW   INDEX FROM student;
```

### 8.4 重命名索引
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student REname INDEX index_name TO NEW_index_name;
SHOW   INDEX FROM student;
```

## 库
```
SHOW   DATABASES;                   # 查看所有的数据库
CREATE DATABASE IF NOT EXISTS test; # 创建数据库
SHOW   CREATE DATABASE test;        # 查看数据库的创建信息, 比如编码
USE    test;                        # 选择数据库
DROP   DATABASE test;               # 删除数据库
```

## 表
### 0. 准备库
```
SHOW   DATABASES;
CREATE DATABASE IF NOT EXISTS test;
SHOW   DATABASES;
```

### 1. 创建和删除表
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS student_test;
CREATE TABLE student (id INT);
CREATE TABLE student_test AS SELECT * FROM student; # 通过已存在的表新建
SHOW   TABLES;
SHOW   CREATE TABLE student;
SHOW   CREATE TABLE student_test;
DESC   student;
DESC   student_test;
```

### 2. 增加列
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);
DESC   student;
ALTER  TABLE student ADD before_id VARCHAR(20) FIRST;
ALTER  TABLE student ADD  after_id VARCHAR(20) AFTER id;
ALTER  TABLE student ADD      name VARCHAR(20);
DESC   student;
```

### 3. 删除列
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student DROP name;
DESC   student;
```

### 4. 修改列属性
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student MODIFY id BIGINT;
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20) FIRST;
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20) AFTER id;
DESC   student;
```

### 5. 重命名列名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student RENAME COLUMN name TO new_name;
DESC   student;
ALTER  TABLE student CHANGE id new_id BIGINT;
DESC   student;
```

### 6. 设置列不可见
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student ALTER name SET INVISIBLE;
DESC   student;
ALTER  TABLE student ALTER name SET VISIBLE;
DESC   student;
```

### 7. 重命名表
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS student_test;
CREATE TABLE student (id INT, name VARCHAR(20));
SHOW   TABLES;
ALTER  TABLE student RENAME TO student_test;
SHOW   TABLES;
RENAME TABLE student_test TO student;
SHOW   TABLES;
```

### 8. 删除表内数据(清空表)
```
USE    test;
DROP   TABLE IF EXISTS student;
SET    AUTOCOMMIT = FALSE;      # 取消自动提交
CREATE TABLE student (id INT, name VARCHAR(20));
INSERT INTO  student VALUES(1, "马钰");
INSERT INTO  student VALUES(2, "丘处机");
INSERT INTO  student VALUES(3, "王处一");
COMMIT;                  # 提交
SELECT * FROM student;
DELETE   FROM student;
SELECT * FROM student;
ROLLBACK;                # 回滚
SELECT * FROM  student;
TRUNCATE TABLE student;  # 清空表 --- 不能回滚 --- 会自动提交
ROLLBACK;                # 回滚
SELECT * FROM  student;
```

### 9. 插入数据(一个一个插入)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
INSERT INTO  student VALUES(1, "马钰");
INSERT INTO  student VALUES(2, "丘处机");
INSERT INTO  student VALUES(3, "王处一");
SELECT * FROM student;
```

### 10. 插入数据(多个插入)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
INSERT INTO  student VALUES(1, "马钰"), (2, "丘处机"), (3, "王处一");
SELECT * FROM student;
```

### 11. 插入数据(使用现有表)
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS student_test;
CREATE TABLE student (id INT, name VARCHAR(20));
CREATE TABLE student_test (id INT, name VARCHAR(20));
INSERT INTO  student VALUES(1, "马钰"), (2, "丘处机"), (3, "王处一");
SELECT * FROM student;
SELECT * FROM student_test;
INSERT   INTO student_test SELECT * FROM student;
SELECT * FROM student;
SELECT * FROM student_test;
```

### 12. 插入数据(忽略重复的数据, 列唯一)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20));
INSERT INTO  student VALUES(1, "马钰");
SELECT * FROM student;
INSERT INTO  student VALUES(2, "马钰");
SELECT * FROM student;
INSERT INTO  student VALUES(1, "丘处机");        # 报错
INSERT IGNORE INTO  student VALUES(1, "丘处机"); # 忽略重复的数据
SELECT * FROM student;
```

### 13. 插入数据(遇到重复的数据, 先删除再添加)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20));
INSERT INTO  student VALUES(1, "丘处机");
SELECT * FROM student;
REPLACE INTO  student VALUES(1, "马钰");
SELECT * FROM student;
REPLACE INTO  student VALUES(2, "丘处机");
SELECT * FROM student;
```

### 14. 更新数据
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
INSERT INTO  student VALUES(1, "马玉");
INSERT INTO  student VALUES(2, "丘处机");
INSERT INTO  student VALUES(3, "王处一");
SELECT * FROM student;
UPDATE student SET name = "马钰" WHERE id = 1;
SELECT * FROM student;
```

### 15. SELECT(书写和执行顺序)
```
书写: SELECT -> DISTINCT -> FROM -> WHERE -> GROUP BY -> HAVING -> ORDER BY -> LIMIT
执行: FROM -> WHERE -> GROUP BY(此后可以使用聚合) -> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT
```

### 16. SELECT()
```
USE    test;
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher (id INT PRIMARY KEY, name VARCHAR(20), addr VARCHAR(20));
INSERT INTO  teacher VALUES(1, "中神通", "全真教");
INSERT INTO  teacher VALUES(2, "东邪",   "桃花岛");
INSERT INTO  teacher VALUES(3, "西毒",   "西域");
INSERT INTO  teacher VALUES(4, "南帝",   "大理");
INSERT INTO  teacher VALUES(5, "北丐",   "宋");
INSERT INTO  teacher VALUES(6, "中顽童", "全真教");
INSERT INTO  teacher VALUES(7, "北侠",   "大元");
INSERT INTO  teacher VALUES(8, "西狂",   NULL);

CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20), addr VARCHAR(20), teacher_id int,
  FOREIGN KEY (teacher_id) REFERENCES teacher(id)
);
INSERT INTO  student VALUES(1, "马钰",   "全真教", 1);
INSERT INTO  student VALUES(2, "丘处机", "全真教", 1);
INSERT INTO  student VALUES(3, "王处一", "全真教", 1);
INSERT INTO  student VALUES(4, "黄蓉",   "桃花岛", 2);
INSERT INTO  student VALUES(5, "欧阳克",   "西域", 3);
INSERT INTO  student VALUES(6, "朱子柳",   "大理", 4);

DROP   TABLE IF EXISTS teacher2;
CREATE TABLE teacher2 (id INT PRIMARY KEY, name VARCHAR(20), addr VARCHAR(20));
INSERT INTO  teacher2 VALUES(7, "北侠",      "大元");
INSERT INTO  teacher2 VALUES(10, "金轮法王", "蒙古");
INSERT INTO  teacher2 VALUES(11, "潇湘子",   "蒙古");
INSERT INTO  teacher2 VALUES(12, "尼摩星",   "蒙古");
INSERT INTO  teacher2 VALUES(13, "尹克西",   "蒙古");

SELECT * FROM teacher;
SELECT * FROM teacher WHERE addr = NULL;
SELECT * FROM teacher WHERE addr IS NULL;
SELECT * FROM teacher WHERE addr IS NOT NULL;
SELECT * FROM teacher WHERE id BETWEEN 3 AND 5; # []
SELECT * FROM teacher WHERE id IN (3, 5, 8);
SELECT * FROM teacher WHERE id NOT IN (3, 5, 8);
SELECT * FROM teacher WHERE addr   LIKE '大_';    # _ 任意一个字符
SELECT * FROM teacher WHERE addr   LIKE '__';
SELECT * FROM teacher WHERE name   LIKE '中%';    # % 任意多个字符
SELECT * FROM teacher WHERE addr  RLIKE '^.{2}$'; # 正则
SELECT * FROM teacher WHERE addr REGEXP '^.{3}$'; # 正则
SELECT DISTINCT addr FROM teacher; # 去重
SELECT * FROM teacher ORDER BY name;
SELECT * FROM teacher ORDER BY name DESC;
SELECT addr, count(*) c FROM teacher                        GROUP BY addr;
SELECT addr, count(*) c FROM teacher WHERE addr IS NOT NULL GROUP BY addr;
SELECT addr, count(*) c FROM teacher                        GROUP BY addr having c = 1;
SELECT addr, count(*) c FROM teacher                        GROUP BY addr limit 1; # LIMIT 偏移量, 行数

SELECT * FROM teacher UNION     SELECT * FROM teacher2; # 合并,   去重
SELECT * FROM teacher UNION ALL SELECT * FROM teacher2; # 合并, 不去重, 效率高

SELECT * FROM teacher t       JOIN student s ON s.teacher_id = t.id; # 内连接
SELECT * FROM teacher t LEFT  JOIN student s ON s.teacher_id = t.id; # 左连接
SELECT * FROM teacher t RIGHT JOIN student s ON s.teacher_id = t.id; # 右连接

# 查看有徒弟的师傅
SELECT DISTINCT t.id, t.name from teacher t WHERE EXISTS (SELECT * FROM student s WHERE t.id = s.teacher_id);
SELECT DISTINCT t.id, t.name from teacher t, student s WHERE t.id = s.teacher_id;
```

## 视图
```
* 相当于是一张虚拟表
* 不存储数据
* 一般只用于查询
* 简化操作, 便于操作
* 提高数据安全, 只展示部分列
* 底层变化时, 必须更新视图

USE    test;
DROP   TABLE IF EXISTS student_base;
DROP   TABLE IF EXISTS student_detail;
CREATE TABLE student_base   (id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student_detail (id INT PRIMARY KEY, addr VARCHAR(20));

# 创建或更新视图
CREATE OR REPLACE VIEW view_name AS
  SELECT b.id, b.name, d.addr
  FROM student_base b, student_detail d
  WHERE b.id = d.id;

# 查看视图
SHOW TABLE STATUS LIKE 'view_name';
SHOW CREATE VIEW view_name;

# 更新视图
ALTER VIEW view_name AS
  SELECT b.id, b.name, d.addr
  FROM student_base b, student_detail d
  WHERE b.id = d.id;

# 删除视图
DROP VIEW  view_name;
```

## 1. 存储过程
### 1.1 优缺点
```
* 提前编译, 效率高
* 简化操作
* 提高复用
* 减少操作失误
* 减少网上传输的数据
* 提高了数据安全
* 没返回值
* 不好调试
* 分表时, 不好维护
* 跨数据库不好移植
* 不好做版本管理
```

### 1.2 说明
```
DELIMITER $
CREATE PROCEDURE procedure_name(...) ------- IN, OUT, INOUT
[characteristics ...]
BEGIN
    ...
END $
DELIMITER ;

characteristics:
* LANGUAGE SQL ----------- 语言 SQL
* DETERMINISTIC ---------- 相同的输入会得到相同的输出
* NOT DETERMINISTIC ------ 相同的输入不一定会得到相同的输出 ---- 默认值
* NO SQL ----------------- 不包含任何 SQL 语句
* CONTAINS SQL ----------- 不包含任何 SQL 语句, 但是并不包含读写数据的SQL语句 ---- 默认
* READS SQL DATA --------- 包含读数据的 SQL 语句
* MODIFIES SQL DATA ------ 包含写数据的 SQL 语句
* SQL SECURITY DEFINER --- 只允许创建者或定义者使用 --- 默认
* SQL SECURITY INVOKER --- 允许所有人使用
* COMMENT string --------- 注释信息

CALL procedure_name(...)
```

### 1.3 示例
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    SELECT 123;
END $
DELIMITER ;

CALL  procedure_name();
SHOW  CREATE PROCEDURE procedure_name;
```

## 2. 函数
### 2.1 和存储过程的区别
```
* 有返回值
* 参数只能是 IN
* 需要设置: SET GLOBAL log_bin_trust_function_creators = 1
```

### 2.2 说明
```
DELIMITER $
CREATE FUNCTION function_name(...)
[characteristics ...]
RETURNS ...
BEGIN
   ...
END $
DELIMITER ;

SELECT procedure_name(...)
```

### 2.3 实例
```
SET GLOBAL log_bin_trust_function_creators = 1; # 使用 root 用户或有权限的用户设置

DROP FUNCTION  IF EXISTS function_name;
DELIMITER $
CREATE FUNCTION function_name()
RETURNS INT
BEGIN
   RETURN 123;
END $
DELIMITER ;

SELECT function_name();
SHOW CREATE FUNCTION function_name;
```

## 3. 变量
### 3.1 全局系统变量
```
SHOW   GLOBAL  VARIABLES LIKE 'character%';    # 查询全局系统变量
SELECT @@GLOBAL.character_set_client;          # 查询全局系统变量
SET    @@global.character_set_client = 变量值;       # 设置全局系统变量 -- 不能跨服务器重启
SET            GLOBAL character_set_client = 变量值; # 设置全局系统变量 -- 不能跨服务器重启
SET    PERSIST GLOBAL character_set_client = 变量值; # 设置全局系统变量 -----能跨服务器重启
```

### 3.2 会话系统变量
```
* 初始值可以从全局系统变量拷贝

SHOW   SESSION VARIABLES LIKE 'character%';     # 查询会话系统变量
SELECT @@SESSION.character_set_client;          # 查询会话系统变量
SET    @@session.character_set_client = 变量值; # 设置会话系统变量
SET    SESSION   character_set_client = 变量值; # 设置会话系统变量
```

### 3.3 会话用户变量
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);
SET    @num = 100;                      # 设置会话用户变量
SELECT @num;                            # 查看会话用户变量
SELECT count(*) INTO @num FROM student; # 设置会话用户变量
SELECT @num;                            # 查看会话用户变量
```

### 3.4 局部变量
```
* 只在BEGIN 和 END 之间使用, 定义只能放在开头
* 需要指定类型
* DECLARE 定义
```

### 3.5 测试
#### 3.5.1: SET SELECT
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    DECLARE num  int;
    SET     num  = 10;
    SELECT  num;
END $
DELIMITER ;

CALL procedure_name()
```

#### 3.5.2: SET DEFAULT SELECT
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    DECLARE num  int DEFAULT 100;
    SELECT  num;
    SET     num  = 10;
    SELECT  num;
END $
DELIMITER ;

CALL procedure_name()
```

#### 3.5.3: SELECT INTO
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);

DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    DECLARE num int;
    SELECT count(*) INTO num FROM student;
    SELECT  num;
END $
DELIMITER ;

CALL procedure_name()
```

#### 3.5.4 : 混用局部变量和用户会话变量
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);

DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name(OUT num int)
BEGIN
    SELECT count(*) INTO num FROM student;
END $
DELIMITER ;

SET    @num = 10;
SELECT @num;
CALL   procedure_name(@num);
SELECT @num;
```

## 4. 流程控制
### 4.1 语句: IF
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE num INT;
  SET num = 3;
  IF num = 1 THEN
    select "num 1", num;
  ELSEIF num = 2 THEN
    select "num 2", num;
  ELSE
    select "num 3", num;
  END IF;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.2 语句: CASE (情况一: 类似 switch)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE num INT;
  SET num = 3;
  CASE num
	WHEN 1 THEN
    select "num 1", num;
  WHEN 2 THEN
    select "num 2", num;
	ELSE
    select "num 3", num;
  END CASE;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.2 语句: CASE (情况二)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE num INT;
  SET num = 3;
  CASE
	WHEN num = 1 THEN
    select "num 1", num;
  WHEN num = 2 THEN
    select "num 2", num;
	ELSE
    select "num 3", num;
  END CASE;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.3 语句: LOOP
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE id INT DEFAULT 0;
  add_loop: LOOP
    SET id = id +1;
    IF id > 3 THEN
      LEAVE add_loop;
    ELSE
      select id;
    END IF;
  END LOOP add_loop;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.4 语句: WHILE
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE i INT DEFAULT 0;

	add_while: WHILE i < 10 DO
		SET i = i + 1;
	END WHILE add_while;

	SELECT i;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.5 语句: REPEAT (类似 do ... while)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE i INT DEFAULT 0;

  add_repeat: REPEAT
		SET i = i + 1;
	UNTIL i >= 10
	END REPEAT add_repeat;

	SELECT i;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.6 语句: ITERATE(与 continue 类似)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE id INT DEFAULT 0;
  add_loop: LOOP
    SET id = id +1;
    IF id < 10 THEN
      ITERATE add_loop;
    ELSEIF id > 13 THEN
      LEAVE add_loop;
    END IF;

    select id;
  END LOOP add_loop;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.7 语句: LEAVE(与 break 类似)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE id INT DEFAULT 0;
  add_loop: LOOP
    SET id = id +1;
    IF id > 3 THEN
      LEAVE add_loop;
    ELSE
      select id;
    END IF;
  END LOOP add_loop;
END $
DELIMITER ;

CALL procedure_name();
```

## 5. 异常处理
### 5.1 定义条件: 方便后续使用
```
DECLARE 错误名称 CONDITION FOR 错误码（或错误条件）

错误码: 整形
错误条件: 长度为 5 的字符串

DECLARE Field_Not_Be_NULL CONDITION FOR 1048;
DECLARE Field_Not_Be_NULL CONDITION FOR SQLSTATE '23000';
```

### 5.2 定义程序: 发生错误执行的代码
```
DECLARE 处理方式 HANDLER FOR 错误类型 处理语句
SIGNAL  错误类型 .....     ------ 抛出错误

处理方式:
* CONTINUE：表示遇到错误不处理，继续执行。
* EXIT：表示遇到错误马上退出
* UNDO：表示遇到错误后撤回之前的操作 -- MySQL中暂时不支持这样的操作

错误类型:
* SQLSTATE 字符串错误码: 上述定义的错误条件
* MySQL_error_code: 上述定义的错误码
* 错误名称: 见上述定义。
* SQLWARNING:   匹配所有以01开头的SQLSTATE错误代码
* NOT FOUND:    匹配所有以02开头的SQLSTATE错误代码
* SQLEXCEPTION: 匹配所有没有被SQLWARNING或NOT FOUND捕获的SQLSTATE错误代码

处理语句: 简单语句 或 BEGIN ... END 编写的复合语句
```

## 1. 游标: 用于定位某条记录
### 1.1 说明
```
* 游标使用过程会对数据加锁
* 耗内存资源

DECLARE cursor_name CURSOR FOR select ....; # 1. 定义游标
OPEN    cursor_name;                        # 2. 打开游标
FETCH   cursor_name INTO var_name ...;      # 3. 使用游标
CLOSE   cursor_name;                        # 4. 关闭游标, 需要及时关闭, 否则消耗系统资源
```

### 1.2 实例
#### 1.2.1 数据准备
```
USE    test;
DROP   TABLE IF EXISTS employees;
CREATE TABLE employees(id INT, name VARCHAR(20), salary INT);
INSERT INTO  employees values(1, "张三",  7000);
INSERT INTO  employees values(2, "李四",  8000);
INSERT INTO  employees values(3, "王五",  9000);
INSERT INTO  employees values(4, "赵六", 10000);
INSERT INTO  employees values(4, "田七", 11000);
```

#### 1.2.2 定义存储过程
```
USE  test;
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name(IN total_salary INT, OUT ret int, INOUT sum_salary INT, INOUT count_salary INT)
BEGIN
  DECLARE  curr_salary INT DEFAULT 0;
  DECLARE v_not_found  INT DEFAULT FALSE;
  DECLARE cursor_name CURSOR FOR SELECT salary FROM employees ORDER BY salary DESC;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_not_found = TRUE;  # 游标无数据时 设置变量

  OPEN    cursor_name;

  add_loop: LOOP
      FETCH cursor_name INTO curr_salary;
      IF v_not_found THEN
        SET ret = -1;
        LEAVE add_loop;
      END IF;
      SET sum_salary   = sum_salary + curr_salary;
      SET count_salary = count_salary + 1;
      IF sum_salary > total_salary THEN
        SET ret = 0;
        LEAVE add_loop;
      END IF;
  END LOOP add_loop;

  CLOSE   cursor_name;
END $
DELIMITER ;
```

#### 1.2.3 测试
```
SET @ret          = 0;
SET @sum_salary   = 0;
SET @count_salary = 0;
CALL   procedure_name(20000, @ret, @sum_salary, @count_salary);   # 正常获取
SELECT @ret, @sum_salary, @count_salary;
CALL   procedure_name(200000, @ret, @sum_salary, @count_salary);  # 测试报错
SELECT @ret, @sum_salary, @count_salary;
```

## 2. 触发器
### 2.1 说明
```
* 可用于自动维护一些信息, 比如 日志
* 可用于检查入参的错误
* 底层表变化时, 需要修改触发器
* 由于操作是自动的, 不容易发现错误
* OLD 获取旧数据, NEW 获取新数据

CREATE TRIGGER trigger_name
[BEFORE|AFTER]  [INSERT|UPDATE|DELETE]
ON table_name FOR EACH ROW ...

DROP TRIGGER   table_name.trigger_name;               # 删除触发器
```

### 2.2 测试
#### 2.2.1 日志记录
```
USE test;
DROP TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DROP TABLE IF EXISTS student_log;
CREATE TABLE student_log (log_time DATETIME, log_name VARCHAR(20));

DROP   TRIGGER   IF EXISTS trigger_name;
CREATE TRIGGER trigger_name AFTER INSERT ON student FOR EACH ROW
INSERT INTO student_log values(now(), "insert");
SELECT * FROM student;
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student;
SELECT * FROM student_log;
```

#### 2.2.2 检查入参 (只是测试, 用唯一键更合适)
```
USE test;
DROP TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DROP TABLE IF EXISTS student_log;
CREATE TABLE student_log (log_time DATETIME, log_name VARCHAR(20));

DROP   TRIGGER   IF EXISTS trigger_name;
DELIMITER $
CREATE TRIGGER trigger_name
BEFORE INSERT ON student FOR EACH ROW
BEGIN
    DECLARE num int DEFAULT(0);

    SELECT count(*) into num FROM student WHERE name = NEW.name;

    IF num != 0 THEN
        SIGNAL SQLSTATE 'HY000' SET MESSAGE_TEXT = '数据已存在, 不允许插入';
    END IF;

    INSERT INTO student_log values(now(), "insert");
END $
DELIMITER ;

SELECT * FROM student;
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student;
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student;
SELECT * FROM student_log;
```

round -- 不一定是直观 的四舍五入

current_timestamp()
current_date()
now()

## 练习子查询
```
# 1. 为什么使用数据库
* 数据持久化
* 效率

DDL: create drop alter rename truncate

DDL(数据定义语言): CREATE DROP   ALTER
DML(数据操作语言): INSERT UPDATE SELECT DELETE
DCL(数据控制语言): GRANT  REVOKE COMMIT ROLLBACK SAVEPOINT

source ...

round -- 不一定是直观 的四舍五入

DB: 数据库 Database
DBMS: 数据库管理系统 Database Management System
SQL: 结构化查询语言 Structured Query Language

RDBMS: 关系型数据库
* 将复杂的关系转化为二元的关系, 表格
* 表之间通过外键来关联

E-R(entity-relationship 实体-联系)模型中有三个主要概念是 实体集 属性集 联系集
一个实体集(class)   == 一个表(table)
一个实体(instance)  == 一行(row), 一条记录(record)
一个属性(attribute) == 一列(column), 一个字段(field)

表之间的关系
一对一: 用的不多, 可以使用一张表, 但会冗余
一对多
多对多
自引用

单引号: 字符串 日期
双引号: 别名
反引用: 与关键字冲突时, 使用

库名 表名 表别名 字段名 字段别名 小写, 其他建议大写

## 其他
mysql -D <库名> -h <域名> -u <用户名> -p<密码>  # 登录
myqsl -D testdb < 1.sql                         # 从文件导入
mysqldump database_name table_name > 1.sql      # 导出到文件
select .. into outfile .. fields terminated by ',' optionally enclosed by '"' lines terminated by '\n' from ..
                                                # 保存数据到文件

mysql_install_db --user=mysql --ldata=/var/lib/mysql # 添加用户 mysql 使mysqld 可以使用 systemctl 启动

set global max_allowed_packet=64*1024*1024 # 设置插入的上限

current_timestamp()
current_date()
now()


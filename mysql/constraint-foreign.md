
## 7. FOREIGN KEY --- 外键
* 会自动创建索引
* 从表的外键必须是主表的主键或唯一键
* 先创建主表, 再创建从表
* 先删除从表或外键, 再删除主表
* 默认外键的外键名不是列名, 默认的索引名是列名
* 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
* 通过删除外键约束名或外键可以删除外键, 不能通过删除外键索引来删除外键
* 删除外键后, 外键索引还存在
* 外键可以有多个

### 7.1 创建
#### 7.1.1 不指定约束名和索引名: 约束名不是列名, 由系统生成, 索引名是列名 (建议)
```
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

#### 7.1.2 同时指定约束名和索引名: 索引名没意义, 约束名和索引名都变成指定的约束名
```
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

#### 7.1.3 只指定约束名: 约束名和索引名都变成指定的约束名
```
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

#### 7.1.4 只指定索引名: 约束名不是列名, 由系统生成, 索引名是指定名
```
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

#### 7.1.5 不指定约束名和索引名(多个外键) (建议)
```
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

### 7.2 添加
```
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

### 7.3 删除
#### 7.3.1 删除外键, 索引不会自动删除 (建议)
```
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

#### 7.3.2 删除索引, 报错
```
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

#### 7.3.3 删除约束名, 和删除外键相同, 索引不会自动删除
```
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

### 7.4 约束等级
#### 7.4.1 CASCADE --- 父表更新时, 同步更新子表
```
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

#### 7.4.2 CASCADE --- 父表删除时, 同步删除子表对应的行
```
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

#### 7.4.3 SET NULL --- 父表更新时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
```
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

#### 7.4.4 SET NULL --- 父表删除时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
```
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

#### 7.4.5 NO ACTION (同 RESTRICT) --- 父表更新时, 如果子表对应字段已使用, 报错, 未使用时, 更新成功 (默认)
```
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
DELETE FROM student WHERE teacher_id = 1;
UPDATE teacher SET id = 11 WHERE id = 1; # 成功
UPDATE teacher SET id = 22 WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 7.4.6 NO ACTION (同 RESTRICT) --- 父表删除时, 如果子表对应字段已使用, 报错, 未使用时, 删除成功 (默认)
```
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
DELETE FROM student WHERE teacher_id = 1;
DELETE FROM teacher WHERE id = 1; # 成功
DELETE FROM teacher WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

#### 7.4.7 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
```
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
DELETE FROM student WHERE teacher_id = 11;
DELETE FROM teacher WHERE id = 11; # 成功
DELETE FROM teacher WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

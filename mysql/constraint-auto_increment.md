
## `auto_increment` -- 自动递增
```
* 只能作用于整形
* 最多只有一列
* 列必须是主键或唯一键
* 该列将变成非空
```

### 1. 创建
#### 1.1 单列 (整形): 作用于主键
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.2 单列 (整形): 作用于唯一键, 非空, 无主键时, 该列会变成主键
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.3 单列 (整形): 作用于唯一键, 有其他主键时, 该列还是唯一键
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT PRIMARY KEY);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.4 单列 (非整形) -- 报错
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) UNIQUE AUTO_INCREMENT);
```

#### 1.5 多列 (整形) -- 报错
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT UNIQUE AUTO_INCREMENT);
```

#### 1.6 单列 (整形, 非主键和唯一键) -- 报错
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT AUTO_INCREMENT, idd INT UNIQUE);
```

#### 1.7 单列 -- 默认初始值为 1
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

#### 1.8 单列 -- 设置初始值为 10
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20))AUTO_INCREMENT = 10;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

### 2. 添加
#### 2.1 初始值为 1
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT AUTO_INCREMENT;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

#### 2.2 设置初始值为 10
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student AUTO_INCREMENT = 10;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

### 3. 删除
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

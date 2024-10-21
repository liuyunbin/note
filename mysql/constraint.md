
## NOT NULL
```
* 只能作用在单列上
```

### 1. 创建
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
```

### 2. 添加
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
DESC   student;
ALTER  TABLE student MODIFY id INT NOT NULL;
DESC   student;
```

### 3. 删除
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
ALTER  TABLE student MODIFY id INT;
DESC   student;
```

## DEFAULT --- 默认值
### 1. 创建
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
```

###  2. 添加
```
# 1. 方式一
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student ALTER name SET DEFAULT 'TOM';
DESC   student;

#  2. 方式二 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20) DEFAULT 'TOM';
DESC   student;
```

### 3. 删除
```
# 1. 方式一
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
ALTER  TABLE student ALTER name DROP DEFAULT;
DESC   student;

# 2. 方式二 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20);
DESC   student;
```

## `AUTO_INCREMENT` --- 自动递增
```
* 只能作用于整形
* 最多只有一列
* 列必须是主键或唯一键
```

### 1. 创建
```
# 1. 单列 (整形): 作用于主键
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;

# 2. 单列 (整形): 作用于唯一键, 非空, 无主键时, 该列会变成主键
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT);
DESC   student;

# 3. 单列 (整形): 作用于唯一键, 非空, 有其他主键时, 该列还是唯一键
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT PRIMARY KEY);
DESC   student;

# 4. 单列 (非整形) -- 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) UNIQUE AUTO_INCREMENT);

# 5. 多列 (整形) -- 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idD INT UNIQUE AUTO_INCREMENT);

# 6. 单列 -- 默认初始值为 1
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;

# 7. 单列 -- 设置初始值为 10
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20))AUTO_INCREMENT = 10;
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

### 2. 添加
```
# 1. 初始值为 1
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
ALTER  TABLE student MODIFY id INT AUTO_INCREMENT;
DESC   student;
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;

# 2. 设置初始值为 10
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student AUTO_INCREMENT = 10;
DESC   student;
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;
```

### 3. 删除
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
ALTER  TABLE student MODIFY id INT;
DESC   student;
```

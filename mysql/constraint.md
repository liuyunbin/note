
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

## CHECK --- 检查
```
* 只能通过删除 CHECK 约束名来删除 CHECK 约束
* 可以使 CHECK 不生效
```

### 1. 创建
```
# 1. 列级约束: 约束名由系统生成 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT CHECK(id > 0), name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 2. 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 3. 表级约束(单列): 指定约束名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  id INT,
  name VARCHAR(20),
  CONSTRAINT constraint_name CHECK(id > 0)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4. 表级约束(多列): (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0 AND LENGTH(name) > 1));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 2. 添加
```
# 1. 可以添加列级和表级约束 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ADD CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 2. 只能添加列级约束
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 3. 删除
```
# 1. 删除 CHECK 约束名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student DROP CHECK constraint_name;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 2. 通过 ALTER ... MODIFY ... ------ 没用
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 4. 使 CHECK 不生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student VALUES(-1, 'BOB'); # 报错
ALTER  TABLE student ALTER CHECK constraint_name NOT ENFORCED;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student VALUES(-1, 'BOB'); # 成功
SELECT * FROM student;
```

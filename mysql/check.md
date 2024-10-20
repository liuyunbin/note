
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


## CHECK --- 检查
```
* 只能通过删除 CHECK 约束名来删除 CHECK 约束
* 可以使 CHECK 不生效
```

### 1. 创建
#### 1.1 列级约束: 约束名由系统生成 (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT CHECK(id > 0), name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.2 列级约束: 约束名由系统生成 (推荐) -- 约束不生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT CHECK(id > 0) NOT ENFORCED, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.3 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.4 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐) -- 约束不生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0) NOT ENFORCED);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.5 表级约束(单列): 指定约束名
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  id INT,
  name VARCHAR(20),
  CONSTRAINT constraint_name CHECK(id > 0)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.6 表级约束(单列): 指定约束名 -- 约束不生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  id INT,
  name VARCHAR(20),
  CONSTRAINT constraint_name CHECK(id > 0) NOT ENFORCED
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.7 表级约束(多列): (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0 AND LENGTH(name) > 1));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 1.8 表级约束(多列): (推荐) -- 约束不生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0 AND LENGTH(name) > 1) NOT ENFORCED);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 2. 添加 或 修改
#### 2.1 可以添加列级和表级约束 (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ADD CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 2.2 只能添加列级约束
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 2.3 生效 -> 不生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ALTER CHECK constraint_name NOT ENFORCED;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 2.4 不生效 -> 生效
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0) NOT ENFORCED);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ALTER CHECK constraint_name ENFORCED;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 3. 删除
#### 3.1 删除 CHECK 约束名
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student DROP CHECK constraint_name;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 3.2 通过 ALTER ... MODIFY ... ------ 没用
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

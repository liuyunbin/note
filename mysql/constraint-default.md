
## 2. DEFAULT -- 默认值
### 2.1 创建
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 2.2 添加
#### 2.2.1 方式一
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ALTER name SET DEFAULT 'TOM';
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 2.2.2 方式二 (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY name VARCHAR(20) DEFAULT 'TOM';
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

### 2.3 删除
#### 2.3.1 方式一
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ALTER name DROP DEFAULT;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 2.3.2 方式二 (推荐)
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY name VARCHAR(20);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

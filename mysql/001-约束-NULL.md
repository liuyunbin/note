
## NOT NULL -- 非空
#### 1. 创建
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 2. 添加
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT NOT NULL;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

#### 3. 删除
```
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

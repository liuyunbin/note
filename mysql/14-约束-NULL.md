
## NOT NULL
```
* 只能作用在单列上
```

### 1. 创建
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
```

### 2. 添加
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
DESC   student;
ALTER  TABLE student MODIFY id INT NOT NULL;
DESC   student;
```

### 3. 删除
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT NOT NULL);
DESC   student;
ALTER  TABLE student MODIFY id INT;
DESC   student;
```

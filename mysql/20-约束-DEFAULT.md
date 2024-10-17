## DEFAULT --- 默认值
### 1. 创建
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
```

###  2. 添加
####  2.1 方式一
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student ALTER name SET DEFAULT 'TOM';
DESC   student;
```

####  2.2 方式二 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20) DEFAULT 'TOM';
DESC   student;
```

### 3. 删除
#### 3.1 方式一
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
ALTER  TABLE student ALTER name DROP DEFAULT;
DESC   student;
```

#### 3.2 方式二 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) DEFAULT 'TOM');
DESC   student;
ALTER  TABLE student MODIFY name VARCHAR(20);
DESC   student;
```

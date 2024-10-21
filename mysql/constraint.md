
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

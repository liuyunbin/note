
## 1. 两张不同表的多表查询
### 1.1 准备数据
```
USE    test;
DROP   TABLE IF EXISTS teacher1;
CREATE TABLE teacher1 (id INT PRIMARY KEY, name VARCHAR(20), addr VARCHAR(20));
INSERT INTO  teacher1 VALUES(1, "中神通", "全真教");
INSERT INTO  teacher1 VALUES(2, "东邪",   "桃花岛");
INSERT INTO  teacher1 VALUES(3, "西毒",   "西域");
INSERT INTO  teacher1 VALUES(4, "南帝",   "大理");
INSERT INTO  teacher1 VALUES(5, "北丐",   "宋");
INSERT INTO  teacher1 VALUES(6, "中顽童", "全真教");
INSERT INTO  teacher1 VALUES(7, "北侠",   "蒙古");
INSERT INTO  teacher1 VALUES(8, "西狂",   "大宋");

DROP   TABLE IF EXISTS teacher2;
CREATE TABLE teacher2 (id INT PRIMARY KEY, name VARCHAR(20), addr VARCHAR(20));
INSERT INTO  teacher2 VALUES(7,  "北侠",     "蒙古");
INSERT INTO  teacher2 VALUES(10, "金轮法王", "蒙古");
INSERT INTO  teacher2 VALUES(11, "潇湘子",   "蒙古");
INSERT INTO  teacher2 VALUES(12, "尼摩星",   "蒙古");
INSERT INTO  teacher2 VALUES(13, "尹克西",   "蒙古");

DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20), addr VARCHAR(20), teacher_id int);
INSERT INTO  student VALUES(1, "马钰",   "全真教", 1);
INSERT INTO  student VALUES(2, "丘处机", "全真教", 1);
INSERT INTO  student VALUES(3, "王处一", "全真教", 1);
INSERT INTO  student VALUES(4, "黄蓉",   "桃花岛", 2);
INSERT INTO  student VALUES(5, "欧阳克",   "西域", 3);
INSERT INTO  student VALUES(6, "朱子柳",   "大理", 4);
INSERT INTO  student VALUES(7, "路人甲",   "大宋", 111);
```

### 1.2 查询所有的武林人士, 不去重 -- 效率高
```
SELECT name, addr FROM teacher1
UNION  ALL
SELECT name, addr FROM teacher2;
```

### 1.3 查询所有的武林人士, 去重 --- 效率低
```
SELECT name, addr FROM teacher1
UNION
SELECT name, addr FROM teacher2;
```

### 1.4 查询中原徒弟, 师傅信息
#### 1.4.1 情况一 :  师傅徒弟同时存在 (中)
```
SELECT student.name student, teacher1.name teacher
FROM   student, teacher1
WHERE  teacher1.id = student.teacher_id;
```

#### 1.4.2 情况一: 师傅徒弟同时存在 (使用 JOIN) (中)
```
SELECT student.name student, teacher1.name teacher
FROM   student
JOIN   teacher1 
ON     teacher1.id = student.teacher_id;
```

#### 1.4.3 情况一: 师傅徒弟同时存在 (使用 INNER JOIN) (中)
```
SELECT student.name student, teacher1.name teacher
FROM   student
INNER  JOIN teacher1 
ON     teacher1.id = student.teacher_id;
```

#### 1.4.4 情况二: 师傅徒弟同时存在 或 无师傅徒弟信息 (左中)
```
SELECT student.name student, teacher1.name teacher
FROM   student
LEFT   JOIN teacher1 
ON     teacher1.id = student.teacher_id;
```

#### 1.4.5 情况三: 无师傅徒弟信息 (左)
```
SELECT student.name student, teacher1.name teacher
FROM   student
LEFT   JOIN teacher1 
ON     teacher1.id = student.teacher_id
WHERE  teacher1.name IS NULL;
```

#### 1.4.6 情况四: 师傅徒弟同时存在 或 无徒弟的师傅信息 (中右)
```
SELECT student.name student, teacher1.name teacher
FROM   student
RIGHT  JOIN teacher1 
ON     teacher1.id = student.teacher_id;
```

#### 1.4.7 情况五: 无徒弟的师傅信息 (右)
```
SELECT student.name student, teacher1.name teacher
FROM   student
RIGHT  JOIN teacher1 
ON     teacher1.id = student.teacher_id
WHERE  student.name IS NULL;
```

#### 1.4.8 情况六: 无师傅的徒弟信息 或 无徒弟的师傅信息 (左右)
```
SELECT student.name student, teacher1.name teacher
FROM   student
LEFT   JOIN teacher1 
ON     teacher1.id = student.teacher_id
WHERE  teacher1.name IS NULL
UNION  ALL
SELECT student.name student, teacher1.name teacher
FROM   student
RIGHT  JOIN teacher1 
ON     teacher1.id = student.teacher_id
WHERE  student.name IS NULL;
```

#### 1.4.9 情况七: 师傅徒弟同时存在 或 无徒弟的师傅信息 或 无徒弟的师傅信息 (左中右)  --- 效率低
```
SELECT student.name student, teacher1.name teacher
FROM   student
LEFT   JOIN teacher1 
ON     teacher1.id = student.teacher_id
UNION 
SELECT student.name student, teacher1.name teacher
FROM   student
RIGHT  JOIN teacher1 
ON     teacher1.id = student.teacher_id;
```

#### 1.4.10 情况七: 师傅徒弟同时存在 或 无徒弟的师傅信息 或 无徒弟的师傅信息 (左中右)  --- 效率高
```
SELECT student.name student, teacher1.name teacher
FROM   student
LEFT   JOIN teacher1 
ON     teacher1.id = student.teacher_id
WHERE  teacher1.name IS NULL
UNION  ALL
SELECT student.name student, teacher1.name teacher
FROM   student
RIGHT  JOIN teacher1 
ON     teacher1.id = student.teacher_id;
```

## 2. 同一张表的多表查询
### 2.1 准备数据
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20), class_id INT, score DECIMAL);
INSERT INTO  student VALUES(1, "一班张三", 1, 80);
INSERT INTO  student VALUES(2, "一班李四", 1, 100);
INSERT INTO  student VALUES(3, "一班王五", 1, 90);
INSERT INTO  student VALUES(4, "一班赵六", 1, 70);

INSERT INTO  student VALUES(5, "二班张三", 2, 80);
INSERT INTO  student VALUES(6, "二班李四", 2, 100);
INSERT INTO  student VALUES(7, "二班王五", 2, 90);
INSERT INTO  student VALUES(8, "二班赵六", 2, 70);

INSERT INTO  student VALUES(9,  "三班张三", 3, 80);
INSERT INTO  student VALUES(10, "三班李四", 3, 100);
INSERT INTO  student VALUES(11, "三班王五", 3, 90);
INSERT INTO  student VALUES(12, "三班赵六", 3, 70);
```

## 2.2 测试
### 2.2.1 测试成绩比 一班张三 高的学生
```
SELECT s2.*
FROM   student s1, student s2
WHERE  s1.name = '一班张三' AND s2.score > s1.score;
```

### 2.2.2 测试成绩比 一班张三 高的学生, 并且该学生和张三在同一个班
```
SELECT s2.*
FROM   student s1, student s2
WHERE  s1.name = '一班张三' AND s2.score > s1.score AND s2.class_id = s1.class_id;
```

### 2.2.3 测试成绩比 一班张三 高的学生, 并且该学生和张三不在同一个班
```
SELECT s2.*
FROM   student s1, student s2
WHERE  s1.name = '一班张三' AND s2.score > s1.score AND s2.class_id != s1.class_id;
```

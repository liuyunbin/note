
## 1. 测试在 SELECT FROM WHERE HAVING 中使用
```
# 1.1 准备数据
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT PRIMARY KEY, name VARCHAR(20), class_id INT, score DECIMAL);
INSERT INTO  student VALUES(1, "一班张三", 1, 80);
INSERT INTO  student VALUES(2, "一班李四", 1, 100);
INSERT INTO  student VALUES(3, "一班李四四", 1, 100);
INSERT INTO  student VALUES(4, "一班王五", 1, 90);
INSERT INTO  student VALUES(5, "一班赵六", 1, 70);

INSERT INTO  student VALUES(6, "二班张三", 2, 90);
INSERT INTO  student VALUES(7, "二班李四", 2, 99);
INSERT INTO  student VALUES(8, "二班王五", 2, 90);
INSERT INTO  student VALUES(9, "二班赵六", 2, 90);

INSERT INTO  student VALUES(10, "三班张三", 3, 70);
INSERT INTO  student VALUES(11, "三班李四", 3, 98);
INSERT INTO  student VALUES(12, "三班王五", 3, 60);
INSERT INTO  student VALUES(13, "三班赵六", 3, 70);

# 1.2 测试
# 1.2.1 测试成绩比 一班张三 高的学生
SELECT *
FROM student
WHERE score > (
  SELECT score
  FROM   student
  WHERE  name = '一班张三'
);

# 1.2.2 测试成绩比 一班张三 高的学生, 并且该学生和张三在同一个班
SELECT *
FROM student
WHERE score > (
  SELECT score
  FROM   student
  WHERE  name = '一班张三'
)
AND class_id = (
  SELECT class_id
  FROM   student
  WHERE  name = '一班张三'
);

# 1.2.3 测试成绩比 一班张三 高的学生, 并且该学生和张三不在同一个班
SELECT *
FROM student
WHERE score > (
  SELECT score
  FROM student
  WHERE name = '一班张三'
)
AND class_id != (
  SELECT class_id
  FROM student
  WHERE name = '一班张三'
);

# 1.2.4 查看年级平均成绩
SELECT avg(score)
FROM student;

# 1.2.5 查看班级平均成绩
SELECT class_id, avg(score)
FROM student
GROUP BY class_id;

# 1.2.6 测试成绩比平均成绩高的学生
SELECT *
FROM student
WHERE score > (
  SELECT avg(score)
  FROM student
);

# 1.2.7 测试成绩比本班平均成绩高的学生 -- 关联子查询
SELECT *
FROM student s1
WHERE score > (
  SELECT avg(s2.score)
  FROM student s2
  WHERE s1.class_id = s2.class_id
);

# 1.2.8 测试每个学生成绩以及年级平均成绩
SELECT 
  *,
  (SELECT avg(score) FROM student) avg_class
FROM student;

# 1.2.9 测试每个学生成绩以及所属班级平均成绩 --- 关联子查询
SELECT 
  *,
  (
    SELECT avg(score)
    FROM student s2
    WHERE s1.class_id = s2.class_id
  ) avg_class
FROM student s1;

# 1.2.10 测试每个学生成绩以及年级平均成绩
SELECT 
  *
FROM student, (
  SELECT avg(score) FROM student
) s2;

# 1.2.11 测试每个学生成绩以及班级平均成绩
SELECT 
  s1.*,
  s2.avg_score
FROM student s1, (
  SELECT class_id, avg(score) avg_score FROM student GROUP BY class_id
) s2
WHERE s1.class_id = s2.class_id;

# 1.2.12 测试班级平均成绩比一班平均成绩高的班级
SELECT 
    class_id,
    avg(score)
FROM student
GROUP BY class_id
HAVING avg(score) >= (
    SELECT avg(score) FROM student WHERE class_id = 1
);

# 1.2.13 测试成绩最高的学生 (方法一)
SELECT 
    *
FROM  student
WHERE score >= ALL(SELECT score FROM student);

# 1.2.14 测试成绩最高的学生 (方法二)
SELECT 
    *
FROM  student
WHERE score = (SELECT max(score) FROM student);

# 1.2.15 测试成绩最高的学生 (方法三) 有误 -- 只取一个
SELECT 
    *
FROM  student
ORDER BY score DESC
LIMIT 1;

# 1.2.16 测试成绩最高的学生 (方法四)
SELECT 
    *
FROM  student
WHERE NOT score < ANY(SELECT score FROM student);

# 1.2.17 测试成绩最高的学生 (方法五)
SELECT 
    *
FROM  student
WHERE score IN (SELECT  MAX(score) FROM  student);

# 1.2.18 测试成绩最高的学生 (方法六)
SELECT 
    *
FROM  student s1
WHERE NOT EXISTS (SELECT * FROM  student s2 WHERE s1.score < s2.score);

# 1.2.19 测试成绩比任意班平均成绩低的学生
SELECT 
    *
FROM  student
WHERE score < ANY(SELECT avg(score) FROM student GROUP BY class_id);
```

## 2. 测试在 GROUP BY, ORDER BY 中使用
```
# 2.1 准备数据
DROP   TABLE IF EXISTS student_base;
CREATE TABLE student_base (id INT PRIMARY KEY, name VARCHAR(20), score DECIMAL);
INSERT INTO  student_base VALUES(1, "张三", 80);
INSERT INTO  student_base VALUES(2, "李四", 90);
INSERT INTO  student_base VALUES(3, "李四四", 100);
INSERT INTO  student_base VALUES(4, "张五", 90);

DROP   TABLE IF EXISTS student_detail;
CREATE TABLE student_detail (id INT PRIMARY KEY, name VARCHAR(20), province VARCHAR(20));
INSERT INTO  student_detail VALUES(1, "张三", '山西');
INSERT INTO  student_detail VALUES(2, "李四", '天津');
INSERT INTO  student_detail VALUES(3, "李四四", '北京');
INSERT INTO  student_detail VALUES(4, "张五", '山西');

SELECT * FROM student_base;
SELECT * FROM student_detail;

# 2.2 查看每个地区成绩的平均成绩 (GROUP BY)
SELECT
  avg(score)
FROM student_base
GROUP BY (SELECT province FROM student_detail WHERE student_base.id = student_detail.id);

# 2.3 查看成绩按照省份排序 (ORDER BY)
SELECT * FROM student_base;
SELECT * FROM student_detail;

SELECT * FROM student_base
ORDER  BY (SELECT province FROM student_detail WHERE student_base.id = student_detail.id);
```

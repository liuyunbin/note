
## 1. 普通公用表表达式
```
* 和子查询的区别, 可以多次引用
* 相当于是一张临时表

WITH CTE名称 
AS （子查询）
SELECT|DELETE|UPDATE 语句;

# 1. 准备数据
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

# 2. 测试
# 2.1 测试成绩比 一班张三 高的学生, 并且该学生和张三在同一个班 (子查询)
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

# 2.2 测试成绩比 一班张三 高的学生, 并且该学生和张三在同一个班 (公共表表达式)
WITH t1
AS (SELECT * FROM student WHERE name = '一班张三')
SELECT student.*
FROM student, t1
WHERE student.score > t1.score AND student.class_id = t1.class_id;
```

## 2. 递归公用表表达式
```
WITH RECURSIVE
CTE名称 AS （子查询）
SELECT|DELETE|UPDATE 语句;

# 1. 准备数据
DROP   TABLE IF EXISTS employees;
CREATE TABLE employees (id INT PRIMARY KEY, name VARCHAR(20), manager_id INT);
INSERT INTO  employees VALUES(1, "汉献帝", -1);

INSERT INTO  employees VALUES(2, "曹操", 1);
INSERT INTO  employees VALUES(3, "孙权", 1);
INSERT INTO  employees VALUES(4, "刘备", 1);

INSERT INTO  employees VALUES(5, "曹丕", 2);
INSERT INTO  employees VALUES(6, "曹仁", 2);
INSERT INTO  employees VALUES(7, "曹真", 2);
INSERT INTO  employees VALUES(8, "曹彰", 2);

INSERT INTO  employees VALUES(9,  "周瑜", 3);
INSERT INTO  employees VALUES(10, "鲁肃", 3);
INSERT INTO  employees VALUES(11, "吕蒙", 3);
INSERT INTO  employees VALUES(12, "陆逊", 3);

INSERT INTO  employees VALUES(13, "关羽",   4);
INSERT INTO  employees VALUES(14, "张飞",   4);
INSERT INTO  employees VALUES(15, "赵云",   4);
INSERT INTO  employees VALUES(16, "诸葛亮", 4);

INSERT INTO  employees VALUES(17, "司马懿",   5);
INSERT INTO  employees VALUES(18, "司马师",   5);
INSERT INTO  employees VALUES(19, "司马昭",   5);

INSERT INTO  employees VALUES(20, "姜维", 16);

# 2. 测试
# 2.1 显示第四层员工
SELECT * FROM employees;

WITH RECURSIVE cte 
AS 
(
    SELECT id, name, manager_id, 1 AS n FROM employees WHERE manager_id = -1 -- 找到根: 汉献帝
    UNION ALL
    SELECT a.id, a.name, a.manager_id, n + 1
    FROM employees AS a JOIN cte
    ON (a.manager_id = cte.id) -- 递归查询
)
SELECT id, name FROM cte WHERE n = 4; 
```


## 1. 窗口函数
```
在不改变原表行数的情况下进行分组和排序计算
GROUP BY: 分组并合并
窗口函数: 分组不合并

语法:
窗口函数 OVER (PARTITION BY 分组的列 ORDER BY 排序的列 ROWS  BETWEEN <数据范围> AND <数据范围>)
窗口函数 OVER (PARTITION BY 分组的列 ORDER BY 排序的列 RANGE BETWEEN <数据范围> AND <数据范围>)

数据范围:
current row ---------------- 当前行
数字      preceding -------- 当前行的前n行, 或 当前值减数字
unbounded preceding -------- 第一行
数字      following -------- 当前行的后n行, 或 当前值加数字
unbounded following -------- 最后一行

  有 ORDER BY 没有 ROWS BETWEEN 时, 窗口取: [第一行, 本行]
没有 ORDER BY 没有 ROWS BETWEEN 时, 窗口取: [第一行, 最后一行] --- 当前分组

动态窗口函数: FIRST_VALUE() LAST_VALUE() NTH_VALUE()  SUM() AVG() MAX() MIN() COUNT()
静态窗口函数: ROW_NUMBER() RANK() DENSE_RANK() PERCENT_RANK() CUME_DIST() LAG() LEAD() NTILE()

数据范围只针对动态窗口函数有效

常见使用场景
* 组内比较
* 组内topN
* 累计求和
* 连续登录
```

## 测试窗口函数
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  name      VARCHAR(20),
  class_id  INT,
  score     DECIMAL
);

INSERT INTO student VALUES('张三', 1, 99);
INSERT INTO student VALUES('张四', 1, 100);
INSERT INTO student VALUES('张五', 1, 99);
INSERT INTO student VALUES('张六', 1, 98);

INSERT INTO student VALUES('李三', 2, 89);
INSERT INTO student VALUES('李四', 2, 88);
INSERT INTO student VALUES('李五', 2, 89);
INSERT INTO student VALUES('李六', 2, 87);

INSERT INTO student VALUES('王三', 3, 79);
INSERT INTO student VALUES('王四', 3, 78);
INSERT INTO student VALUES('王五', 3, 79);
INSERT INTO student VALUES('王六', 3, 77);

SELECT * FROM student ORDER BY score DESC;

# 1. 测试 序号函数 ----- 静态窗口函数
RANK() --------------- 相同的值排名  相同, 排名不连续, 例如 1 2 2 4
DENSE_RANK() --------- 相同的值排名  相同, 排名  连续, 例如 1 2 2 3
ROW_NUMBER() --------- 相同的值排名不相同, 排名  连续, 例如 1 2 3 4

# 1.1 比较三个序号函数的区别
SELECT
  *,
         RANK() OVER w t_rank,
   DENSE_RANK() OVER w t_dense_rank,
   ROW_NUMBER() OVER w t_row_number
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC);

# 1.2 证明是 静态窗口函数, 使用  ROWS BETWEEN ... AND ... , 没用
SELECT
  *,
        RANK() OVER (PARTITION BY class_id ORDER BY score DESC) rank_1,
        RANK() OVER (PARTITION BY class_id ORDER BY score DESC
                      ROWS BETWEEN current row AND 1 following) rank_2,
  DENSE_RANK() OVER (PARTITION BY class_id ORDER BY score DESC) dense_rank_1,
  DENSE_RANK() OVER (PARTITION BY class_id ORDER BY score DESC
                      ROWS BETWEEN current row AND 1 following) dense_rank_2,
  ROW_NUMBER() OVER (PARTITION BY class_id ORDER BY score DESC) row_number_1,
  ROW_NUMBER() OVER (PARTITION BY class_id ORDER BY score DESC
                      ROWS BETWEEN current row AND 1 following) row_number_2
FROM student;

# 2. 测试 分布函数 ----- 静态窗口函数
PERCENT_RANK() ------- 排名百分比:  (rank - 1) / (rows - 1)
CUME_DIST() ---------- 小于等于 或大于等于某一值的比例

# 2.1 比较两个分布函数的区别
SELECT
  *,
  PERCENT_RANK() OVER w t_percent_rank,
     CUME_DIST() OVER w t_cume_dist
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC);

# 2.2 证明是 静态窗口函数, 使用  ROWS BETWEEN ... AND ... , 没用
SELECT
  *,
  PERCENT_RANK() OVER (PARTITION BY class_id ORDER BY score DESC) percent_rank_1,
  PERCENT_RANK() OVER (PARTITION BY class_id ORDER BY score DESC
                        ROWS BETWEEN current row AND 1 following) percent_rank_2,
     CUME_DIST() OVER (PARTITION BY class_id ORDER BY score DESC) cume_dist_1,
     CUME_DIST() OVER (PARTITION BY class_id ORDER BY score DESC
                        ROWS BETWEEN current row AND 1 following) cume_dist_2
FROM student;

# 3. 测试 前后函数 ----- 静态窗口函数
 LAG(expr, n) --------- 当前行的前n行的expr的值
LEAD(expr, n) --------- 当前行的后n行的expr的值

# 3.1 比较两个前后函数的区别
SELECT
  *,
   LAG(score, 1) OVER w t_lag,
  LEAD(score, 1) OVER w t_lead
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC);

# 3.2 证明是 静态窗口函数, 使用  ROWS BETWEEN ... AND ... ,没用
SELECT
  *,
  LAG(score, 1)  OVER (PARTITION BY class_id ORDER BY score DESC) lag_1,
  LAG(score, 1)  OVER (PARTITION BY class_id ORDER BY score DESC
                      ROWS BETWEEN current row AND 1 following)   lag_2,
  LEAD(score, 1) OVER (PARTITION BY class_id ORDER BY score DESC) lead_1,
  LEAD(score, 1) OVER (PARTITION BY class_id ORDER BY score DESC
                      ROWS BETWEEN current row AND 1 following)   lead_2
FROM student;

# 4. 测试 NTILE(n) 函数 ----- 静态窗口函数
将数据分成 n 组, 返回组编号

# 4.1 测试
SELECT
  *,
  NTILE(2) OVER w t_ntile
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC);

# 4.2 证明是 静态窗口函数, 使用  ROWS BETWEEN ... AND ... ,没用
SELECT
  *,
  NTILE(2) OVER (PARTITION BY class_id ORDER BY score DESC) ntile_1,
  NTILE(2) OVER (PARTITION BY class_id ORDER BY score DESC
                  ROWS BETWEEN current row AND 1 following) ntile_2
FROM student;

# 5. 动态窗口函数
FIRST_VALUE(expr) ---- 第一个expr的值
 LAST_VALUE(expr) ---- 最后一个expr的值
  NTH_VALUE(expr,n) -- 第n个expr的值 
  
# 5.1 无 ORDER BY 无 rows between ----- 窗口是分组下所有行
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id);

# 5.2 有 ORDER BY 无 rows between ----- 窗口是 [第一行, 当前行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC);

# 5.3 有 ORDER BY 有 rows between ----- 指定窗口 [第一行, 当前行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
            ROWS BETWEEN unbounded preceding AND current row);

# 5.4 有 ORDER BY 有 rows between ----- 指定窗口 [当前行的前两行, 当前行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
            ROWS BETWEEN 2 preceding AND current row);

# 5.5 有 ORDER BY 有 rows between ----- 指定窗口 [当前行, 最后一行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
            ROWS BETWEEN current row AND unbounded following);
  
# 5.6 有 ORDER BY 有 rows between ----- 指定窗口 [当前行, 当前行的后两行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
              ROWS BETWEEN current row AND 2 following);

# 5.7 有 ORDER BY 有 rows between ----- 指定窗口 [当前行的前一行, 当前行的后一行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
              ROWS BETWEEN 1 preceding AND 1 following);

# 5.8 有 ORDER BY 有 rows between ----- 指定窗口 [第一行, 最后一行]
SELECT
  *,
  FIRST_VALUE(score)   OVER w t_first,
   LAST_VALUE(score)   OVER w t_last, 
    NTH_VALUE(score,2) OVER w t_nth
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
             ROWS BETWEEN unbounded preceding AND unbounded following);

# 5.9 聚合函数同上
SELECT
  *,
    SUM(score) OVER w t_sum,
    AVG(score) OVER w t_avg,
  COUNT(score) OVER w t_count,
    MAX(score) OVER w t_max,
    MIN(score) OVER w t_min
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
             ROWS BETWEEN 1 preceding AND current row);

# 5.10 使用 RANGE
SELECT
  *,
    sum(score) OVER w t_sum,
    avg(score) OVER w t_avg,
  count(score) OVER w t_count,
    max(score) OVER w t_max,
    min(score) OVER w t_min
FROM student
WINDOW w AS (PARTITION BY class_id ORDER BY score DESC
             RANGE BETWEEN 1 preceding AND current row);
```

## 2. 实战
### 2.1 查看各个市 GDP 占各自省的比例以及全国的比例以及排名 (体现窗口函数的优势)
```
# 1.1 准备数据
USE    test;
DROP   TABLE IF EXISTS m_gdp;
CREATE TABLE m_gdp(
  province VARCHAR(20),
  city     VARCHAR(20),
  gdp      DECIMAL
);

INSERT INTO m_gdp VALUES('山西', '晋中', 5);
INSERT INTO m_gdp VALUES('山西', '太原', 10);
INSERT INTO m_gdp VALUES('山西', '临汾', 8);
INSERT INTO m_gdp VALUES('山西', '大同', 6);

INSERT INTO m_gdp VALUES('北京', '昌平', 5);
INSERT INTO m_gdp VALUES('北京', '朝阳', 10);
INSERT INTO m_gdp VALUES('北京', '海淀', 8);
INSERT INTO m_gdp VALUES('北京', '东城', 6);

INSERT INTO m_gdp VALUES('天津', '滨海新区', 5);
INSERT INTO m_gdp VALUES('天津', '武清', 6);
INSERT INTO m_gdp VALUES('天津', '塘沽', 7);

SELECT * FROM m_gdp;

# 1.2 使用窗口函数 (推荐)
SELECT
  *,
  RANK() OVER (PARTITION BY province ORDER BY gdp DESC) '省内排名',
  RANK() OVER (                      ORDER BY gdp DESC) '全国排名',
        SUM(gdp) OVER (PARTITION BY province) '省内总和',
  gdp / SUM(gdp) OVER (PARTITION BY province) '省内占比',  
        SUM(gdp) OVER () '全国总和',
  gdp / SUM(gdp) OVER () '全国占比'
FROM m_gdp
ORDER BY province, RANK() OVER (ORDER BY gdp DESC);

# 1.3 不使用窗口函数
# 1.3.1 存储全国 GDP 的总和
DROP   TABLE IF EXISTS sum_total;
CREATE TEMPORARY TABLE sum_total AS SELECT sum(gdp) sum_total FROM m_gdp;
SELECT * FROM sum_total;
# 1.3.2 存储全省 GDP 的总和
DROP   TABLE IF EXISTS sum_province;
CREATE TEMPORARY TABLE sum_province AS SELECT province, sum(gdp) sum_province FROM m_gdp GROUP BY province;
SELECT * FROM sum_province;
# 1.3.3 存储全国排名
DROP   TABLE IF EXISTS rank_total;
CREATE TEMPORARY TABLE rank_total
AS
SELECT
  m1.city,
  m1.province,
  (SELECT count(*) FROM m_gdp m2 WHERE m2.gdp > m1.gdp) + 1 AS t_rank
FROM m_gdp m1;
SELECT * FROM rank_total ORDER BY t_rank;
# 1.3.4 存储省内排名
DROP   TABLE IF EXISTS rank_province;
CREATE TEMPORARY TABLE rank_province
AS
SELECT
  m1.city,
  m1.province,
  (SELECT count(*) FROM m_gdp m2 WHERE m2.province = m1.province AND m2.gdp > m1.gdp) + 1 AS t_rank
FROM m_gdp m1;
SELECT * FROM rank_province ORDER BY t_rank;
# 1.3.5 使用五张表求结果
SELECT
 m_gdp.province,
 m_gdp.city,
 m_gdp.gdp,
 rank_province.t_rank '省内排名',
 rank_total.t_rank '全国排名',
 sum_province.sum_province '省内总和',
 m_gdp.gdp / sum_province.sum_province '省内占比',
 sum_total.sum_total '全国总和',
 m_gdp.gdp / sum_total.sum_total '全国占比' 
FROM m_gdp
JOIN sum_province ON m_gdp.province = sum_province.province
JOIN rank_total ON m_gdp.city = rank_total.city
JOIN rank_province ON m_gdp.city = rank_province.city
JOIN sum_total
ORDER BY province, RANK() OVER (ORDER BY gdp DESC);
```

### 2.2 查看各个市 GDP 占各自省内排名前二的区域
```
# 2.1 准备数据
USE    test;
DROP   TABLE IF EXISTS m_gdp;
CREATE TABLE m_gdp(
  province VARCHAR(20),
  city     VARCHAR(20),
  gdp      DECIMAL
);

INSERT INTO m_gdp VALUES('山西', '晋中', 5);
INSERT INTO m_gdp VALUES('山西', '太原', 10);
INSERT INTO m_gdp VALUES('山西', '临汾', 10);
INSERT INTO m_gdp VALUES('山西', '大同', 10);

INSERT INTO m_gdp VALUES('北京', '昌平', 5);
INSERT INTO m_gdp VALUES('北京', '朝阳', 10);
INSERT INTO m_gdp VALUES('北京', '海淀', 8);
INSERT INTO m_gdp VALUES('北京', '东城', 8);

INSERT INTO m_gdp VALUES('天津', '滨海新区', 5);
INSERT INTO m_gdp VALUES('天津', '武清', 6);
INSERT INTO m_gdp VALUES('天津', '塘沽', 6);

# 2.2 并列的数据都返回, 每组结果可能超过两个
SELECT *
FROM (
  SELECT
    city,
    province,
    gdp,
    RANK() OVER (PARTITION BY province ORDER BY gdp DESC) m_rank
  FROM m_gdp
) t
WHERE t.m_rank <= 2;

# 2.3 每组结果可能最多两个, 并列的数据只取前两个
SELECT *
FROM (
  SELECT
    city,
    province,
    gdp,
    ROW_NUMBER() OVER (PARTITION BY province ORDER BY gdp DESC) m_rank
  FROM m_gdp
) t
WHERE t.m_rank <= 2;
```

### 2.3 综合测试
```
# 3.1 准备数据, 内容为 日期和销售额
USE    test;
DROP   TABLE IF EXISTS m_company;
CREATE TABLE m_company (
  order_date DATE UNIQUE,
  sale       DECIMAL
);

INSERT INTO m_company VALUES('2023-10-01', 7);
INSERT INTO m_company VALUES('2023-11-01', 8);
INSERT INTO m_company VALUES('2023-12-01', 11);
INSERT INTO m_company VALUES('2024-01-01', 5);
INSERT INTO m_company VALUES('2024-02-01', 6);
INSERT INTO m_company VALUES('2024-03-01', 7);
INSERT INTO m_company VALUES('2024-04-01', 8);
INSERT INTO m_company VALUES('2024-05-01', 9);
INSERT INTO m_company VALUES('2024-06-01', 3);
INSERT INTO m_company VALUES('2024-07-01', 4);
INSERT INTO m_company VALUES('2024-08-01', 5);
INSERT INTO m_company VALUES('2024-09-01', 6);
INSERT INTO m_company VALUES('2024-10-01', 7);
INSERT INTO m_company VALUES('2024-11-01', 8);
INSERT INTO m_company VALUES('2024-12-01', 11);
INSERT INTO m_company VALUES('2025-01-01', 5);
INSERT INTO m_company VALUES('2025-02-01', 6);
INSERT INTO m_company VALUES('2025-03-01', 7);
INSERT INTO m_company VALUES('2025-04-01', 8);

INSERT INTO m_company VALUES('2023-10-02', 7);
INSERT INTO m_company VALUES('2023-11-02', 8);
INSERT INTO m_company VALUES('2023-12-02', 11);
INSERT INTO m_company VALUES('2024-01-02', 5);
INSERT INTO m_company VALUES('2024-02-02', 6);
INSERT INTO m_company VALUES('2024-03-02', 7);
INSERT INTO m_company VALUES('2024-04-02', 8);
INSERT INTO m_company VALUES('2024-05-02', 9);
INSERT INTO m_company VALUES('2024-06-02', 3);
INSERT INTO m_company VALUES('2024-07-02', 4);
INSERT INTO m_company VALUES('2024-08-02', 5);
INSERT INTO m_company VALUES('2024-09-02', 6);
INSERT INTO m_company VALUES('2024-10-02', 7);
INSERT INTO m_company VALUES('2024-11-02', 8);
INSERT INTO m_company VALUES('2024-12-02', 11);
INSERT INTO m_company VALUES('2025-01-02', 5);
INSERT INTO m_company VALUES('2025-02-02', 6);
INSERT INTO m_company VALUES('2025-03-02', 7);
INSERT INTO m_company VALUES('2025-04-02', 8);

SELECT * FROM m_company ORDER BY order_date;

# 3.2 查看公司各个月的销售
SELECT
  year(order_date) year,
  month(order_date) month,
  SUM(sale) sale
FROM m_company
GROUP BY year(order_date), month(order_date)

# 3.3 查看公司各个月的销售和每个月累计销售, 年销售总额
SELECT
  year '年',
  month '月',
  sale '当月销售',
  SUM(sale) OVER(PARTITION BY year ORDER BY month) '月累计销售', 
  SUM(sale) OVER(PARTITION BY year               ) '年总销售'
FROM (
  SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
  FROM m_company
  GROUP BY year(order_date), month(order_date)
) t;

# 3.3 查看公司各个月的销售和年销售总额, 月销售占比
SELECT
  year '年',
  month '月',
  sale '当月销售',
         SUM(sale) OVER w1 '年总销售', 
  sale / SUM(sale) OVER w1 '月销售占比'
FROM (
  SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
  FROM m_company
  GROUP BY year(order_date), month(order_date)
) t
WINDOW w1 AS (PARTITION BY year);

# 3.4 销售量前二的月份及其占比
SELECT *
FROM
(
  SELECT
    year '年',
    month '月',
    sale '当月销售',
           SUM(sale) OVER w1 '年总销售', 
    sale / SUM(sale) OVER w1 '月销售占比',
    RANK() OVER (PARTITION BY year ORDER BY sale DESC) row_rank
  FROM (
    SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
    FROM m_company
    GROUP BY year(order_date), month(order_date)
  ) t1
  WINDOW w1 AS (PARTITION BY year)
) t2
WHERE t2.row_rank <= 2;

# 3.5 销售量的季度和
SELECT *
FROM
(
  SELECT
    year '年',
    month '月',
    sale '当月销售',
    SUM(sale) OVER(PARTITION BY year) '年总销售',
    SUM(sale) OVER(PARTITION BY year ORDER BY month ROWS BETWEEN 2 preceding AND current row) '三个月的和'
  FROM (
    SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
    FROM m_company
    GROUP BY year(order_date), month(order_date)
  ) t1
) t2
WHERE t2.月 % 3 = 0;

# 3.6 销售量的季度和及其占比
SELECT *
FROM
(
  SELECT
    year '年',
    month '月',
    sale '当月销售',
    SUM(sale) OVER w2 '年总销售',
    SUM(sale) OVER w1,
    SUM(sale) OVER w1 / SUM(sale) OVER w2 '占比'
  FROM (
    SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
    FROM m_company
    GROUP BY year(order_date), month(order_date)
  ) t1
  WINDOW w1 AS (PARTITION BY year ORDER BY month ROWS BETWEEN 2 preceding AND current row),
         w2 AS (PARTITION BY year)
) t2
WHERE t2.月 % 3 = 0;

# 3.7 月销售量排名
SELECT
   year '年',
   month '月',
   sale '当月销售',
   RANK() OVER(PARTITION BY year ORDER BY sale DESC) row_rank
FROM (
   SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
   FROM m_company
   GROUP BY year(order_date), month(order_date)
) t1
ORDER BY year, row_rank;

# 3.8 月销售量排名前 40% 的月份
SELECT *
FROM (
  SELECT
    year '年',
    month '月',
    sale '当月销售',
    NTILE(12) OVER(PARTITION BY year ORDER BY sale DESC) row_level
  FROM (
    SELECT year(order_date) year, month(order_date) month, SUM(sale) sale
    FROM m_company
    GROUP BY year(order_date), month(order_date)
  ) t1
) t2
WHERE row_level <= 4;

# 3.9 月销售量比前一个月高的月份
SELECT *
FROM (
  SELECT
    month,
    sale,
    LAG(sale, 1) OVER(ORDER BY month) last_price
  FROM (
    SELECT SUBSTRING(order_date,1,7) month, SUM(sale) sale
    FROM m_company
    GROUP BY SUBSTRING(order_date,1,7)
  ) t1
) t2
WHERE last_price < sale OR last_price IS NULL;
```

### 2.4 连续登录的最大天数
```
# 4.1 准备数据, 内容为 ID, 用户名, 日期
USE    test;
DROP   TABLE IF EXISTS m_user;
CREATE TABLE m_user (
  id         INT,
  name       VARCHAR(20),
  login_date DATE
);

INSERT INTO m_user VALUES(1, '张三', '2023-10-01');
INSERT INTO m_user VALUES(1, '张三', '2023-10-02');
INSERT INTO m_user VALUES(1, '张三', '2023-10-04');
INSERT INTO m_user VALUES(1, '张三', '2023-10-05');
INSERT INTO m_user VALUES(1, '张三', '2023-10-06');
INSERT INTO m_user VALUES(1, '张三', '2023-10-08');

INSERT INTO m_user VALUES(2, '李四', '2023-10-01');
INSERT INTO m_user VALUES(2, '李四', '2023-10-02');
INSERT INTO m_user VALUES(2, '李四', '2023-10-05');
INSERT INTO m_user VALUES(2, '李四', '2023-10-06');
INSERT INTO m_user VALUES(2, '李四', '2023-10-08');

INSERT INTO m_user VALUES(3, '王五', '2023-10-01');
INSERT INTO m_user VALUES(3, '王五', '2023-10-05');
INSERT INTO m_user VALUES(3, '王五', '2023-10-06');
INSERT INTO m_user VALUES(3, '王五', '2023-10-08');

# 为了测试重复
INSERT INTO m_user VALUES(1, '张三', '2023-10-01');
INSERT INTO m_user VALUES(1, '张三', '2023-10-02');
INSERT INTO m_user VALUES(1, '张三', '2023-10-04');

SELECT * FROM m_user ORDER BY id, login_date;

# 4.2 去重
SELECT DISTINCT * FROM m_user;

# 4.3 用户分组, 日期排名
SELECT
  *,
  rank() OVER (PARTITION BY id ORDER BY login_date) row_rank
FROM (SELECT DISTINCT * FROM m_user) t1;

# 4.4 求日期和排名的差值
SELECT
  *,
  DATE_SUB(login_date, INTERVAL row_rank DAY) AS diffe_date
FROM (
  SELECT
    *,
    rank() OVER (PARTITION BY id ORDER BY login_date) row_rank
  FROM (SELECT DISTINCT * FROM m_user) t1
  ) t2

# 4.5 统计连续登录的信息
SELECT
  id,
  name,
  min(login_date) begin_date,
  max(login_date)   end_date,
  count(*)
FROM (
  SELECT
    *,
    DATE_SUB(login_date, INTERVAL row_rank DAY) AS diff_date
  FROM (
    SELECT
      *,
      rank() OVER (PARTITION BY id ORDER BY login_date) row_rank
    FROM (SELECT DISTINCT * FROM m_user) t1
  ) t2
) t3
GROUP BY id, name, diff_date
HAVING count(*) > 1;
```

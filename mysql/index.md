
## INDEX --- 索引
```
* 类型
  * 普通索引 ----- 无任何限制
  * 唯一索引 ----- 和 唯一键 对应
  * 主键索引 ----- 和   主键 对应
  * 全文索引 ----- 很少使用
  * 空间索引 ----- 很少使用
* 范围
  * 单列索引 -----
  * 多列索引 ----- 最左前缀原则 -- 最常用的放最左边
* 实现
  * 聚簇索引 ----- 主键 -- 只有一个
  * 非聚簇索引 --- 可以多个
* 新特性
  * 降序索引 ----- 如果查找是降序的话, 可以提高效率 --- DESC
  * 隐藏索引 ----- 便于观察删除索引的影响 --- INVISIBLE VISIBLE
* 适合建索引
    * WHERE GROUP BY ORDER BY 中频繁使用
    * 区分度大的列
    * DISTINCT 列
    * 很少变化的列
* 不适合建索引
    * 表很小
* 联合索引好于多个单列索引
* 删除无用或冗余的索引
```

### 1. 创建
#### 1.1 单列: 不指定索引名称: 索引名称默认是列名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id));
SHOW   INDEX FROM student;
```

#### 1.2 单列: 指定索引名称
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
```

#### 1.3 多列: 不指定索引名称: 索引名称默认是第一个列名
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX(id, name));
SHOW   INDEX FROM student;
```

#### 1.4 多列: 指定索引名称
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), INDEX index_name(id, name));
SHOW   INDEX FROM student;
```

#### 1.5 降序索引
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id));
SHOW   INDEX FROM student;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id DESC));
SHOW   INDEX FROM student;
```

#### 1.6 不可见索引
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id) VISIBLE);
SHOW   INDEX FROM student;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX(id) INVISIBLE);
SHOW   INDEX FROM student;
```

### 2. 添加 或 修改
#### 2.1 使用 CREATE INDEX 添加 (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
CREATE INDEX index_name ON student(id);
SHOW   INDEX FROM student;
```

#### 2.2 使用 ALTER 添加
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SHOW   INDEX FROM student;
ALTER  TABLE student ADD INDEX index_name(id);
SHOW   INDEX FROM student;
```

#### 2.3 设置索引是否可见
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name INVISIBLE;
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX index_name VISIBLE;
SHOW   INDEX FROM student;
```

### 3. 删除
#### 3.1 使用 DROP (推荐)
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
DROP   INDEX index_name ON student;
SHOW   INDEX FROM student;
```

#### 3.2 使用 ALTER
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX index_name;
SHOW   INDEX FROM student;
```

### 4. 重命名索引
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, INDEX index_name(id));
SHOW   INDEX FROM student;
ALTER  TABLE student RENAME INDEX index_name TO new_index_name;
SHOW   INDEX FROM student;
```

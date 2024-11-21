



## 3. `auto_increment` -- 自动递增
```
* 只能作用于整形
* 最多只有一列
* 列必须是主键或唯一键
* 该列将变成非空

# 3.1 创建
# 3.1.1 单列 (整形): 作用于主键
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 3.1.2 单列 (整形): 作用于唯一键, 非空, 无主键时, 该列会变成主键
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 3.1.3 单列 (整形): 作用于唯一键, 有其他主键时, 该列还是唯一键
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT PRIMARY KEY);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 3.1.4 单列 (非整形) -- 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20) UNIQUE AUTO_INCREMENT);

# 3.1.5 多列 (整形) -- 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE AUTO_INCREMENT, idd INT UNIQUE AUTO_INCREMENT);

# 3.1.6 单列 (整形, 非主键和唯一键) -- 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT AUTO_INCREMENT, idd INT UNIQUE);

# 3.1.7 单列 -- 默认初始值为 1
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;

# 3.1.8 单列 -- 设置初始值为 10
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20))AUTO_INCREMENT = 10;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;

# 3.2 添加
# 3.2.1 初始值为 1
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT AUTO_INCREMENT;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;

# 3.2.2 设置初始值为 10
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student AUTO_INCREMENT = 10;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
INSERT INTO student(name) VALUES('BOB');
SELECT * FROM student;

# 3.3 删除
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY AUTO_INCREMENT);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

## 4. CHECK --- 检查
```
* 只能通过删除 CHECK 约束名来删除 CHECK 约束
* 可以使 CHECK 不生效

# 4.1 创建
# 4.1.1 列级约束: 约束名由系统生成 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT CHECK(id > 0), name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.2 列级约束: 约束名由系统生成 (推荐) -- 约束不生效
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT CHECK(id > 0) NOT ENFORCED, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.3 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.4 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐) -- 约束不生效
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0) NOT ENFORCED);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.5 表级约束(单列): 指定约束名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  id INT,
  name VARCHAR(20),
  CONSTRAINT constraint_name CHECK(id > 0)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.6 表级约束(单列): 指定约束名 -- 约束不生效
DROP   TABLE IF EXISTS student;
CREATE TABLE student(
  id INT,
  name VARCHAR(20),
  CONSTRAINT constraint_name CHECK(id > 0) NOT ENFORCED
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.7 表级约束(多列): (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0 AND LENGTH(name) > 1));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.1.8 表级约束(多列): (推荐) -- 约束不生效
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CHECK(id > 0 AND LENGTH(name) > 1) NOT ENFORCED);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.2 添加 或 修改
# 4.2.1 可以添加列级和表级约束 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ADD CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.2.2 只能添加列级约束
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT CHECK(id > 0);
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.2.3 生效 -> 不生效
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ALTER CHECK constraint_name NOT ENFORCED;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.2.4 不生效 -> 生效
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0) NOT ENFORCED);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student ALTER CHECK constraint_name ENFORCED;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.3 删除
# 4.3.1 删除 CHECK 约束名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student DROP CHECK constraint_name;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';

# 4.3.2 通过 ALTER ... MODIFY ... ------ 没用
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name CHECK(id > 0));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
ALTER  TABLE student MODIFY id INT;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
```

## 5. primary KEY --- 主键
```
* 会自动创建主键索引
* 不可以存储 NULL
* 存储的值不能相同
* 索引名和约束名是 PRIMARY
* 设置或修改索引名和约束名没意义
* 最多只存在一个主键
* 可以对多列定义一个主键
* 删除主键约束只能通过删除主键来实现, 删除主键索引或主键约束名报错
* 删除主键约束后, 主键索引也会删除, 但非空约束还在
* 和唯一键的区别: 非空 + 最多只有一个
* 主键不能是不可见的

# 5.1 创建
# 5.1.1 列级约束(单列): 约束名和索引名为 PRIMARY (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.2 列级约束(多列): 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20) PRIMARY KEY);

# 5.1.3 表级约束, 不指定约束名和索引名: 约束名和索引名都为 PRIMARY (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.4 表级约束, 指定约束名和索引名: 约束名和索引名都为 PRIMARY
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name PRIMARY KEY index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.5 表级约束, 只指定约束名: 约束名和索引名都为 PRIMARY
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name PRIMARY KEY(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.6 表级约束, 只指定索引名: 约束名和索引名都为 PRIMARY
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.7 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.8 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.1.9 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐) --- 主键不能不可见
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), PRIMARY KEY(id, name) INVISIBLE);

# 5.2 添加
# 5.2.1 可以添加表级或列级主键约束 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD PRIMARY KEY(id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.2.2 只能添加列级主键约束
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student MODIFY id INT PRIMARY KEY;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.3 删除
# 5.3.1 删除主键: 会删除对应的索引, 但非空约束还在
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP PRIMARY KEY;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 5.3.2 删除主键约束名: 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINT PRIMARY;

# 5.3.3 删除主键索引: 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX PRIMARY;

# 5.4 不可以存储 NULL, 不可以重复
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
INSERT INTO student VALUES(NULL, "BOB"); # 报错
INSERT INTO student VALUES(1,    "TOM");
SELECT * FROM student;
INSERT INTO student VALUES(1,    "BOB"); # 报错
```

## 6. UNIQUE --- 唯一键
```
* 会创建唯一索引
* 可以存储 NULL
* 存储的值不能相同, 但 NULL 可以多个
* 默认的索引名和约束名是第一列的列名
* 可以存在多个唯一键
* 可以对多列定义一个唯一键
* 只能通过删除唯一索引的方式删除唯一键
* 删除唯一约束名报错

# 6.1 创建
# 6.1.1 列级约束(单列): 约束名和索引名默认和列名相同 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.2 列级约束(多列): 约束名和索引名默认和列名相同 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20) UNIQUE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.3 表级约束(单列), 不指定约束名和索引名: 约束名和索引名都是列名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.4 表级约束(单列), 同时指定约束名和索引名: 约束名没意义, 约束名和索引名都变成索引名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name UNIQUE index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.5 表级约束(单列), 只指定约束名: 约束名和索引名都变成约束名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), CONSTRAINT constraint_name UNIQUE(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.6 表级约束(单列), 只指定索引名: 约束名和索引名都变成索引名
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE index_name(id));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.7 表级约束(多列): 约束名和索引名默认和第一列的列名相同 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id, name));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.1.8 表级约束(多列): 约束名和索引名默认和第一列的列名相同 (推荐) -- 索引不可见
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id, name) INVISIBLE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.2 添加
# 6.2.1 可以添加表级或列级唯一约束 (推荐)
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD UNIQUE (id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.2.2 只能添加列级唯一约束
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student MODIFY id INT UNIQUE;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.2.3 可见 -> 不可见
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX id INVISIBLE;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.2.4 不可见 -> 可见
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT, name VARCHAR(20), UNIQUE(id) INVISIBLE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ALTER INDEX id VISIBLE;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.3 删除
# 6.3.1 删除唯一索引: 使用 ALTER
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX id;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.3.2 删除唯一索引: 使用 DROP
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
DROP   INDEX id ON student;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 6.3.3 删除唯一约束名: 报错
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20));
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINTS id;

# 6.4 可以存储 NULL, NULL 可以重复, 其他不行
DROP   TABLE IF EXISTS student;
CREATE TABLE student(id INT UNIQUE, name VARCHAR(20) UNIQUE);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
INSERT INTO student VALUES(NULL, "BOB");
SELECT * FROM student;
INSERT INTO student VALUES(NULL, "TOM");
SELECT * FROM student;
INSERT INTO student VALUES(NULL, "BOB"); # 报错
```

## 7. FOREIGN KEY --- 外键
```
* 会自动创建索引
* 从表的外键必须是主表的主键或唯一键
* 先创建主表, 再创建从表
* 先删除从表或外键, 再删除主表
* 默认外键的外键名不是列名, 默认的索引名是列名
* 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
* 通过删除外键约束名或外键可以删除外键, 不能通过删除外键索引来删除外键
* 删除外键后, 外键索引还存在
* 外键可以有多个

# 7.1 创建
# 7.1.1 不指定约束名和索引名: 约束名不是列名, 由系统生成, 索引名是列名 (建议)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.1.2 同时指定约束名和索引名: 索引名没意义, 约束名和索引名都变成指定的约束名
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY index_name(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.1.3 只指定约束名: 约束名和索引名都变成指定的约束名
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.1.4 只指定索引名: 约束名不是列名, 由系统生成, 索引名是指定名
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY index_name(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.1.5 不指定约束名和索引名(多个外键) (建议)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20) UNIQUE);
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  teacher_name VARCHAR(20),
  FOREIGN KEY(teacher_id) REFERENCES teacher(id),
  FOREIGN KEY(teacher_name) REFERENCES teacher(name)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.2 添加
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student ADD FOREIGN KEY(teacher_id) REFERENCES teacher(id);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.3 删除
# 7.3.1 删除外键, 索引不会自动删除 (建议)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP FOREIGN KEY constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.3.2 删除索引, 报错
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX constraint_name;

# 7.3.3 删除约束名, 和删除外键相同, 索引不会自动删除
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  CONSTRAINT constraint_name FOREIGN KEY(teacher_id) REFERENCES teacher(id)
);
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP CONSTRAINT constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;
ALTER  TABLE student DROP INDEX constraint_name;
DESC   student;
SELECT * FROM information_schema.table_constraints WHERE table_name = 'student';
SHOW   INDEX FROM student;

# 7.4 约束等级
# 7.4.1 CASCADE --- 父表更新时, 同步更新子表
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE CASCADE
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 2 WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;

# 7.4.2 CASCADE --- 父表删除时, 同步删除子表对应的行
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON DELETE CASCADE
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;

# 7.4.3 SET NULL --- 父表更新时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE SET NULL
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 2 WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;

# 7.4.4 SET NULL --- 父表删除时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON DELETE SET NULL
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;

# 7.4.5 NO ACTION (同 RESTRICT) --- 父表更新时, 如果子表对应字段已使用, 报错, 未使用时, 更新成功 (默认)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE NO ACTION
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO teacher VALUES(2, "丘处机");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 11 WHERE id = 1; # 报错
DELETE FROM student WHERE teacher_id = 1;
UPDATE teacher SET id = 11 WHERE id = 1; # 成功
UPDATE teacher SET id = 22 WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;

# 7.4.6 NO ACTION (同 RESTRICT) --- 父表删除时, 如果子表对应字段已使用, 报错, 未使用时, 删除成功 (默认)
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON DELETE NO ACTION
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO teacher VALUES(2, "丘处机");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 1; # 报错
DELETE FROM student WHERE teacher_id = 1;
DELETE FROM teacher WHERE id = 1; # 成功
DELETE FROM teacher WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;

# 7.4.7 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
DROP   TABLE IF EXISTS student;
DROP   TABLE IF EXISTS teacher;
CREATE TABLE teacher(id INT PRIMARY KEY, name VARCHAR(20));
CREATE TABLE student(
  id INT PRIMARY KEY,
  name VARCHAR(20) UNIQUE,
  teacher_id INT,
  FOREIGN KEY(teacher_id) REFERENCES teacher(id) ON UPDATE CASCADE ON DELETE RESTRICT
);
INSERT INTO teacher VALUES(1, "马钰");
INSERT INTO teacher VALUES(2, "丘处机");
INSERT INTO student VALUES(1, "郭靖", 1);
SELECT * FROM teacher;
SELECT * FROM student;
UPDATE teacher SET id = 11 WHERE id = 1;
SELECT * FROM teacher;
SELECT * FROM student;
DELETE FROM teacher WHERE id = 11; # 报错
DELETE FROM student WHERE teacher_id = 11;
DELETE FROM teacher WHERE id = 11; # 成功
DELETE FROM teacher WHERE id = 2;
SELECT * FROM teacher;
SELECT * FROM student;
```

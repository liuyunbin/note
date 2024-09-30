
## 常用数据类型
```
int --------------- 整形 ------------------- 4     个字节
bigint unsigned --- 大整形 ----------------- 8     个字节
decimal(m,d) ------ 定点数 ----------------- m + 2 个字节
datetime ---------- 日期和时间 ------------- 8     个字节
timestamp --------- 时间戳 ----------------- 4     个字节
char(m) ----------- 固定长度, m 为字符数 ---
varchar(m) -------- 可变长度, m 为字符数 ---
```

## 约束
```
show databases;
create database if not exists test;

# 1. NOT NULL
* 只能作用在单列上

# 1.1 创建
use    test;
drop   table if exists student;
create table student(id int not null);
desc   student;

# 1.2 添加
use    test;
drop   table if exists student;
create table student(id int);
desc   student;
alter  table student modify id int not null;
desc   student;

# 1.3 删除
use    test;
drop   table if exists student;
create table student(id int not null);
desc   student;
alter  table student modify id int;
desc   student;

# 2. UNIQUE --- 唯一键
* 会创建唯一索引
* 可以存储 NULL
* 存储的值不能相同, 但 NULL 可以多个
* 默认的索引名和约束名是第一列的列名
* 可以存在多个唯一键
* 可以对多列定义一个唯一键
* 只能通过删除唯一索引的方式删除唯一键
* 删除唯一约束名报错

# 2.1 创建
# 2.1.1 列级约束(单列): 约束名和索引名默认和列名相同 (推荐)
use    test;
drop   table if exists student;
create table student(id int unique, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.1.2 列级约束(多列): 约束名和索引名默认和列名相同 (推荐)
use    test;
drop   table if exists student;
create table student(id int unique, name varchar(20) unique);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.1.3 表级约束(单列), 不指定约束名和索引名: 约束名和索引名都是列名
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), unique(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.1.4 表级约束(单列), 同时指定约束名和索引名: 约束名没意义, 约束名和索引名都变成索引名
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name unique index_name(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.1.5  表级约束(单列), 只指定约束名: 约束名和索引名都变成约束名
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name unique(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.1.6 表级约束(单列), 只指定索引名: 约束名和索引名都变成索引名
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), unique index_name(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.1.7 表级约束(多列): 约束名和索引名默认和第一列的列名相同 (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), unique(id, name));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.2 添加
# 2.2.1 可以添加表级或列级唯一约束 (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student add unique (id);
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.2.2 只能添加列级唯一约束
use    test;
drop   table if exists student;
create table student(id int, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student modify id int unique;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.3 删除
# 2.3.1 删除唯一索引: 使用 ALTER
use    test;
drop   table if exists student;
create table student(id int unique, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop index id;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.3.2 删除唯一索引: 使用 DROP
use    test;
drop   table if exists student;
create table student(id int unique, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
drop   index id on student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 2.3.3 删除唯一约束名: 报错
use    test;
drop   table if exists student;
create table student(id int unique, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop constraints id;

# 2.4 可以存储 NULL, NULL 可以重复, 其他不行
use    test;
drop   table if exists student;
create table student(id int unique, name varchar(20) unique);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
insert into student values(NULL, "bob");
select * from student;
insert into student values(NULL, "tom");
select * from student;
insert into student values(NULL, "bob"); # 报错

# 3 PRIMARY KEY --- 主键
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

# 3.1 创建
# 3.1.1 列级约束(单列): 约束名和索引名为 PRIMARY (推荐)
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.1.2 列级约束(多列): 报错
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20) primary key);

# 3.1.3 表级约束, 不指定约束名和索引名: 约束名和索引名都为 PRIMARY (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), primary key(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.1.4 表级约束, 指定约束名和索引名: 约束名和索引名都为 PRIMARY
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name primary key index_name(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.1.5 表级约束, 只指定约束名: 约束名和索引名都为 PRIMARY
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name primary key(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.1.6 表级约束, 只指定索引名: 约束名和索引名都为 PRIMARY
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), primary key index_name(id));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.1.7 表级约束(同时在多列指定): 约束名和索引名都为 PRIMARY (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), primary key(id, name));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.2 添加
# 3.2.1 可以添加表级或列级主键约束 (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student add primary key(id);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.2.2 只能添加列级主键约束
use    test;
drop   table if exists student;
create table student(id int, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student modify id int primary key;
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.3 删除
# 3.3.1 删除主键: 会删除对应的索引, 但非空约束还在
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop primary key;
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 3.3.2 删除主键约束名: 报错
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop constraints primary;

# 3.3.3 删除主键索引: 报错
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop index primary;

# 3.4 不可以存储 NULL, 不可以重复
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
insert into student values(NULL, "bob"); # 报错
insert into student values(1,    "tom");
select * from student;
insert into student values(1,    "bob"); # 报错

# 4. FOREIGN KEY --- 外键
* 会自动创建索引
* 从表的外键必须是主表的主键或唯一键
* 先创建主表, 再创建从表
* 先删除从表或外键, 再删除主表
* 默认外键的外键名不是列名, 默认的索引名是列名
* 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
* 通过删除外键约束名或外键可以删除外键, 不能通过删除外键索引来删除外键
* 删除外键后, 外键索引还存在

# 4.1 创建
# 4.1.1 不指定约束名和索引名: 约束名不是列名, 由系统生成, 索引名是列名 (建议)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.1.2 同时指定约束名和索引名: 索引名没意义, 约束名和索引名都变成指定的约束名
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  constraint constraint_name foreign key index_name(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.1.3 只指定约束名: 约束名和索引名都变成指定的约束名
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  constraint constraint_name foreign key(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.1.4 只指定索引名: 约束名不是列名, 由系统生成, 索引名是指定名
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key index_name(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.1.5 不指定约束名和索引名(多列) (建议)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20) unique);
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  teacher_name varchar(20),
  foreign key(teacher_id) references teacher(id),
  foreign key(teacher_name) references teacher(name)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.2 添加
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student add foreign key(teacher_id) references teacher(id);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.3 删除
# 4.3.1 删除外键, 索引不会自动删除 (建议)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  constraint constraint_name foreign key(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop foreign key constraint_name;
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop index constraint_name;
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.3.2 删除索引, 报错
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  constraint constraint_name foreign key(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop index constraint_name;

# 4.3.3 删除约束名, 和删除外键相同, 索引不会自动删除
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  constraint constraint_name foreign key(teacher_id) references teacher(id)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop constraint constraint_name;
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;
alter  table student drop index constraint_name;
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
show   index from student;

# 4.4 约束等级
# 4.4.1 cascade --- 父表更新时, 同步更新子表
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on update cascade
);
insert into teacher values(1, "马钰");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
update teacher set id = 2 where id = 1;
select * from teacher;
select * from student;

# 4.4.2 cascade --- 父表删除时, 同步删除子表对应的行
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on delete cascade
);
insert into teacher values(1, "马钰");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
delete from teacher where id = 1;
select * from teacher;
select * from student;

# 4.4.3 SET NULL --- 父表更新时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on update set null
);
insert into teacher values(1, "马钰");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
update teacher set id = 2 where id = 1;
select * from teacher;
select * from student;

# 4.4.4 SET NULL --- 父表删除时, 同步更新子表对应字段为 NULL (该列不能为 NOT NULL)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on delete set null
);
insert into teacher values(1, "马钰");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
delete from teacher where id = 1;
select * from teacher;
select * from student;

# 4.4.5 NO ACTION (同 RESTRICT) --- 父表更新时, 如果子表对应字段已使用, 报错, 未使用时, 更新成功 (默认)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on update no action
);
insert into teacher values(1, "马钰");
insert into teacher values(2, "丘处机");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
update teacher set id = 11 where id = 1; # 报错
update teacher set id = 22 where id = 2;
select * from teacher;
select * from student;

# 4.4.6 NO ACTION (同 RESTRICT) --- 父表删除时, 如果子表对应字段已使用, 报错, 未使用时, 删除成功 (默认)
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on delete no action
);
insert into teacher values(1, "马钰");
insert into teacher values(2, "丘处机");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
delete from teacher where id = 1; # 报错
delete from teacher where id = 2;
select * from teacher;
select * from student;

# 4.4.7 建议: ON UPDATE CASCADE ON DELETE RESTRICT -- 同步更新, 删除严格
use    test;
drop   table if exists student;
drop   table if exists teacher;
create table teacher(id int primary key, name varchar(20));
create table student(
  id int primary key,
  name varchar(20) unique,
  teacher_id int,
  foreign key(teacher_id) references teacher(id) on update cascade on delete restrict
);
insert into teacher values(1, "马钰");
insert into teacher values(2, "丘处机");
insert into student values(1, "郭靖", 1);
select * from teacher;
select * from student;
update teacher set id = 11 where id = 1;
select * from teacher;
select * from student;
delete from teacher where id = 11; # 报错
delete from teacher where id = 2;
select * from teacher;
select * from student;

# 5. AUTO_INCREMENT --- 自动递增
* 只能作用于整形
* 最多只有一列
* 列必须是主键或唯一键

# 5.1 创建
# 5.1.1 单列 (整形): 作用于主键
use    test;
drop   table if exists student;
create table student(id int primary key auto_increment);
desc   student;

# 5.1.2 单列 (整形): 作用于唯一键, 非空, 无主键时, 该列会变成主键
use    test;
drop   table if exists student;
create table student(id int unique auto_increment, idd int);
desc   student;

# 5.1.3 单列 (整形): 作用于唯一键, 非空, 有其他主键时, 该列还是唯一键
use    test;
drop   table if exists student;
create table student(id int unique auto_increment, idd int primary key );
desc   student;

# 5.1.4 单列 (非整形) -- 报错
use    test;
drop   table if exists student;
create table student(id int, name varchar(20) unique auto_increment);

# 5.1.5 多列 (整形) -- 报错
use    test;
drop   table if exists student;
create table student(id int unique auto_increment, idd int unique auto_increment);

# 5.1.6 单列 -- 默认初始值为 1
use    test;
drop   table if exists student;
create table student(id int primary key auto_increment, name varchar(20));
insert into student(name) values('bob');
select * from student;

# 5.1.7 单列 -- 设置初始值为 10
use    test;
drop   table if exists student;
create table student(id int primary key auto_increment, name varchar(20)) auto_increment = 10;
insert into student(name) values('bob');
select * from student;

# 5.2 添加
# 5.2.1 初始值为 1
use    test;
drop   table if exists student;
create table student(id int primary key, name varchar(20));
desc   student;
alter  table student modify id int auto_increment;
desc   student;
insert into student(name) values('bob');
select * from student;

# 5.2.2 设置初始值为 10
use    test;
drop   table if exists student;
create table student(id int primary key auto_increment, name varchar(20));
desc   student;
alter  table student auto_increment = 10;
desc   student;
insert into student(name) values('bob');
select * from student;

# 5.3 删除
use    test;
drop   table if exists student;
create table student(id int primary key auto_increment);
desc   student;
alter  table student modify id int;
desc   student;

# 6. check --- 检查
* 只能通过删除 check 约束名来删除 check 约束
* 可以使 check 不生效

# 6.1 创建
# 6.1.1 列级约束: 约束名由系统生成 (推荐)
use    test;
drop   table if exists student;
create table student(id int check(id > 0), name varchar(20));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';

# 6.1.2 表级约束(单列): 未指定约束名, 约束名由系统生成 (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), check(id > 0));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';

# 6.1.2 表级约束(单列): 指定约束名
use    test;
drop   table if exists student;
create table student(
  id int,
  name varchar(20),
  constraint constraint_name check(id > 0)
);
desc   student;
select * from information_schema.table_constraints where table_name = 'student';

# 6.1.3 表级约束(多列): (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), check(id > 0 and length(name) > 1));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';

# 6.2 添加
# 6.2.1 可以添加列级和表级约束 (推荐)
use    test;
drop   table if exists student;
create table student(id int);
select * from information_schema.table_constraints where table_name = 'student';
alter  table student add check(id > 0);
select * from information_schema.table_constraints where table_name = 'student';

# 6.2.2 只能添加列级约束
use    test;
drop   table if exists student;
create table student(id int);
select * from information_schema.table_constraints where table_name = 'student';
alter  table student modify id int check(id > 0);
select * from information_schema.table_constraints where table_name = 'student';

# 6.3 删除
# 6.3.1 删除 check 约束名
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name check(id > 0));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
alter  table student drop check constraint_name;
select * from information_schema.table_constraints where table_name = 'student';

# 6.3.2 通过 alter ... modify ... ------ 没用
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name check(id > 0));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
alter  table student modify id int;
select * from information_schema.table_constraints where table_name = 'student';

# 6.4 使 check 不生效
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), constraint constraint_name check(id > 0));
desc   student;
select * from information_schema.table_constraints where table_name = 'student';
insert into student values(-1, 'bob'); # 报错
alter  table student alter check constraint_name not enforced;
select * from information_schema.table_constraints where table_name = 'student';
insert into student values(-1, 'bob');
select * from student;

# 7. DEFAULT --- 默认值
# 7.1 创建
use    test;
drop   table if exists student;
create table student(id int, name varchar(20) default 'tom');
desc   student;

# 7.2 添加
# 7.2.1 方式一
use    test;
drop   table if exists student;
create table student(id int, name varchar(20));
desc   student;
alter  table student alter name set default 'tom';
desc   student;

# 7.2.2 方式二 (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20));
desc   student;
alter  table student modify name varchar(20) default 'tom';
desc   student;

# 7.3 删除
# 7.3.1 方式一
use    test;
drop   table if exists student;
create table student(id int, name varchar(20) default 'tom');
desc   student;
alter  table student alter name drop default;
desc   student;

# 7.3.2 方式二 (推荐)
use    test;
drop   table if exists student;
create table student(id int, name varchar(20) default 'tom');
desc   student;
alter  table student modify name varchar(20);
desc   student;

# 8. INDEX --- 索引
* 类型
  * 普通索引 ----- 无任何限制
  * 唯一索引 ----- 和 unique 对应
  * 主键索引 ----- 和 primary key 对应
  * 全文索引 ----- 很少使用
  * 空间索引 ----- 很少使用
* 范围
  * 单列索引 -----
  * 多列索引 ----- 最左前缀原则 -- 最常用的放最左边
* 实现
  * 聚簇索引 -----
  * 非聚簇索引 ---
* 新特性
  * 降序索引 ----- 如果查找是降序的话, 可以提高效率 --- ASC DESC
  * 隐藏索引 ----- 便于观察删除索引的影响 --- INVISIBLE VISIBLE
* 适合建索引
    * where group by order by 中频繁使用
    * 区分度大的列
    * DISTINCT 列
    * 很少变化的列
* 不适合建索引
    * 表很小
* 联合索引好于多个单列索引
* 删除无用或冗余的索引

# 8.1 创建
# 8.1.1 单列: 不指定索引名称: 索引名称默认是列名
use    test;
drop   table if exists student;
create table student(id int, index(id));
show   index from student;

# 8.1.2 单列: 指定索引名称
use    test;
drop   table if exists student;
create table student(id int, index index_name(id));
show   index from student;

# 8.1.3 多列: 不指定索引名称: 索引名称默认是第一个列名
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), index(id, name));
show   index from student;

# 8.1.4 多列: 指定索引名称
use    test;
drop   table if exists student;
create table student(id int, name varchar(20), index index_name(id, name));
show   index from student;

# 8.1.5 降序索引
use    test;
drop   table if exists student;
create table student(id int, index(id));
show   index from student;
drop   table if exists student;
create table student(id int, index(id desc));
show   index from student;

# 8.1.6 不可见索引
use    test;
drop   table if exists student;
create table student(id int, index(id) visible);
show   index from student;
drop   table if exists student;
create table student(id int, index(id) invisible);
show   index from student;

# 8.2 添加 或 修改
# 8.2.1 使用 create index 添加
use    test;
drop   table if exists student;
create table student(id int);
show   index from student;
create index index_name on student(id);
show   index from student;

# 8.2.2 使用 alter 添加
use    test;
drop   table if exists student;
create table student(id int);
show   index from student;
alter  table student add index index_name(id);
show   index from student;

# 8.2.3 设置索引是否可见
use    test;
drop   table if exists student;
create table student(id int, index index_name(id));
show   index from student;
alter  table student alter index index_name invisible;
show   index from student;
alter  table student alter index index_name visible;
show   index from student;

# 8.3 删除
# 8.3.1 使用 drop
use    test;
drop   table if exists student;
create table student(id int, index index_name(id));
show   index from student;
drop   index index_name on student;
show   index from student;

# 8.3.2 使用 alter
use    test;
drop   table if exists student;
create table student(id int, index index_name(id));
show   index from student;
alter  table student drop index index_name;
show   index from student;

# 8.4 重命名索引
use    test;
drop   table if exists student;
create table student(id int, index index_name(id));
show   index from student;
alter  table student rename index index_name to new_index_name;
show   index from student;
```

## 库
```
# 1. 为什么使用数据库
* 数据持久化
* 效率

# 2. 常用命令
show   databases;            # 查看所有的数据库
show   create database test; # 查看数据库的创建信息, 比如编码
create database test;        # 创建数据库
alter  database test ...;    # 修改数据库
drop   database test;        # 删除数据库
use    test;                 # 选择数据库
```

## 表
```
show databases;
create database if not exists test;

# 1. 创建和删除表
use    test;
drop   table if exists student;
drop   table if exists student_test;
create table student (id int);
create table student_test as select * from student;
show   tables;
show   create table student;
show   create table student_test;
desc   student;
desc   student_test;

# 2. 增加列
use    test;
drop   table if exists student;
create table student (id int);
desc   student;
alter  table student add before_id varchar(20) first;
alter  table student add  after_id varchar(20) after id;
alter  table student add      name varchar(20);
desc   student;

# 3. 删除列
use    test;
drop   table if exists student;
create table student (id int, name varchar(20));
desc   student;
alter  table student drop name;
desc   student;

# 4. 修改列属性
use    test;
drop   table if exists student;
create table student (id int, name varchar(20));
desc   student;
alter  table student modify id bigint;
desc   student;
alter  table student modify name varchar(20) first;
desc   student;
alter  table student modify name varchar(20) after id;
desc   student;

# 5. 重命名列名
use    test;
drop   table if exists student;
create table student (id int, name varchar(20));
desc   student;
alter  table student rename column name to new_name;
desc   student;
alter  table student change id new_id bigint;
desc   student;

# 6. 设置列不可见
use    test;
drop   table if exists student;
create table student (id int, name varchar(20));
desc   student;
alter  table student alter name set invisible;
desc   student;
alter  table student alter name set visible;
desc   student;

# 7. 重命名表
use    test;
drop   table if exists student;
drop   table if exists student_test;
create table student (id int, name varchar(20));
show   tables;
alter  table student rename to student_test;
show   tables;
rename table student_test to student;
show   tables;

# 8. 删除表内数据(清空表)
use    test;
drop   table if exists student;
set    autocommit = false;      # 取消自动提交
create table student (id int, name varchar(20));
insert into  student values(1, "马钰");
insert into  student values(2, "丘处机");
insert into  student values(3, "王处一");
commit;                  # 提交
select * from student;
delete from   student;
select * from student;
rollback;                # 回滚
select * from  student;
truncate table student;  # 清空表 --- 不能回滚
rollback;                # 回滚
select * from  student;

# 9. 插入数据(单个)
use    test;
drop   table if exists student;
create table student (id int, name varchar(20));
insert into  student values(1, "马钰");
insert into  student values(2, "丘处机");
insert into  student values(3, "王处一");
select * from student;



insert into table_name(...) select ...;  # 插入数据
insert ignore into ...                   # 插入数据 忽略重复的

replace into ...                         # 插入数据 如果重复, 删旧的, 加新的
update table_name set ... where ...      # 更新




## SELECT
```
书写: SELECT -> DISTINCT -> FROM -> WHERE -> GROUP BY -> HAVING -> ORDER BY -> LIMIT
执行: FROM -> WHERE -> GROUP BY(此后可以使用聚合) -> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT

distinct -------------- 放在所有列开头
between ... and ... --- 范围 [ ]
isnull ---------------- 是 null
is null --------------- 是 null
is not null ----------- 不是 null
in -------------------- 属于集合
not in ---------------- 不属于集合
like ------------------ % 任意多个字符, _ 任意一个字符
regexp ---------------- 正则表达式
rlike ----------------- 正则表达式

order by ... asc | desc

inner join ... on ... # 内连接
left  join ... on ... # 左连接
right join ... on ... # 右连接

limit 偏移量, 行数
limit 行数

union --------- # 合并, 去重 ---- 效率低
union all ----- # 合并, 不去重 -- 效率高
```


```


表和视图
```


## 视图
* 相当于是一张虚拟表
* 不存储数据
* 一般只用于查询
* 简化操作, 便于操作
* 提高数据安全
* 底层变化时, 必须更新视图

create [or replace] view view_name as select ... # 创建或更新视图
alter view view_name as select ...    # 更新视图
drop view                    view_name;               # 删除视图

```

## 存储过程和函数
```
## 存储过程
* 简化操作, 减少网上传输的数据
* 没返回值
* 提高复用, 减少操作失误
* 提前编译, 效率高
* 不好调试
* 分表时, 不好维护


## 函数
和存储过程的区别
* 有返回值

## 变量

## if

# 存储函数和存储过程
* characteristics
    * LANGUAGE SQL ----------- 语言 SQL
    * DETERMINISTIC ---------- 相同的输入会得到相同的输出
    * NOT DETERMINISTIC ------ 相同的输入不一定会得到相同的输出 ---- 默认值
    * NO SQL ----------------- 不包含任何 SQL 语句
    * CONTAINS SQL ----------- 不包含任何 SQL 语句, 但是并不包含读写数据的SQL语句 ---- 默认
    * READS SQL DATA --------- 包含读数据的 SQL 语句
    * MODIFIES SQL DATA ------ 包含写数据的 SQL 语句
    * SQL SECURITY DEFINER --- 只允许创建者或定义者使用 --- 默认
    * SQL SECURITY INVOKER --- 允许所有人使用

DELIMITER $
create procedure procedure_name(...) ------- IN, OUT, INOUT
    [characteristics ...]
    begin
        ...
    end $
DELIMITER ;

call procedure_name(...)

DELIMITER $
create function function_name(...) --- 只能是 IN
    [characteristics ...]
    return ...
    begin
        ...
    end $
DELIMITER ;

select procedure_name(...)


drop function            function_name;               # 删除函数
drop procedure          procedure_name;               # 删除存储过程
```

## 游标
```

```

## 触发器
```
create trigger trigger_name [before|after]  [insert|update|delete]   on table_name for each row ...


drop trigger   table_name.trigger_name;               # 删除触发器
```


DDL: create drop alter rename truncate

DDL(数据定义语言): CREATE DROP   ALTER
DML(数据操作语言): INSERT UPDATE SELECT DELETE
DCL(数据控制语言): GRANT  REVOKE COMMIT ROLLBACK SAVEPOINT

source ...

round -- 不一定是直观 的四舍五入

DB: 数据库 Database
DBMS: 数据库管理系统 Database Management System
SQL: 结构化查询语言 Structured Query Language

RDBMS: 关系型数据库
* 将复杂的关系转化为二元的关系, 表格
* 表之间通过外键来关联

E-R(entity-relationship 实体-联系)模型中有三个主要概念是 实体集 属性集 联系集
一个实体集(class)   == 一个表(table)
一个实体(instance)  == 一行(row), 一条记录(record)
一个属性(attribute) == 一列(column), 一个字段(field)

表之间的关系
一对一: 用的不多, 可以使用一张表, 但会冗余
一对多
多对多
自引用

单引号: 字符串 日期
双引号: 别名
反引用: 与关键字冲突时, 使用

库名 表名 表别名 字段名 字段别名 小写, 其他建议大写

## 其他
mysql -D <库名> -h <域名> -u <用户名> -p<密码>  # 登录
myqsl -D testdb < 1.sql                         # 从文件导入
mysqldump database_name table_name > 1.sql      # 导出到文件
select .. into outfile .. fields terminated by ',' optionally enclosed by '"' lines terminated by '\n' from ..
                                                # 保存数据到文件

mysql_install_db --user=mysql --ldata=/var/lib/mysql # 添加用户 mysql 使mysqld 可以使用 systemctl 启动

set global max_allowed_packet=64*1024*1024 # 设置插入的上限

current_timestamp()
current_date()
now()


## 参考资源
* https://dev.mysql.com/doc/refman/9.0/en/resetting-permissions.html ----------- 重置 root 密码

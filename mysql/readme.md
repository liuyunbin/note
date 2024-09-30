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

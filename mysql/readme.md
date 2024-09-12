
# 安装及初始化
```
apt install mariadb-server           # 安装
                                     #
systemctl enable     mariadb.service # 开机自动启动
systemctl start      mariadb.service # 启动服务
systemctl is-active  mariadb.service # 查看是否已启动
systemctl is-enabled mariadb.service # 查看是否开机自动启动
                                     #
mariadb-secure-installation          # 禁止 root 远程登录
                                     # 删除匿名用户
                                     # 删除测试数据库
```

# 库
```
show   databases;       # 查看数据库
use    testdb;          # 使用数据库
create database testdb; # 创建数据库
alter  database testdb; # 修改数据库
drop   database testdb; # 删除数据库
```

## 数据类型
int --------------- 整形
bigint unsigned --- 大整形
decimal(m,d) ------ 定点数
datetime ---------- 日期和时间
timestamp --------- 时间戳
char(m) ----------- 固定长度
varchar(m) -------- 可变长度, 5.0 之后 m 为字符数

## 创建表


alter table tbl_name add primary key (col_list);
alter table tbl_name add unique index_name (col_list);
alter table tbl_name add index index_name (col_list);
alter table tbl_name add fulltext index_name (col_list);

drop index index_name on tbl_name;
alter table tbl_name drop index index_name；
alter table tbl_name drop primary key;

create unique index uniq_idx_firstname on actor (`first_name`);
create        index idx_lastname on actor (`last_name`);


insert into ...
insert ignore into ...
replace into ...

show databases;
show tables;
show tables from ...;

show create database ...
show create table ...

create database ...
create table ...()

drop database ...
drop table ...

use ...;

source ...

DISTINCT ----- 放在所有列开头

NULL 参与的所有结果都为 NULL

desc ...

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

外键: 是主键
主表
从表

DDL(数据定义语言): CREATE DROP   ALTER
DML(数据操作语言): INSERT UPDATE SELECT DELETE
DCL(数据控制语言): GRANT  REVOKE COMMIT ROLLBACK SAVEPOINT

单引号: 字符串 日期
双引号: 别名
反引用: 与关键字冲突时, 使用

库名 表名 表别名 字段名 字段别名 小写, 其他建议大写

## 为什么使用数据库
* 数据持久化
* 效率

## 配置 utf8mb4 -- 最新版本不需要修改了
1. 查看字符集
    mysql -e "show variables like 'character%';"
2. 修改字符集为 utf8mb4
   * 查找配置文件: mysqld --help --verbose 2> /dev/null | grep -A1 'Default options'
   * 在相关文件内添加以下内容:
       [client]
       default-character-set = utf8mb4

       [mysql]
       default-character-set = utf8mb4

       [mysqld]
       character-set-server = utf8mb4
       collation-server = utf8mb4_unicode_ci
    * 停止 mysql 服务: pkill mysql
    * 启动: mysqld --user=root &

## 用户管理
create user 'tom'@'localhost' identified by 'password' --------------------------- 创建用户

grant all privileges on *.* to 'tom'@'localhost' identified with grant option ---- 授权
grant select         on *.* to 'tom'@'localhost' identified with grant option ---- 授权

flush privileges; ---------------------------------------------------------------- 刷新权限

revoke process on *.* from 'tom'@'localhost'; ------------------------------------ 回收权限

drop user 'tom'@'localhost'; ----------------------------------------------------- 删除用户

show grants; --------------------------------------------------------------------- 查看权限

## 修改密码
set password for 'tom'@'localhost' = password('123');
mysqladmin -u root -p password “123456”;

## 忘记密码
sudo systemctl stop mariadb
sudo mysqld_safe --skip-grant-tables & ---- 跳过权限判断启动
mysql -u root
set password for 'root'@'localhost' = password('123'); --- 修改密码
flush privileges;
sudo systemctl start mariadb

## 其他
mysql -D <库名> -h <域名> -u <用户名> -p<密码>  # 登录
myqsl -D testdb < 1.sql                         # 从文件导入
mysqldump database_name table_name > 1.sql      # 导出到文件
select .. into outfile .. fields terminated by ',' optionally enclosed by '"' lines terminated by '\n' from ..
                                                # 保存数据到文件

mysql_install_db --user=mysql --ldata=/var/lib/mysql # 添加用户 mysql 使mysqld 可以使用 systemctl 启动

set global max_allowed_packet=64*1024*1024 # 设置插入的上限

select user,host,passwd from mysql.user; # 查看用户 密码


## 表
show tables;             # 查看表
desc ......;             # 查看表结构
create   table 表名称(); # 创建表
alter table 表名称 add       列名称 列属性 after 旧名称; # 修改表, 增加列
alter table 表名称 change  旧列名称 新列名称 列属性;     # 修改表, 修改列名称
alter table 表名称 modify    列名称 列属性;              # 修改表, 修改列属性
alter table 表名称 drop      列名称;                     # 修改表, 删除列
alter table 表名称 rename  新表名称;                     # 修改表, 重命名表名
drop     table 表名称;   # 删除表
delete   table 表名称;   # 删除表内数据, 表结构保留
truncate table 表名称;   # 删除表内数据, 表结构保留

auto_increment

primary key: 主键, 唯一, 不能为空, 只能有一个主键, 加索引
unique  index: 唯一, 能有多个, 加索引
foreign index: 外键, 加索引
        index: 普通索引

## SELECT
书写: SELECT -> DISTINCT -> FROM -> WHERE -> GROUP BY -> HAVING -> ORDER BY -> LIMIT
执行: FROM -> WHERE -> GROUP BY(此后可以使用聚合) -> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT


LEAST
GREATEST
BETWEEN ... AND ... --- [ ]
ISNULL
IS NULL
IS NOT NULL
IN
NOT IN
LIKE
REGEXP
RLIKE


ORDER BY ... ASC | DESC
LIMIT 偏移量, 行数
LIMIT 行数

update table_name set ...=... where ...

insert into table_name () values ();

delete from table_name where ...

and or not
in, not in,
is null, is not null, <=>(相等或都为null)
between ... and ...,
like(%表示任意字符),
regexp, rlike

order by .... DESC

UNION --------- # 合并, 去重
UNION ALL ----- # 合并, 不去重

INNER JOIN ... ON ... # 内连接
LEFT  JOIN ... ON ... # 左连接
RIGHT JOIN ... ON ... # 右连接

NATURAL JOIN ... # 所有相同字段等值连接
JION ... USING(...) ... # 指定字段等值连接

current_timestamp()
current_date()
now()

trigger 触发器

create index 索引名称  表名(字段名称)            # 创建索引
alter table 表名称 add  index 索引名称(字段名称) # 创建索引
drop index 索引名称 on 表名                      # 删除索引



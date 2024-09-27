
## 安装及初始化
```
# 1. 安装软件
sudo apt install mysql-server

# 2. 基本安全设置
#   * 配置 root 使用 Linux root 用户认证
#   * 禁止 root 远程登录
#   * 删除匿名用户
#   * 删除测试数据库
mysql_secure_installation

# 3. 启动 MySQL 并设置为开机自动启动
sudo systemctl list-unit-files | grep mysql   # 1. 查看 mysql 服务的名称
sudo systemctl list-unit-files | grep mariadb #
sudo systemctl is-active  mysql.service       # 2. 查看是否已启动
sudo systemctl start      mysql.service       # 3. 启动服务
sudo systemctl is-active  mysql.service       # 4. 再次查看是否已启动
sudo systemctl is-enabled mysql.service       # 5. 查看是否开机自动启动
sudo systemctl enable     mysql.service       # 6. 设置开机自动启动
sudo systemctl is-enabled mysql.service       # 7. 再次查看是否开机自动启动

# 3. 修改编码为 utf8mb4 --- 8.0 及以后的版本不需要修改了
show variables like 'character%';         # 1. 查看编码和字符集
show variables like 'collation%';         #
mysql --help | grep -A1 'Default options' # 2. 查看 MySQL 的配置文件
default-character-set = utf8mb4           # 3. 修改配置文件中的编码
sudo systemctl restart mysql              # 4. 重启 MySQL
show variables like 'character%';         # 5. 再次查看编码和字符集
show variables like 'collation%';         #

# 4. 开启防火墙
sudo firewall-cmd --list-services                 # 1. 查看目前开启的服务
sudo firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
sudo firewall-cmd --reload                        # 3. 重新加载防火墙
sudo firewall-cmd --list-services                 # 4. 再次查看目前开启的服务

# 5. 允许远程访问
ss -tal | grep mysql                      # 1. 查看 MySQL 是否允许远程访问
mysql --help | grep -A1 'Default options' # 2. 查看 MySQL 的配置文件
bind-address           = 127.0.0.1        # 3. 注释掉对应的配置
mysqlx-bind-address    = 127.0.0.1        #
sudo systemctl restart mysql              # 4. 重启 MySQL
ss -tal | grep mysql                      # 5. 再次查看 MySQL 是否允许远程访问
```

## 修改密码
```
set password                   =password('123456');  # 修改当前用户密码 -- 旧版本 5.7
set password for user@hostname =password('123456');  # 修改其他用户密码 -- 旧版本 5.7
set password                   =new_password;        # 修改当前用户密码 -- 新版本 8.0 -- 不建议使用
set password for user@hostname=new_password;         # 修改其他用户密码 -- 新版本 8.0 -- 不建议使用
alter user user@hostname identified by new_password; # 修改其他用户密码 -- 新版本 8.0
alter user user@hostname identified with caching_sha2_password by 'new_password';
                                                     # 修改其他用户密码, 客户端为 8.0
alter user user@hostname identified with mysql_native_password by 'new_password';
                                                     # 修改其他用户密码, 客户端为 5.7
```

## 忘记 root 密码 或 恢复 root 权限-- MariaDB 5.5.68 --- centos 7
```
sudo systemctl list-unit-files | grep mariadb # 1. 查看 mariadb 服务的名称
sudo systemctl stop mariadb.service;          # 2. 停止服务器
sudo mysqld_safe --skip-grant-tables &        # 3. 启动服务器, 跳过密码和权限判断
mysql -u root;                                # 4. 连接 MySQL, 不需要密码
flush privileges;                             # 5. 刷新权限, 使得权限管理生效
set password for 'root'@'localhost' = password('root');
                                              # 6. 设置新密码(可选)
grant all privileges on *.* to 'root'@'localhost' with grant option;
                                              # 7. 赋予权限(可选)
mysqladmin -u root -p shutdown;               # 8. 使用新密码停止服务
sudo systemctl start mariadb.service;         # 9. 启动服务
```

## 忘记 root 密码 或 恢复 root 权限----- MySQL 8.0.39 --- ubuntu 22.04
```
sudo systemctl list-unit-files | grep mysql   # 1. 查看 mysql 服务的名称
sudo systemctl stop   mysql.service;          # 2. 停止服务器
sudo mkdir -p /var/run/mysqld                 # 3. 新建目录
sudo chown mysql:mysql /var/run/mysqld        # 4. 改变归属
sudo mysqld_safe --skip-grant-tables &        # 5. 启动服务器, 跳过密码和权限判断
mysql -u root;                                # 6. 连接 MySQL, 不需要密码
flush privileges;                             # 7. 刷新权限, 使得权限管理生效
alter user 'root'@'localhost' identified by 'root';
                                              # 8. 设置新密码(可选)
grant all privileges on *.* to 'root'@'localhost' with grant option;
                                              # 9. 赋予权限(可选)
mysqladmin -u root -p shutdown;               # 10. 使用新密码停止服务
sudo systemctl start   mysql.service;         # 11. 启动服务
```










DDL: create drop alter rename truncate


## SQL
```
use   database_name;                 # 使用数据库

show  databases;                     # 查看所有的数据库
show  tables;                        # 查看所有的表
show  tables from     database_name; # 查看某一库中所有的表
show  index  from        table_name; # 查看索引
show  create database database_name; # 查看数据库的创建信息, 比如编码
show  create table       table_name; # 查看表的创建信息
show variables like 'character%';         # 查看编码
show variables like 'collation%';         # 查看字符集
show variables like 'validate_password%'; # 查看密码要求

create database database_name;           # 创建数据库
create table tbl (...);                  # 创建表
create table tbl (id int  [constraint]); # 创建表, 包含约束
create table tbl (id int, [constraint symbol] unique(id));      # 创建表, 包含唯一键
create table tbl (id int, [constraint symbol] primary key(id)); # 创建表, 包含主键
create table tbl (id int, [constraint symbol] foreign key(id) references 主表名(被参考字段)
                                                  on update cascade on delete restrict
                                         # 创建表, 包含外键, 同步更新, 删除严格
create table tbl(id int, [unique] index index_name(id)); # 创建索引

create          table table_name as select ...;      # 创建表
create [unique] index index_name on table_name(...); # 添加索引

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

# 触发器
create trigger trigger_name [before|after]  [insert|update|delete]   on table_name for each row ...

create [or replace] view view_name as select ... # 创建或更新视图

desc table_name;                       # 查看表结构

alter table tbl_name add col_name col_def [first | after col_name];          # 增加列
alter table tbl_name add index index_name(id);                               # 添加普通索引
alter table tbl_name add [constraint symbol] primary key(id);                # 添加主键
alter table tbl_name add [constraint symbol] unique      index_name(id);     # 添加唯一键 或 唯一索引
alter table tbl_name add [constraint symbol] foreign key index_name(id) ...; # 添加外键
alter table tbl_name add [constraint symbol] check(id > 0) [[NOT] ENFORCED]; # 添加 check

alter table tbl_name drop   check      symbol;          # 删除 check 约束
alter table tbl_name drop   constraint symbol;          # 删除 主键 外键 唯一键 约束
alter table tbl_name drop   col_name;                   # 删除列
alter table tbl_name drop   index index_name;           # 删除索引
alter table tbl_name drop   primary key;                # 删除主键约束
alter table tbl_name drop   foreign key key_name;       # 删除外键约束
alter table tbl_name drop   check       check_name;     # 删除 check
alter table tbl_name drop   index index_name;           # 删除索引

alter table tbl_name alter check      symbol [[NOT] ENFORCED];   # 设置 check 约束 是否生效
alter table tbl_name alter constraint symbol [[NOT] ENFORCED];   # 设置 主键 外键 唯一键 约束 是否生效

alter table tbl_name alter col_name drop default;              # 删除默认值
alter table tbl_name alter col_name set  default ...;          # 设置默认值
alter table tbl_name alter col_name set {visible | invisible}; # 设置列是否可见

alter table tbl_name alter index index_name {visible | invisible}; # 设置索引是否可见

alter table tbl_name modify                  col_name col_def [first | after col_name]; # 修改列属性
alter table tbl_name change old_col_name new_col_name col_def [first | after col_name]; # 修改列名称

alter table tbl_name order by col_name,...;             # 列排序

alter table tbl_name rename column   old_col_name to   new_col_name;  # 重命名列
alter table tbl_name rename index  old_index_name to new_index_name;  # 重命名索引
alter table tbl_name rename                       to   new_tbl_name;  # 重命名表

alter view view_name as select ...    # 更新视图

alter database database_name ...;   # 修改数据库

drop database            database_name;               # 删除数据库
drop table                  table_name;               # 删除表
drop view                    view_name;               # 删除视图
drop function            function_name;               # 删除函数
drop procedure          procedure_name;               # 删除存储过程
drop trigger   table_name.trigger_name;               # 删除触发器
drop index                  index_name on table_name; # 删除索引

rename table old_table to new_table; # 重命名表

truncate table table_name; # 清空表 --- 不能回滚






create user user@hostname identified by 'password'; # 3. 创建用户


drop user user@hostname;                     #  删除用户

drop role role@hostname;                     # 删除角色

insert into table_name(...) values(...); # 插入数据
insert into table_name(...) select ...;  # 插入数据
insert ignore into ...                   # 插入数据 忽略重复的

replace into ...                         # 插入数据 如果重复, 删旧的, 加新的
update table_name set ... where ...      # 更新
delete from table_name where ...         # 删除
set autocommit = false; # 取消自动提交
rollback;               # 回滚

select user,host,plugin from mysql.user;            # 1. 查看用户及其加密插件



## 权限使用原则
* 只赋予满足要求的最小权限
* 限制用户登录的主机, root 只允许本机登录
* 定期删除不用的用户
* 权限可以叠加

## 权限刷新
* 服务端
    * GRANT, REVOKE, SET PASSWORD, RENAME USER --- 不需要刷新权限
    * INSERT, UPDATE, or DELETE -------------------- 需要刷新权限 FLUSH PRIVILEGES --- 不推荐
* 客户端
    * 表和列的权限, 下一次请求的时候就会生效
    * 库的权限, 客户端使用 use ... 的时候才生效, 但客户端可能缓存库名称
    * 密码那些不会影响到已连接的客户端
* 修改权限后, 客户端最好重连

## 直接授予和回收用户权限
```
show privileges;                                           # 查看所有权限
grant select,insert,delete,update on *.* to user@hostname; # 授予用户 增删改查 权限
grant all privileges              on *.* to user@hostname; # 授予用户全部权限, 除 grant
grant all privileges              on *.* to user@hostname with grant option;
                                                           # 授予用全部权限
show grants;                                               # 查看当前用户权限
show grants for user@hostname;                             # 查看其他用户权限
revoke 权限 on *.* from user@hostname;                     # 回收用户权限
```

## 创建和删除角色
create role role@hostname;                                  # 创建角色

## 授予和回收角色权限
```
show privileges;                                           # 查看所有权限
grant select,insert,delete,update on *.* to role@hostname; # 授予角色 增删改查 权限
grant all privileges              on *.* to role@hostname; # 授予角色全部权限, 除 grant
grant all privileges              on *.* to role@hostname with grant option;
                                                           # 授予角色全部权限
show grants for role@hostname;                             # 查看角色权限
revoke 权限 on *.* from role@hostname;                     # 回收角色权限
```

## 通过角色赋予和删除用户权限
```
grant  role to   user;                                      # 1. 将角色赋予用户
set default role all to user@hostname;                      # 2. 激活权限
revoke role from user;                                      # 3. 撤销用户角色
```

####  UNIQUE --- 唯一键
```
* 可以存储 NULL
* 整个表中的数据是唯一的, 但 NULL 可以多个
* 可以有多个 unique
* 一个 unique 可以对多个列创建
* 会自动创建唯一索引
* 默认约束名为第一个列名
```
#### PRIMARY KEY --- 主键
* 唯一键 + 非空 + 最多只有一个

#### AUTO_INCREMENT --- 自动递增
* 一般用在主键
* 最多有一列
* 作用于整形

#### FOREIGN KEY --- 外键
* 从表的外键必须是主表的主键或唯一键
* 先创建主表, 再创建从表
* 先删除从表或外键, 再删除主表
* 外键可以多个
* 外键会自动创建索引
* 默认的外键约束名不是列名

#### check --- 检查
#### DEFAULT --- 默认值
#### INDEX --- 索引
```
* 普通索引 ----- 无任何限制
* 唯一索引 ----- 和 unique 对应
* 主键索引 ----- 和 primary key 对应
* 全文索引 ----- 很少使用
* 空间索引 ----- 很少使用
* 单列索引 -----
* 多列索引 ----- 最左前缀原则
* 聚簇索引 -----
* 非聚簇索引 ---
* 降序索引 ----- 如果查找是降序的话, 可以提高效率 --- ASC DESC
* 隐藏索引 ----- 便于观察删除索引的影响 --- INVISIBLE VISIBLE
* 适合建索引
    * where group by order by 中频繁使用
    * 区分度大的列
    * DISTINCT 列
    * 很少变化的列
* 不适合建索引
    * 表很小
    * 列无序
* 联合索引多余多个单列索引
* 删除无用或冗余的索引
```

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

## 视图
```
* 相当于是一张虚拟表
* 不存储数据
* 一般只用于查询
* 简化操作, 便于操作
* 提高数据安全
* 底层变化时, 必须更新视图
```


## 存储过程
```
* 简化操作, 减少网上传输的数据
* 没返回值
* 提高复用, 减少操作失误
* 提前编译, 效率高
* 不好调试
* 分表时, 不好维护
```

## 函数
```
和存储过程的区别
* 有返回值
```



## 变量

## if

## 为什么使用数据库
* 数据持久化
* 效率


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

trigger 触发器

## 参考资源
* https://dev.mysql.com/doc/refman/9.0/en/account-management-statements.html --- 用户和角色
* https://dev.mysql.com/doc/refman/9.0/en/privilege-changes.html --------------- 权限刷新
* https://dev.mysql.com/doc/refman/9.0/en/resetting-permissions.html ----------- 重置 root 密码


## 常用类型
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
####  NOT NULL
```

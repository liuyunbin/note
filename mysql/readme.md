

## 联系子查询

## 库
```
# 1. 为什么使用数据库
* 数据持久化
* 效率

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


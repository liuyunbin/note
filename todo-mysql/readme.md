
## 1. 为什么使用数据库
* 数据持久化
* 效率

DROP TABLE IF EXISTS tb1;

CREATE TABLE tb1 (
    t1 INT PRIMARY KEY,
    t2 INT UNIQUE,
    t3 INT,
    t4 int,
    INDEX(t3)
);


INSERT INTO tb1 VALUES(5,   5,  5,  5);
INSERT INTO tb1 VALUES(10, 10, 10, 10);
INSERT INTO tb1 VALUES(15, 15, 15, 15);
INSERT INTO tb1 VALUES(20, 20, 20, 20);

SELECT * FROM tb1;

SELECT t1 FROM tb1 WHERE t2 = 7 FOR 

select *             from information_schema.table_constraints;  # 查看约束
select *             from information_schema.innodb_trx;         # 查看事务信息

select *             from information_schema.processlist;        # 目前的连接信息

select *             from sys.innodb_lock_waits where locked_table=`'test'.'t'`

SELECT *             FROM performance_schema.data_locks

 SELECT blocking_pid from  sys.schema_table_lock_waits;          # 获取造成阻塞的 ID

SELECT @@innodb_deadlock_detect; # 开启死锁的自动回滚
SELECT @@innodb_lock_wait_timeout ; # 死锁等待的超时时间

SELECT @@innodb_max_dirty_pages_pct; # 脏页的最大比例
SELECT @@innodb_io_capacity;         # 磁盘IOPS 



SELECT @@Innodb_buffer_pool_pages_dirty;
SELECT @@Innodb_buffer_pool_pages_total;

CREATE table student (id INT);

LOCK TABLE student WRITE;

show processlist;      # 查看目前的连接


DESC   student;
SHOW   INDEX FROM student;

show processlist;      # 查看目前的连接
SELECT @@wait_timeout; # 查看自动断开的时间. 默认是 8 小时
mysql_reset_connection # 重置连接资源, 使之和刚建立连接时一样

transaction_isolation

select * from information_schema.innodb_trx where TIME_TO_SEC(timediff(now(),trx_started))>60




## 2. 重建表
```
alter table A engine=InnoDB --- 重建表
analyze  table t -------------- 对表的索引信息做重新统计
optimize table t -------------- 上述两者的和

重建表
1. 添加表写锁, 扫描主键, 存入临时文件 --- 此时不能修改数据
2. 表写锁退化为表读锁, 后续对表的增删改都写入日志文件 --- 此时可以修改数据
3. 拷贝数据 -- 最耗时的操作
4. 读取日志文件, 作用于临时文件, 完成表重建
```

SELECT count(*) FROM tb1;
SELECT count(*) FROM tb2;

SHOW TABLEs;

SELECT * FROM teacher;

CREATE TABLE teacher (
id INT PRIMARY key,
name VARCHAR(20) UNIQUE
);

alter table teacher drop primary key;
alter table teacher add primary key(id);


连接器 ->  分析器 -> 优化器 -> 执行器

1. 连接器
show processlist;      # 查看目前的连接
SELECT @@wait_timeout; # 查看自动断开的时间. 默认是 8 小时
mysql_reset_connection # 重置连接资源, 使之和刚建立连接时一样


2. 分析器
3. 优化器
4. 执行器


RTO（恢复目标时间）

select VARIABLE_VALUE into @a from global_status where VARIABLE_NAME = 'Innodb_buffer_pool_pages_dirty';
select VARIABLE_VALUE into @b from global_status where VARIABLE_NAME = 'Innodb_buffer_pool_pages_total';
select @a/@b;

SELECT * FROM sys.schema_table_lock_waits;

SELECT @@innodb_flush_neighbors 

SELECT @@innodb_change_buffer_max_size 

SELECT @@sort_buffer_size/1024/1024

SELECT @@max_connections 

SELECT @@binlog_group_commit_sync_delay 

SELECT @@binlog_row_image 

SELECT @@MAX_EXECUTION_TIME ;

# 查询事务持续时间高于 60s 的事务
select * from information_schema.innodb_trx where TIME_TO_SEC(timediff(now(),trx_started))>60
```

## 1. 为什么 MySQL 的默认隔离级别是 RR
```
* 排除 READ-UNCOMMITTED, 会导致脏读
* 排除 SERIALIZABLE, 效率太低
* 排除 READ-COMMITTED
    * BINLOG 格式为 STATEMENT 时, 可能导致主从数据不一致
    * 旧版本的 BINLOG 的格式为 STATEMENT
    * 修改 隔离级别为 READ-COMMITTED 时, 要将 BINLOG 的格式修改为 ROW
```


## 核心业务主键设计
1. 自增ID
    不是全局唯一的
    容易被猜测, 安全性不高
    mysql 8.0 前, 服务器重启后, 自增 id 可能回溯
    
2. UUID()
    全局唯一
    
    
SELECT UUID(); 
UUID = 时间+UUID版本（16字节）- 时钟序列（4字节） - MAC地址（12字节）
36 

SET @uuid = UUID();
SELECT @uuid,
       uuid_to_bin(@uuid), -- 去掉 - (16字节)
       uuid_to_bin(@uuid,TRUE) -- 去掉 - 且 递增 (16字节)
       
       ;


DDL: create drop alter rename truncate

DDL(数据定义语言): CREATE DROP   ALTER
DML(数据操作语言): INSERT UPDATE SELECT DELETE
DCL(数据控制语言): GRANT  REVOKE COMMIT ROLLBACK SAVEPOINT

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
```

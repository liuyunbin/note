
## 事务的基础特性: ACID
```
* 原子性
* 一致性: 执行事务后的状态合法
* 隔离型: 事务之间没影响
* 持久性: 持久保存到文件 重做日志 和 回滚日志


### 2.2 隐式事务
SHOW VARIABLES LIKE 'autocommit'; #  查看
SHOW VARIABLES LIKE 'innodb_flush_log_at_trx_commit'; #  查看

innodb_flush_log_at_trx_commit
```

## 简单测试
```
DROP TABLE if EXISTS student;
CREATE TABLE student(name varchar(20) UNIQUE);

# 1. 使用 BEGIN 开启事务
TRUNCATE student;
BEGIN;                              # 开启事务
INSERT INTO student VALUES('张三'); # 不提交
COMMIT;                             # 提交事务
SELECT * FROM student;

# 2. 使用 START TRANSACTION 开启事务 (读写事务)
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student VALUES('张三'); # 不提交
COMMIT;                             # 提交事务
SELECT * FROM student;

# 3. 测试普通回滚
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '李四';  # 不提交
INSERT INTO student SELECT '李四';  # 报错
ROLLBACK;                           # 回滚空
SELECT * FROM student;

# 4. 测试: 设置回滚点 SAVEPOINT
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '张三';  # 不提交
SAVEPOINT p1;
INSERT INTO student SELECT '李四';  # 不提交
INSERT INTO student SELECT '李四';  # 报错
ROLLBACK TO p1;                     # 回滚到张三成功
SELECT * FROM student;
RELEASE SAVEPOINT p1;               # 删除保存点

# 5. 测试:  completion_type = 0 (默认)
后续的命令, 如果 autocommit = ON, 会自动提交, 否则, 需要手动提交 COMMIT

SET SESSION autocommit      = ON;
SET SESSION completion_type = 0;
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '张三';  # 不提交
COMMIT;                             # 提交
INSERT INTO student SELECT '李四';  # 提交, autocommit = ON
ROLLBACK;                           # 回滚
SELECT * FROM student;

SET SESSION autocommit      = OFF;
SET SESSION completion_type = 0;
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '张三';  # 不提交
COMMIT;                             # 提交
INSERT INTO student SELECT '李四';  # 不提交 autocommit = OFF
ROLLBACK;                           # 回滚
SELECT * FROM student;

# 6. 测试:  completion_type = 1
开启链式事务, 后续的命令需要手动提交 COMMIT

SET SESSION autocommit      = ON;
SET SESSION completion_type = 1;
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '张三';  # 不提交
COMMIT;                             # 提交
INSERT INTO student SELECT '李四';  # 不提交
ROLLBACK;                           # 回滚
SELECT * FROM student;

SET SESSION autocommit      = OFF;
SET SESSION completion_type = 1;
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '张三';  # 不提交
COMMIT;                             # 提交
INSERT INTO student SELECT '李四';  # 不提交
ROLLBACK;                           # 回滚
SELECT * FROM student;

# 7. 测试:  completion_type = 2
* 提交后, 与服务器断开
* 使用终端测试

SET SESSION completion_type = 2;
TRUNCATE student;
START TRANSACTION;                  # 开启事务
INSERT INTO student SELECT '张三';  # 不提交
COMMIT;                             # 提交, 然后断开连接
SELECT * FROM student;              # 报错

# 8. 使用 START TRANSACTION 开启事务 (读写事务)
TRUNCATE student;
START TRANSACTION READ WRITE;       # 开启事务
INSERT INTO student VALUES('张三'); # 不提交
COMMIT;                             # 提交事务
SELECT * FROM student;

# 9. 使用 START TRANSACTION 开启事务 (只读事务) -- 对于其他事务能访问的资源
TRUNCATE student;
START TRANSACTION READ ONLY;        # 开启事务
INSERT INTO student VALUES('张三'); # 报错
COMMIT;                             # 提交事务
SELECT * FROM student;



START TRANSACTION READ ONLY, WITH CONSISTENT SNAPSHOT; # 启动一致性读
START TRANSACTION READ WRITE, WITH CONSISTENT SNAPSHOT; # 启动一致性读

```


## 3. 事务隔离级别
* 脏写
    1. 事务一更新数据, 还未提交
    2. 事务二更新相同数据, 提交
    3. 事务一提交, 此时, 事务一覆盖了事务二的数据
* 脏读
    1. 事务一更新数据, 还未提交
    2. 事务二读取到更新过的数据
    3. 事务一回滚  
* 不可重复读
    1. 事务一读取数据
    2. 会话B 更新相关数据
    3. 事务一再次读取数据, 数据不一致
* 幻读
    1. 事务一读取数据
    2. 会话B 插入一些数据
    3. 事务一再次读取数据, 比之前多 


### 3.3 SQL中的四种隔离级别

按照严重性来排一下序
脏写 > 脏读 > 不可重复读 > 幻读

* READ UNCOMMITTED: 所有事务都可以看到其他未提交事务的执行结果, 不能避免脏读、不可重复读、幻读 
* READ COMMITTED: 一个事务只能看见已经提交事务所做的改变, 可以避免脏读，但不可重复读、幻读问题仍然存在
* REPEATABLE READ: 可重复读
    * 事务A在读到一条数据之后，此时事务B对该数据进行了修改并提交
    * 那么事务A再读该数据，读到的还是原来的内容
    * 可以避免脏读、不可重复读，但幻读问题仍然存在
    * 这是 MySQL 的默认隔离级别。 
* SERIALIZABLE: 可串行化，确保事务可以从一个表中读取相同的行
    * 在这个事务持续期间，禁止其他事务对该表执行插入、更新和删除操作
    * 所有的并发问题都可以避免，但性能十分低下。能避免脏读、不可重复读和幻读

SHOW VARIABLES LIKE 'transaction_isolation'; # 查看隔离级别

SET GLOBAL  TRANSACTION_ISOLATION = SERIALIZABLE;  # 设置隔离级别
SET SESSION TRANSACTION_ISOLATION = SERIALIZABLE;  # 设置隔离级别


# 第14章_MySQL事务日志

事务有4种特性：原子性、一致性、隔离性和持久性。那么事务的四种特性到底是基于什么机制实现呢？

* 事务的隔离性由 `锁机制` 实现。
* 而事务的原子性、一致性和持久性由事务的 redo 日志和undo 日志来保证。
  + REDO LOG 称为 `重做日志 `，提供再写入操作，恢复提交事务修改的页操作，用来保证事务的持久性。
  + UNDO LOG 称为 `回滚日志` ，回滚行记录到某个特定版本，用来保证事务的原子性、一致性。

# redo log
* 为了实现持久性和效率的平衡
* 落盘: 内存中的文件存入磁盘
* 事务完成前, 把所有修改的页落盘 (修改量和落盘量不成比例, 随机 IO 效率低)
* 事务完成前, 只把修改的内容的日志落盘 (顺序 IO 效率高, 占用空间小, 降低刷盘的频率)
* Write-Ahead Logging: 先写日志(此时, 可以完成事务了), 再写磁盘(定期写入即可)
* 事务执行过程中就会 redo log
* innodb_flush_log_at_trx_commit = 0
    * 提交事务成功, 保证将 redo log 写入 MySQL 缓冲区
    * 主线程 刷新缓冲区, 每一秒落盘
    * MySQL 崩溃了, 可能会丢失数据
    * 操作系统崩溃了, 可能丢失数据
* innodb_flush_log_at_trx_commit = 1 (默认)
    * 提交事务成功, 保证将 redo log 写入内核缓冲区, 同时刷盘
    * MySQL 崩溃了, 不会丢失数据
    * 操作系统崩溃了, 不会丢失数据
* innodb_flush_log_at_trx_commit = 2 
    * 提交事务成功, 保证将 redo log 写入内核缓冲区
    * 主线程每一秒落盘
    * MySQL 崩溃了, 不会丢失数据
    * 操作系统崩溃了, 可能丢失数据

## undo log
    * 记录的是 逻辑操作
    * 比如 执行 INSERT 操作, 就记录一条 DELETE 操作
    * 用于事务的回滚

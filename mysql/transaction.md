
## 0. 总结
```
* READ UNCOMMITTED --- 很少使用
    * 可以看到其他未提交事务的执行结果
    * 默认不能避免脏读, 不可重复读、幻读 
    * 使用锁可以解决 脏读 不可重复读  -- 记录锁
    * 不能解决幻读 -- 没有间隙锁和临键锁
* READ COMMITTED
    * 只能看见已经提交事务所做的改变
    * 默认可以避免脏读，但不可重复读、幻读问题仍然存在
    * 使用锁可以解决 脏读 不可重复读  -- 记录锁
    * 不能解决幻读  -- 没有间隙锁和临键锁
* REPEATABLE READ: 可重复读
    * 默认可以避免脏读、不可重复读，但幻读问题仍然存在
    * 解决不可重复读使用的是快照读, 加锁可以使用当前读 -- 记录锁
    * 加锁可以处理幻读  -- 间隙锁和临键锁
    * 这是 MySQL 的默认隔离级别
* SERIALIZABLE: 串行化 --- 很少使用 
    * 相当于对 SELECT 语句增加 共享锁
    * 性能十分低下
    * 能避免脏读、不可重复读和幻读 -- 记录锁 间隙锁和临键锁
* 严重性: 脏写 > 脏读 > 不可重复读 > 幻读

SELECT  @@GLOBAL.TRANSACTION_ISOLATION; # 查看隔离级别
SELECT @@SESSION.TRANSACTION_ISOLATION; # 查看隔离级别

SET GLOBAL TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; # 设置隔离级别
SET GLOBAL TRANSACTION_ISOLATION = 'READ-COMMITTED';   # 设置隔离级别
SET GLOBAL TRANSACTION_ISOLATION = 'REPEATABLE-READ';  # 设置隔离级别
SET GLOBAL TRANSACTION_ISOLATION = 'SERIALIZABLE';     # 设置隔离级别

SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; # 设置隔离级别
SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED';   # 设置隔离级别
SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ';  # 设置隔离级别
SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';     # 设置隔离级别

DROP TABLE if EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name varchar(20));
```

## 1. 脏写
* 事务一更新数据, 还未提交
* 事务二更新数据, 提交
* 事务一回滚, 此时, 事务一更新的数据丢失了
* 实际情况不可能发生, 会等待

| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
|                                        | START TRANSACTION;     | 开启事务                  |
|                                        | SELECT * FROM student; | 张三                      |
|         | UPDATE student SET name = '张七' WHERE id = 1;        | 更新数据   -- 实际会等待  |
|                                        | SELECT * FROM student; | 张七                      |
|                                        | COMMIT;                | 提交事务                  |
| ROLLBACK;                              |                        | 回滚, 丢失了 会话B 的修改 |
| COMMIT;                                |                        | 提交事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |

## 2. 脏读
* 事务一更新数据, 还未提交
* 事务二读取到更新过的数据
* 事务一回滚, 此时, 事务二读取的数据就是脏的

### 2.1 测试 READ UNCOMMITTED
#### 2.1.1 触发 (未提交的数据)
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; |       | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
|                                        | SELECT * FROM student; | 张六 --- 脏数据           |
| ROLLBACK;                              |                        | 回滚                      |
| COMMIT;                                |                        | 提交事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |

#### 2.1.2 加锁解决 (当前读)
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; |       | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student FOR UPDATE;      |                        | 张三 -- 获取排他锁        |
|                                        | SELECT * FROM student FOR SHARE; | 等待            |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
| ROLLBACK;                              |                        | 回滚                      |
| COMMIT;                                |                        | 提交事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student FOR SHARE; | 解锁后, 取到张三 |

### 2.2 测试 READ COMMITTED -- 不会发生脏读 (当前读)
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED'; |         | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED';   | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
|                                        | SELECT * FROM student; | 张三 --- 修改前的数据     |
| ROLLBACK;                              |                        | 回滚                      |
| COMMIT;                                |                        | 提交事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |

### 2.3 测试 REPEATABLE-READ -- 不会发生脏读 (快照读)
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |        | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ';  | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三 --- 建立快照         |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
|                                        | SELECT * FROM student; | 张三 --- 使用快照         |
| ROLLBACK;                              |                        | 回滚                      |
| COMMIT;                                |                        | 提交事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |

### 2.4 测试 SERIALIZABLE -- 不会发生脏读 (当前读)
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';    |        | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';     | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student;                 |                        | 张三   --- 加共享锁       |
|                                        | SELECT * FROM student; | 张三                      |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据 --- 加排他锁     |
| SELECT * FROM student;                 |                        | 张六                      |
|                                        | SELECT * FROM student; | 张三                      |
| ROLLBACK;                              |                        | 回滚                      |
| COMMIT;                                |                        | 提交事务                  |
| SELECT * FROM student;                 |                        | 张三                      |
|                                        | SELECT * FROM student; | 张三                      |

## 3. 不可重复读 ---  由于 其他事务更新或删除 导致 -- 使用记录锁可解决
* 事务一读取数据
* 事务二更新相关数据
* 事务一再次读取数据, 数据不一致

### 3.1 测试 READ UNCOMMITTED -- 会发生不可重复读 -- 使用当前读
#### 3.1.1 触发
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; |       | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 1;    |                        | 张三                      |
|                                        | START TRANSACTION;     | 开启事务                  |
|                           | SELECT * FROM student WHERE id = 1; | 张三                      |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
| COMMIT;                                |                        | 提交事务                  |
|                           | SELECT * FROM student WHERE id = 1; | 张六 --- 不可重复读       |
|                                        | COMMIT;                | 提交事务                  |

#### 3.1.2 解决
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; |       | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 1;    |                        | 张三                      |
|                                        | START TRANSACTION;     | 开启事务                  |
|                 | SELECT * FROM student WHERE id = 1 FOR SHARE; | 张三  -- 加共享锁         |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 阻塞                      |
|                           | SELECT * FROM student WHERE id = 1; | 还是张三                  |
|                                        | COMMIT;                | 提交事务, 释放锁          |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 获取锁, 解阻塞            |
| SELECT * FROM student;                 |                        | 张六                      |
| COMMIT;                                |                        | 提交事务                  |


### 3.2 测试 READ COMMITTED -- 会发生不可重复读 -- 使用当前读 (可使用加锁解决)
```
同 READ-UNCOMMITTED
```

### 3.3 测试 REPEATABLE-READ -- 不会发生不可重复读 -- 使用快照读 (加锁可以使用当前读)
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |        | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ';  | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 1;    |                        | 张三                      |
|                                        | START TRANSACTION;     | 开启事务                  |
|                           | SELECT * FROM student WHERE id = 1; | 张三  --- 建立快照        |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 更新数据                  |
| SELECT * FROM student;                 |                        | 张六                      |
| COMMIT;                                |                        | 提交事务                  |
|                           | SELECT * FROM student WHERE id = 1; | 张三  --- 使用快照        |
|                                        | COMMIT;                | 提交事务                  |

### 3.4 测试 SERIALIZABLE -- 不会发生不可重复读 -- 使用当前读 -- 相当于加锁
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE'; |           | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';     | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 1;    |                        | 张三  --- 加共享锁        |
|                                        | START TRANSACTION;     | 开启事务                  |
|                           | SELECT * FROM student WHERE id = 1; | 张三  --- 加共享锁        |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 阻塞                      |
|                           | SELECT * FROM student WHERE id = 1; | 张三                      |
|                                        | COMMIT;                | 提交事务, 释放共享锁      |
| UPDATE student SET name = '张六' WHERE id = 1; |                | 获取锁                    |
| SELECT * FROM student;                 |                        | 张六                      |
| COMMIT;                                |                        | 提交事务                  |

## 4. 幻读 ---  由于 其他事务插入 导致 -- 使用间隔锁和临键锁可解决
* 事务一读取数据, 发现该行不存在
* 会话B 插入数据
* 事务一尝试插入数据, 失败

### 4.1 测试 READ UNCOMMITTED -- 会发生幻读 -- 使用当前读
```
和下一条的 READ COMMITTED 情况相同 
```

### 4.2 测试 READ COMMITTED -- 会发生幻读 -- 使用当前读 --- 无法解决
#### 4.2.1 触发
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED'; |         | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED';   | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 2;    |                        | 无数据                    |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四                  |
| INSERT INTO student VALUES(2, '李四'); |                        | 插入李四 --- 失败         |
| COMMIT;                                |                        | 提交事务                  |

#### 4.2.2 尝试解决 -- 无法解决 -- 因为 没有间隙锁和临键锁
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED'; |         | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED';   | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 2 FOR UPDATE; |                | 无数据                    |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四                  |
| INSERT INTO student VALUES(2, '李四'); |                        | 插入李四 --- 失败         |
| COMMIT;                                |                        | 提交事务                  |

### 4.3 测试 REPEATABLE-READ -- 会发生幻读 -- 使用当前读 --- 可以解决
#### 4.3.1 触发
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |        | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ';  | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 2;    |                        | 无数据                    |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四                  |
| INSERT INTO student VALUES(2, '李四'); |                        | 插入李四 --- 失败         |
| COMMIT;                                |                        | 提交事务                  |

#### 4.3.2 尝试解决 -- 可以解决 -- 使用间隙锁和临键锁
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |        | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ';  | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 2 FOR UPDATE; |                | 无数据 -- 插入间隙锁      |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四 --- 阻塞         |
| INSERT INTO student VALUES(2, '李四'); |                        | 插入李四 --- 成功         |
| COMMIT;                                |                        | 提交事务                  |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四 -- 解阻塞 -- 然后失败 |

### 4.4 测试 SERIALIZABLE -- 不会发生幻读 -- 使用当前读 -- 相当于加锁
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE'; |           | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';     | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| SELECT * FROM student WHERE id = 2;    |                        | 无数据 -- 插入间隙锁      |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四 --- 阻塞         |
| INSERT INTO student VALUES(2, '李四'); |                        | 插入李四 --- 成功         |
| COMMIT;                                |                        | 提交事务                  |
|                        | INSERT INTO student VALUES(2, '李四'); | 插入李四 -- 解阻塞 -- 然后失败 |

## 5. 测试 SERIALIZABLE 的串行化
| 会话A                                  | 会话B                  | 说明                      |
| -------------------------------------- | ---------------------- | --------                  |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE'; |           | 设置隔离级别              |
|       | SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';     | 设置隔离级别              |
| TRUNCATE student;                      |                        | 清空表                    |
| INSERT INTO student VALUES(1, '张三'); |                        | 插入数据                  |
| START TRANSACTION;                     |                        | 开启事务                  |
| UPDATE student SET name= '李四'  WHERE id = 1; |                | 张三 -> 李四 --- 记录锁   |
| SELECT * FROM student WHERE id = 1;    |                        |                           |
|                           | SELECT * FROM student WHERE id = 1; | 张三                      |
|                                        | START TRANSACTION;     | 开启事务                  |
|                           | SELECT * FROM student WHERE id = 1; | 阻塞                      |
| COMMIT;                                |                        | 提交事务, 释放锁          |
|                           | SELECT * FROM student WHERE id = 1; | 解阻塞 -- 李四            |
|                                        | COMMIT;                | 提交事务                  |

## 1. 全局锁
```
为全库做逻辑备份
Flush tables with read lock
* 全库只读
* 支持所有存储引擎
* 意外断开后自动解锁 

mysqldump –single-transaction
* 不影响现有业务
* 只支持 InnoDB
 
set global readonly=true
* 全库只读
* 该变量可能用于判断主备机器
* 意外断开后不会自动设置变量 
```

## 2. 表锁
```
* 颗粒度大
* 容易锁争用
* 死锁概率低

# 8.1 共享锁(S)和排他锁(X) --- 断开后自动解锁
DROP TABLE if EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name varchar(20));
LOCK TABLES student READ;          # 锁定共享锁
SHOW OPEN TABLES where In_use > 0; # 查看表上的锁
UNLOCK TABLES;                     # 解锁当前加锁的表
SHOW OPEN TABLES where In_use > 0; # 查看表上的锁
LOCK TABLES student WRITE;         # 锁定排他锁
SHOW OPEN TABLES where In_use > 0; # 查看表上的锁
UNLOCK TABLES;                     # 解锁当前加锁的表
SHOW OPEN TABLES where In_use > 0; # 查看表上的锁

# 8.2 意向锁(IX, IS)
* 有事务持有或计划持有该表上的锁
* 由服务器自动维护
* 为了简化锁的判断
* 意向锁之间相互兼容
* 可以和行锁共存

# 8.3 自增锁: AUTO-INC锁
innodb_autoinc_lock_mode = 0
    传统锁定模式
    每条 INSERT 都获取表锁
innodb_autoinc_lock_mode = 1
    连续锁定模式
    每条 INSERT 都获取表锁
    插入条数确定的情况下, 计算自增的值, 提前释放表锁
    8.0 前的默认值
innodb_autoinc_lock_mode = 2
    交错锁定模式
    MySQL 8.0 开始的默认值
    所有数据保证唯一,  单调递增
    给定语句插入的行生成的值可能不是连续的
    插入条数确定的情况下, 计算自增的值, 这种情况一定是连续的
    
# 8.4 元数据锁: MDL锁
* 增删改查加 MDL 读锁
* 表结构变化时, 增加 MDL 写锁
* 修改表结构时, 可以增加一个超时时间

```

## 0. 行锁-总结
```
DROP TABLE if EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name varchar(20));

* 颗粒度小
* 不容易锁争用
* 可能会死锁
* 增删改会自动添加 排他锁
* 使用索引锁定, 否则会是表锁定

IX -------------- 表级意向独占锁
IS -------------- 表级意向共享锁 
S,REC_NOT_GAP --- 共享型记录锁
X,REC_NOT_GAP --- 独占型记录锁
S,GAP ----------- 共享型间隙锁
X,GAP ----------- 独占型间隙锁
X --------------- 临键锁
INSERT_INTENTION -- 插入意向锁
```

## 1. 记录锁
```
* 针对表中存在的记录
* 区分: 共享锁和排他锁
```

### 1.1 测试 共享型记录锁可以叠加
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 10 FOR SHARE;         |                 | 添加 共享记录锁和表意向共享锁 |
| SELECT * FROM performance_schema.data_locks\G          |                      | 共享记录锁和表意向共享锁 |
|                                                        | START TRANSACTION;     | 开启事务               |
|       | SELECT * FROM student WHERE id = 10 FOR SHARE;                   | 添加 共享记录锁和表意向共享锁 |
| SELECT * FROM performance_schema.data_locks\G          |                      | 共享记录锁和表意向共享锁 |
| COMMIT;                                                |                        | 提交事务               |
|                                                        | COMMIT;                | 提交事务               |


### 1.2 测试记录锁是写优先的
| 会话A                                                  | 会话B    | 会话C       | 说明                   |
| ------------------------------------------------------ | -------- | ----------| ------  |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | | 设置变量               |
|                        | | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | | 插入数据               |
| SELECT * FROM student;                                 |                        | | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | | 无锁                   |
| SELECT * FROM student WHERE id = 10 FOR SHARE;         |               | | 添加 共享记录锁和表意向共享锁 |
| SELECT * FROM performance_schema.data_locks\G          |               | |      共享记录锁和表意向共享锁 |
|       | START TRANSACTION;                               | | 开启事务               |
|       | SELECT * FROM student WHERE id = 10 FOR UPDATE;  | | 添加 排他记录锁和表意向排他锁 -- 阻塞 |
| SELECT * FROM performance_schema.data_locks\G  | | | 共享记录锁和表意向共享锁 排他记录锁和表意向排他锁 |
|         | | START TRANSACTION;                               | 开启事务               |
|         | | SELECT * FROM student WHERE id = 10 FOR SHARE;   | 添加 共享记录锁和表意向共享锁 -- 阻塞 |
| SELECT * FROM performance_schema.data_locks\G  | | | 共享记录锁和表意向共享锁 排他记录锁和表意向排他锁 |
| COMMIT;                                                |              | | 提交, 释放锁       |
|                                                        | COMMIT;      | | 获取锁成功, 提交, 释放锁 |
|                                                         |  | COMMIT;    | 获取锁成功, 提交         |

### 1.3 测试同一事务, 开启共享锁的情况下修改数据 -- 可以, 只要其他事务不持有相关锁就可以
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 10 FOR SHARE;         |                 | 添加 共享记录锁和表意向共享锁 |
| SELECT * FROM performance_schema.data_locks\G          |                      | 共享记录锁和表意向共享锁 |
| UPDATE student SET name = '张六' WHERE id = 10;        |                 | 添加 排他记录锁和表意向排他锁 |
| SELECT * FROM performance_schema.data_locks\G      | | 共享记录锁和表意向共享锁 排他记录锁和表意向排他锁 |
| COMMIT;                                                |                        | 提交事务               |

### 1.4 测试同一事务, 开启共享锁的情况下修改数据 -- 其他事务持有相关锁就不可以
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 10 FOR SHARE;         |                 | 添加 共享记录锁和表意向共享锁 |
| SELECT * FROM performance_schema.data_locks\G          |                      | 共享记录锁和表意向共享锁 |
|                                                        | START TRANSACTION;     | 开启事务               |
|       | SELECT * FROM student WHERE id = 10 FOR SHARE;                   | 添加 共享记录锁和表意向共享锁 |
| SELECT * FROM performance_schema.data_locks\G          |                      | 共享记录锁和表意向共享锁 |
| UPDATE student SET name = '张六' WHERE id = 10;        |                 | 阻塞 |
|      | SELECT * FROM performance_schema.data_locks\G | 共享记录锁和表意向共享锁 排他记录锁和表意向排他锁 |
|                                                        | COMMIT;                | 提交事务, 释放锁       |
| COMMIT;                                                |                        | 提交事务               |

### 1.5 测试 锁等待时直接报错
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 10 FOR UPDATE;        |                | 添加 排他记录锁和表意向排他锁 |
| SELECT * FROM performance_schema.data_locks\G          |                      | 排他记录锁和表意向排他锁 |
|                                                        | START TRANSACTION;     | 开启事务               |
|       | SELECT * FROM student WHERE id = 10 FOR SHARE NOWAIT;                   | 直接报错               |
| SELECT * FROM performance_schema.data_locks\G          | | 排他记录锁和表意向排他锁, 表意向共享锁 |
|                                                        | COMMIT;                | 提交事务               |
| COMMIT;                                                |                        | 提交事务               |

## 2. 间隙锁:
```
* 不区分 共享锁 还是 排他锁
* 针对表中不存在的记录
* 该范围内不能插入数据
* 所有的间隙锁都能共存 (可能造成死锁)
* 只有 REPEATABLE-READ 和 SERIALIZABLE 下才存在间隙锁
```

### 2.1 简单测试
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 11 FOR UPDATE;        |                        | 添加 间隙锁和表意向锁  |
| SELECT * FROM performance_schema.data_locks\G          |                        |      间隙锁和表意向锁  |
| COMMIT;                                                |                        | 提交事务               |

### 2.2 测试间隙锁可以叠加
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 11 FOR UPDATE;        |                        | 添加 间隙锁和表意向锁  |
| SELECT * FROM performance_schema.data_locks\G          |                        |      间隙锁和表意向锁  |
|                        | START TRANSACTION;                                     | 开启事务               |
|                        | SELECT * FROM student WHERE id = 11 FOR SHARE;         | 添加 间隙锁和表意向锁  |
| SELECT * FROM performance_schema.data_locks\G          |                        |      间隙锁和表意向锁  |
|                                                        | COMMIT;                | 提交事务               |
| COMMIT;                                                |                        | 提交事务               |

### 2.3 测试死锁
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 11 FOR UPDATE;        |                        | 添加 间隙锁和表意向锁  |
| SELECT * FROM performance_schema.data_locks\G          |                        |      间隙锁和表意向锁  |
|                        | START TRANSACTION;                                     | 开启事务               |
|                        | SELECT * FROM student WHERE id = 11 FOR SHARE;         | 添加 间隙锁和表意向锁  |
| SELECT * FROM performance_schema.data_locks\G          |                        |      间隙锁和表意向锁  |
| INSERT INTO student VALUES(11, '789');                 |                    | 等待, 会增加一个插入意向锁 |
| | INSERT INTO student VALUES(11, '789');                       | 会造成死锁, 自动解决, 回退其中一个操作  |
| SELECT * FROM performance_schema.data_locks\G          |             | 间隙锁和表意向锁, 行级插入意向锁  |
|                                                        | COMMIT;                | 提交事务               |
| COMMIT;                                                |                        | 提交事务               |

### 2.4 测试 READ-UNCOMMITTED 下没有间隙锁
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; |                        | 设置变量              |
|                        | SET SESSION TRANSACTION_ISOLATION = 'READ-UNCOMMITTED'; | 设置变量              |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 15 FOR UPDATE;        |                        | 添加表意向锁           |
| SELECT * FROM performance_schema.data_locks\G          |                        |     表意向锁           |
| COMMIT;                                                |                        | 提交事务               |

### 2.5 测试 READ-COMMITTED 下没有间隙锁
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED'; |                         | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED';  | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 15 FOR UPDATE;        |                        | 添加表意向锁           |
| SELECT * FROM performance_schema.data_locks\G          |                        |     表意向锁           |
| COMMIT;                                                |                        | 提交事务               |

### 2.6 测试 REPEATABLE-READ 下有间隙锁
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 15 FOR UPDATE;        |                        | 添加表意向锁和间隙锁   |
| SELECT * FROM performance_schema.data_locks\G          |                        |     表意向锁和间隙锁   |
| COMMIT;                                                |                        | 提交事务               |

### 2.6 测试 SERIALIZABLE 下有间隙锁
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE'; |                           | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';    | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 15 FOR UPDATE;        |                        | 添加表意向锁和间隙锁   |
| SELECT * FROM performance_schema.data_locks\G          |                        |     表意向锁和间隙锁   |
| COMMIT;                                                |                        | 提交事务               |

## 3. 临键锁: 同时使用记录锁和间隙锁
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id >= 10 FOR UPDATE;       |                        | 添加表意向锁和临键锁   |
| SELECT * FROM performance_schema.data_locks\G          |                        |     表意向锁和临键锁   |
| COMMIT;                                                |                        | 提交事务               |

## 4. 插入意向锁
```
* 插入意向锁之间不排斥, 只要(主键, 唯一键不冲突即可)
* 插入意向锁可能会被间隙锁阻塞
* 被阻塞才会显示出来, 变成显示锁, 否则, 不会显示出来, 是隐式锁
```

| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM performance_schema.data_locks\G          |                        | 无锁                   |
| SELECT * FROM student WHERE id = 15 FOR UPDATE;        |                        | 添加表意向锁和间隙锁   |
| SELECT * FROM performance_schema.data_locks\G          |                        |     表意向锁和间隙锁   |
|             | INSERT INTO student VALUES(15, '张一');                           | 添加插入意向锁         |
| SELECT * FROM performance_schema.data_locks\G          |                        |       意向锁和间隙锁   |
| COMMIT;                                                |                        | 提交事务               |

## 5. 悲观锁
```
* 适用于修改大于查询的情况
* 认为其他事务很有可能修改数据, 为保险, 一定加锁
* 不能获取过时的数据
* 比如, 银行的自动取款机判断可取金额
```

## 6. 乐观锁
```
* 适用于查询大于修改的情况
* 偶尔获取过时的数据也没关系
* 大多数情况都适合
```

## 9. 页锁
```
颗粒度间于表锁和行锁之间
```

## 1. MVCC (Multiversion Concurrency Control) 多版本并发控制
```
* 为了提高并发性能
* 减少读写冲突
```

### 1.1 快照读
```
* 读取的数据可能不是最新的
* 不加锁的 SELECT 都属于快照读 (隔离级别不是 SERIALIZABLE)
```

### 1.2 当前读
```
* 读取的数据是最新的
* 其他事务不能对此进行修改
* INSERT UPDATE DELETE REPLACE 使用的是当前读, 此时, 加了一个排他锁
* 加锁 SELECT 属于当前读
* 隔离级别是 SERIALIZABLE 下的 SELECT 是当前读, 此时, 相当于加了一个 共享锁
```

## 2. 测试
```
DROP TABLE if EXISTS student;
CREATE TABLE student(id INT PRIMARY KEY, name varchar(20));
```

### 2.1 测试 开启事务的时候, 就建立快照, 使用  WITH CONSISTENT SNAPSHOT
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION  WITH CONSISTENT SNAPSHOT;           |                        | 开启事务, 快照所有表   |
|                         | UPDATE student SET name = '张六' WHERE id = 10;       | 更新数据               |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五 -- 使用快照数据 |
| COMMIT;                 |                                            | 提交事务                         |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五                 |

### 2.2 测试 第一次使用 SELECT 时, 建立快照, 不使用  WITH CONSISTENT SNAPSHOT
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
|                         | UPDATE student SET name = '张六' WHERE id = 10;       | 更新数据               |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五 -- 建立快照     |
|                         | UPDATE student SET name = '张七' WHERE id = 10;       | 更新数据               |
|                         | SELECT * FROM student;                     | 张七, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五 -- 使用快照     |
| COMMIT;                 |                                            | 提交事务                         |
|                         | SELECT * FROM student;                     | 张七, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张七, 李四, 王五                 |

### 2.3 测试使用 SELECT 时, 会对整张表建立快照
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM student WHERE id = 10;  |                              | 张三, 李四, 王五 -- 建立快照      |
|                         | UPDATE student SET name = '张六' WHERE id = 10;       | 更新数据               |
|                         | UPDATE student SET name = '李六' WHERE id = 20;       | 更新数据               |
|                         | SELECT * FROM student;                     | 张六, 李六, 王五                  |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五 -- 使用快照      |
| SELECT * FROM student WHERE id = 10;  |                              | 张三 -- 使用快照     |
| SELECT * FROM student WHERE id = 20;  |                              | 李四 -- 使用快照     |
| SELECT * FROM student WHERE id = 30;  |                              | 王五 -- 使用快照     |
| COMMIT;                 |                                            | 提交事务                         |
|                         | SELECT * FROM student;                     | 张六, 李六, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李六, 王五                 |

### 2.3 测试加锁的 SELECT
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五 -- 建立快照      |
|                         | UPDATE student SET name = '张六' WHERE id = 10;       | 更新数据               |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                  |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五 -- 使用快照      |
| SELECT * FROM student FOR SHARE;  |                                  | 张六, 李四, 王五 -- 使用当前读    |
| COMMIT;                 |                                            | 提交事务                          |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                  |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五                  |

### 2.4 测试加锁的 SELECT, 其他事务尝试修改
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五 -- 建立快照      |
| SELECT * FROM student FOR SHARE;  |                                  | 张三, 李四, 王五 -- 使用当前读    |
|                         | UPDATE student SET name = '张六' WHERE id = 10;       | 更新数据 --- 等待      |
| COMMIT;                 |                                            | 提交事务                          |
|                         | SELECT * FROM student;                     | 张三, 李四, 王五                  |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五                  |

### 2.5 测试隔离级别是 SERIALIZABLE
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';    |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| SELECT * FROM student;                                 |                        | 加锁                   |
| SELECT * FROM student WHERE id = 10;                   |                        | 加锁                   |
|                         | UPDATE student SET name = '张六' WHERE id = 10;       | 更新数据 --- 等待      |
| COMMIT;                 |                                            | 提交事务                          |
|                         | SELECT * FROM student;                     | 张三, 李四, 王五                  |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五                  |

### 2.6 测试隔离级别是 SERIALIZABLE --- 隐式事务, 使用快照
| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';    |                        | 设置变量               |
|                        | SET SESSION TRANSACTION_ISOLATION = 'SERIALIZABLE';    | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES(10, '张三');                |                        | 插入数据               |
| INSERT INTO student VALUES(20, '李四');                |                        | 插入数据               |
| INSERT INTO student VALUES(30, '王五');                |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                        | 开启事务               |
| UPDATE student SET name = '张六' WHERE id = 10;        |                        | 更新数据 --- 加锁      |
|                         | SELECT * FROM student WHERE id = 10;                  | 使用快照读             |
|                         | SELECT * FROM student WHERE id = 10 FOR SHARE;        | 使用当前读 --- 等待    |
| COMMIT;                 |                                            | 提交事务                          |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                  |
|                         | SELECT * FROM student FOR SHARE;           | 张六, 李四, 王五                  |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五                  |


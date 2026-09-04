
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

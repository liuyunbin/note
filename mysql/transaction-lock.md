
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

## 7. 全局锁
```
Flush tables with read lock
```

## 8. 表锁
```
* 颗粒度大
* 容易锁争用
* 死锁概率低

# 8.1 共享锁(S)和排他锁(X)
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
```

## 9. 页锁
```
颗粒度间于表锁和行锁之间
```

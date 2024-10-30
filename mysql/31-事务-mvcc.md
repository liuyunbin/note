
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
CREATE TABLE student(id INT PRIMARY KEY, name varchar(20) UNIQUE);
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

### 2.3 测试 第一次使用 SELECT 时, 建立快照, 不使用  WITH CONSISTENT SNAPSHOT



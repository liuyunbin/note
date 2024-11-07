
## 0. 事务基础: ACID
```
* 原子性
* 一致性: 执行事务后的业务状态合法
* 隔离型: 事务之间不受影响
* 持久性: 持久保存到文件
```

## 1. 隐式事务
```
* DML: autocommit = ON 且 未显示开启事务
```

## 2. 显式事务
```
DROP TABLE if EXISTS student;
CREATE TABLE student(name varchar(20) UNIQUE);
```

#### 2.1 使用 BEGIN 开启事务
| 会话A                               | 会话B                  | 说明     |
| ----------------------------------- | ---------------------- | -------- |
| TRUNCATE student;                   |                        | 清空表   |
| BEGIN;                              |                        | 开启事务 |
| INSERT INTO student VALUES('张三'); |                        | 插入数据 |
| SELECT * FROM student;              |                        | 张三     |
|                                     | SELECT * FROM student; | 空表     |
| COMMIT;                             |                        | 提交事务 |
| SELECT * FROM student;              |                        | 张三     |
|                                     | SELECT * FROM student; | 张三     |

#### 2.2 使用 START TRANSACTION 开启事务 (读写事务)
| 会话A                               | 会话B                  | 说明     |
| ----------------------------------- | ---------------------- | -------- |
| TRUNCATE student;                   |                        | 清空表   |
| START TRANSACTION;                  |                        | 开启事务 |
| INSERT INTO student VALUES('张三'); |                        | 插入数据 |
| SELECT * FROM student;              |                        | 张三     |
|                                     | SELECT * FROM student; | 空表     |
| COMMIT;                             |                        | 提交事务 |
| SELECT * FROM student;              |                        | 张三     |
|                                     | SELECT * FROM student; | 张三     |

#### 2.3 测试普通回滚
| 会话A                               | 会话B                  | 说明       |
| ----------------------------------- | ---------------------- | ---------- |
| TRUNCATE student;                   |                        | 清空表     |
| START TRANSACTION;                  |                        | 开启事务   |
| INSERT INTO student VALUES('张三'); |                        | 插入数据   |
| INSERT INTO student VALUES('李四'); |                        | 插入数据   |
| SELECT * FROM student;              |                        | 张三, 李四 |
|                                     | SELECT * FROM student; | 空表       |
| ROLLBACK;                           |                        | 回滚       |
| SELECT * FROM student;              |                        | 空表       |
|                                     | SELECT * FROM student; | 空表       |
| COMMIT;                             |                        | 提交事务   |
| SELECT * FROM student;              |                        | 空表       |
|                                     | SELECT * FROM student; | 空表       |

#### 2.4 测试: 设置回滚点 SAVEPOINT
| 会话A                               | 会话B                  | 说明       |
| ----------------------------------- | ---------------------- | ---------- |
| TRUNCATE student;                   |                        | 清空表     |
| START TRANSACTION;                  |                        | 开启事务   |
| INSERT INTO student VALUES('张三'); |                        | 插入数据   |
| SAVEPOINT p1;                       |                        | 设置回滚点 |
| INSERT INTO student VALUES('李四'); |                        | 插入数据   |
| SELECT * FROM student;              |                        | 张三, 李四 |
|                                     | SELECT * FROM student; | 空表       |
| ROLLBACK TO p1;                     |                        | 回滚到 p1  |
| SELECT * FROM student;              |                        | 张三       |
|                                     | SELECT * FROM student; | 空表       |
| COMMIT;                             |                        | 提交事务   |
| SELECT * FROM student;              |                        | 张三       |
|                                     | SELECT * FROM student; | 张三       |

#### 2.5 completion_type = 0, autocommit = ON 后续命令会自动提交
| 会话A                               | 会话B                  | 说明                 |
| ----------------------------------- | ---------------------- | ------------         |
| SET SESSION autocommit      = ON;   |                        | 设置自动提交         |
| SET SESSION completion_type = 0;    |                        | 设置变量             |
| TRUNCATE student;                   |                        | 清空表               |
| START TRANSACTION;                  |                        | 开启事务             |
| INSERT INTO student VALUES('张三'); |                        | 插入数据             |
| SELECT * FROM student;              |                        | 张三                 |
|                                     | SELECT * FROM student; | 空表                 |
| COMMIT;                             |                        | 提交事务             |
| SELECT * FROM student;              |                        | 张三                 |
|                                     | SELECT * FROM student; | 张三                 |
| INSERT INTO student VALUES('李四'); |                        | 插入数据, 自动提交   |
| SELECT * FROM student;              |                        | 张三, 李四           |
|                                     | SELECT * FROM student; | 张三, 李四           |

#### 2.6 completion_type = 0, autocommit = OFF 后续命令不会自动提交
| 会话A                               | 会话B                  | 说明                   |
| ----------------------------------- | ---------------------- | ------------           |
| SET SESSION autocommit      = OFF;  |                        | 设置不会自动提交       |
| SET SESSION completion_type = 0;    |                        | 设置变量               |
| TRUNCATE student;                   |                        | 清空表                 |
| START TRANSACTION;                  |                        | 开启事务               |
| INSERT INTO student VALUES('张三'); |                        | 插入数据               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 空表                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 张三                   |
| INSERT INTO student VALUES('李四'); |                        | 插入数据, 不会自动提交 |
| SELECT * FROM student;              |                        | 张三, 李四             |
|                                     | SELECT * FROM student; | 张三                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 张三, 李四             |
|                                     | SELECT * FROM student; | 张三, 李四             |

#### 2.7 completion_type = 1, autocommit = ON 后续命令不会自动提交
| 会话A                               | 会话B                  | 说明                   |
| ----------------------------------- | ---------------------- | ------------           |
| SET SESSION autocommit      = ON;   |                        | 设置自动提交           |
| SET SESSION completion_type = 1;    |                        | 设置变量               |
| TRUNCATE student;                   |                        | 清空表                 |
| START TRANSACTION;                  |                        | 开启事务               |
| INSERT INTO student VALUES('张三'); |                        | 插入数据               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 空表                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 张三                   |
| INSERT INTO student VALUES('李四'); |                        | 插入数据, 不会自动提交 |
| SELECT * FROM student;              |                        | 张三, 李四             |
|                                     | SELECT * FROM student; | 张三                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 张三, 李四             |
|                                     | SELECT * FROM student; | 张三, 李四             |

#### 2.8 completion_type = 1, autocommit = OFF 后续命令不会自动提交
| 会话A                               | 会话B                  | 说明                   |
| ----------------------------------- | ---------------------- | ------------           |
| SET SESSION autocommit      = OFF;  |                        | 设置不会自动提交       |
| SET SESSION completion_type = 1;    |                        | 设置变量               |
| TRUNCATE student;                   |                        | 清空表                 |
| START TRANSACTION;                  |                        | 开启事务               |
| INSERT INTO student VALUES('张三'); |                        | 插入数据               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 空表                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 张三                   |
| INSERT INTO student VALUES('李四'); |                        | 插入数据, 不会自动提交 |
| SELECT * FROM student;              |                        | 张三, 李四             |
|                                     | SELECT * FROM student; | 张三                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 张三, 李四             |
|                                     | SELECT * FROM student; | 张三, 李四             |

#### 2.9 completion_type = 2  提交后断开连接 (使用终端测试)
| 会话A                               | 会话B                  | 说明                   |
| ----------------------------------- | ---------------------- | ------------           |
| SET SESSION completion_type = 2;    |                        | 设置变量               |
| TRUNCATE student;                   |                        | 清空表                 |
| START TRANSACTION;                  |                        | 开启事务               |
| INSERT INTO student VALUES('张三'); |                        | 插入数据               |
| SELECT * FROM student;              |                        | 张三                   |
|                                     | SELECT * FROM student; | 空表                   |
| COMMIT;                             |                        | 提交事务               |
| SELECT * FROM student;              |                        | 报错, 重连             |
|                                     | SELECT * FROM student; | 张三                   |

#### 2.10 使用 START TRANSACTION READ WRITE -- 读写事务
| 会话A                               | 会话B                  | 说明     |
| ----------------------------------- | ---------------------- | -------- |
| TRUNCATE student;                   |                        | 清空表   |
| START TRANSACTION READ WRITE;       |                        | 开启事务 |
| INSERT INTO student VALUES('张三'); |                        | 插入数据 |
| SELECT * FROM student;              |                        | 张三     |
|                                     | SELECT * FROM student; | 空表     |
| COMMIT;                             |                        | 提交事务 |
| SELECT * FROM student;              |                        | 张三     |
|                                     | SELECT * FROM student; | 张三     |

#### 2.11 使用 START TRANSACTION READ ONLY -- 只读事务
* 只读指对于其他事务能访问的资源, 不包括临时表

| 会话A                               | 会话B                  | 说明           |
| ----------------------------------- | ---------------------- | --------       |
| TRUNCATE student;                   |                        | 清空表         |
| START TRANSACTION READ ONLY;        |                        | 开启事务       |
| INSERT INTO student VALUES('张三'); |                        | 插入数据, 报错 |
| SELECT * FROM student;              |                        | 空表           |
|                                     | SELECT * FROM student; | 空表           |
| COMMIT;                             |                        | 提交事务       |
| SELECT * FROM student;              |                        | 空表           |
|                                     | SELECT * FROM student; | 空表           |

#### 2.12 REPEATABLE READ 下, 使用 START TRANSACTION WITH CONSISTENT SNAPSHOT -- 一致性读
* 建立事务的时候, 会快照所有的表

| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES('张三');                    |                        | 插入数据               |
| INSERT INTO student VALUES('李四');                    |                        | 插入数据               |
| INSERT INTO student VALUES('王五');                    |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION  WITH CONSISTENT SNAPSHOT;           |                        | 开启事务, 快照所有表   |
|                         | UPDATE student SET name = '张六' WHERE name = '张三'; | 更新数据               |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张三, 李四, 王五 -- 使用快照数据 |
| COMMIT;                 |                                            | 提交事务                         |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五                 |

#### 2.13 REPEATABLE READ 下, 使用 START TRANSACTION -- 不使用一致性读
* 建立事务的时候, 会快照表中所有数据

| 会话A                                                  | 会话B                  | 说明                   |
| ------------------------------------------------------ | ---------------------- | ------------           |
| SET SESSION TRANSACTION_ISOLATION = 'REPEATABLE-READ'; |                        | 设置变量               |
| TRUNCATE student;                                      |                        | 清空表                 |
| INSERT INTO student VALUES('张三');                    |                        | 插入数据               |
| INSERT INTO student VALUES('李四');                    |                        | 插入数据               |
| INSERT INTO student VALUES('王五');                    |                        | 插入数据               |
| SELECT * FROM student;                                 |                        | 张三, 李四, 王五       |
| START TRANSACTION;                                     |                  | 开启事务, 快照表中所有数据   |
|                         | UPDATE student SET name = '张六' WHERE name = '张三'; | 更新数据               |
|                         | SELECT * FROM student;                     | 张六, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五 -- 建立快照     |
|                         | UPDATE student SET name = '张七' WHERE name = '张六'; | 更新数据               |
|                         | SELECT * FROM student;                     | 张七, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张六, 李四, 王五 -- 使用快照     |
| COMMIT;                 |                                            | 提交事务                         |
|                         | SELECT * FROM student;                     | 张七, 李四, 王五                 |
| SELECT * FROM student;  |                                            | 张七, 李四, 王五                 |

## 3. 隐式提交之前的事务
```
* DDL
* 修改密码或权限
* 开启新事务
* AUTOCOMMIT OFF -> ON
* 使用锁语句
* 数据库加载新数据
* 使用主从复制
```

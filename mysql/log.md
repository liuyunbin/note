
## 1. redo log
```
* 位于引擎层 --- InnoDB 独有
* 记录的是 物理操作, 页面的修改
* 落盘: 内存中的文件存入磁盘
* 所占的空间是固定的, 循环使用的, 满了的话必须落盘
* 查看日志文件大小: SELECT @@innodb_log_file_size
* 提高了落盘的效率 (持久性)
    * 直接写入磁盘的话
        * 随机 IO, 效率不高
        * 修改和写入不成比例, 效率不高
    * 先写日志, 再写磁盘 --- Write-Ahead Logging
        * 顺序 IO, 效率高
        * 批量写入, 减少了刷盘的频率
        * 写完日志, 就可以认为数据已持久话了, 后续写入磁盘即可
* 解决 服务器 或 操作系统 意外崩溃 --- crash-safe
    * innodb_flush_log_at_trx_commit = 0
        * 提交事务成功, 保证将 redo log 写入 MySQL 缓冲区
        * 主线程 刷新缓冲区, 落盘
        * MySQL 崩溃了, 可能会丢失数据
        * 操作系统崩溃了, 可能丢失数据
    * innodb_flush_log_at_trx_commit = 1 (默认)
        * 提交事务成功, 保证将 redo log 写入内核缓冲区, 同时刷盘
        * MySQL 崩溃了, 不会丢失数据
        * 操作系统崩溃了, 不会丢失数据
    * innodb_flush_log_at_trx_commit = 2 
        * 提交事务成功, 保证将 redo log 写入内核缓冲区
        * 主线程 刷新缓冲区, 落盘
        * MySQL 崩溃了, 不会丢失数据
        * 操作系统崩溃了, 可能丢失数据

```

## 2. binlog
```
* 位于 server 层, 所有存储引擎共有
* 记录的是逻辑操作, SQL 语言 或 行修改
* 所占的空间是可以叠加的


* 为了主从复制, 数据备份, 归档, 恢复
* 默认开启


* 解决 服务器 或 操作系统 意外崩溃 --- crash-safe
    * sync_binlog = 0: binlog 生成前落盘
    * sync_binlog = 1: 每个 binlog 都落盘  (默认)
        * MySQL 或 操作系统 崩溃了, 不会丢失数据
    * sync_binlog = n:  n个 binlog 都落盘  (默认)
        * MySQL 或 操作系统 崩溃了, 可能会丢失数据
* 格式 
    * Statement: 记录会修改数据的 sql -- 有些结果不确定的函数可能出问题
    * Row: 记录修改的结果 --- 文件会比较大 
    * Mixed: 前两个的混合
    
    







show variables like 'innodb_log%';
## 1. 二进制日志 --- binlog
```
# 1.1 
主从复制, 数据备份
默认开启

show variables like '%log_bin%';   # 日志信息
log_bin_basename -------------------- 文件路径
log_bin_index ----------------------- 管理二进制文件
log_bin_trust_function_creators ----- 信任函数的创建, 避免函数修改表信息, 导致主从不一致

SHOW BINARY LOGS;                        # 查看二进制文件及大小
mysqlbinlog /var/lib/mysql/binlog.000029 # 查看二进制文件内容
RESET MASTER;                            # 删除所有的日志文件

格式:
SET SESSION TRANSACTION_ISOLATION = 'READ-COMMITTED';
set SESSION binlog_format=STATEMENT

Statement: 记录会修改数据的 sql -- 有些结果不确定的函数可能出问题
Row: 记录修改的结果 --- 文件会比较大 
Mixed: 前两个的混合
```

### 7.1 配置文件
```
[mysqld]
log-bin=..... ---------------------- 目录
binlog_expire_logs_seconds=..... --- 保存时间
max_binlog_size=..... -------------- 文件最大大小
server-id=1             # 服务器唯一ID
read-only=0             # 0-主机 1-从机
binlog-ignore-db=test   # 忽略的库名称
binlog-do-db=test       # 复制的库名称, 默认全部复制
binlog_format=STATEMENT # 格式
```

### 7.2 主从复制
```
                                                     # 主机
server-id=1                                          # 1. 配置主机ID
binlog-do-db=test                                    # 2. 配置要同步的数据库
systemctl restart mysql                              # 3. 重启 mysql
CREATE USER 'slave1'@'%' IDENTIFIED BY '123abcABC@'; # 4. 新建用户
GRANT REPLICATION SLAVE ON *.* TO 'slave1'@'%';      # 5. 赋予权限
flush privileges;                                    # 6. 刷新权限
show master status;                                  # 7. 查看主机 BINLOG

                                                     # 从机
server-id=11                                         # 1. 配置从机ID
systemctl restart mysql                              # 2. 重启 mysql
mysql -u slave1 -h 144.168.57.124 -p --get-server-public-key
                                                     # 3. 登录主机, 获取公钥
CREATE DATABASE test;                                # 4. 登录从机, 创建数据库
CHANGE MASTER TO                                     # 5. 登录从机, 配置主机信息
MASTER_HOST='144.168.57.124',
MASTER_USER='slave1',
MASTER_PASSWORD='123abcABC@',
MASTER_LOG_FILE='binlog.000068',
MASTER_LOG_POS=157;
START  SLAVE;                                        # 6. 开启slave
SHOW SLAVE STATUS\G;     # 7. 查看主从信息 -- 两项都为 YES 成功
     Slave_IO_Running: Yes
     Slave_SQL_Running: Yes

                         # 8. 主机创建信息, 从机查看
STOP   SLAVE;            # 9. 停止主从复制
```



### 7.1 配置文件
```
[mysqld]
log-bin=..... ---------------------- 目录
binlog_expire_logs_seconds=..... --- 保存时间
max_binlog_size=..... -------------- 文件最大大小
server-id=1             # 服务器唯一ID
read-only=0             # 0-主机 1-从机
binlog-ignore-db=test   # 忽略的库名称
binlog-do-db=test       # 复制的库名称, 默认全部复制
binlog_format=STATEMENT # 格式

show variables like '%log_bin%';   # 日志信息
log_bin_basename -------------------- 文件路径
log_bin_index ----------------------- 管理二进制文件
log_bin_trust_function_creators ----- 信任函数的创建, 避免函数修改表信息, 导致主从不一致

SHOW BINARY LOGS;                        # 查看二进制文件及大小
mysqlbinlog /var/lib/mysql/binlog.000029 # 查看二进制文件内容
RESET MASTER;                            # 删除所有的日志文件

```
    
    
```

## 3. 两阶段提交
```
# 3.1 流程
1. 修改内存中的数据
2. 写入 redo log --- prepare
3. 写入 binlog -- 主从复制
4. redo log: prepare -> commit
5. 提交事务

# 3.2 恢复数据
1. 如果 1 后崩溃, 相当于该事务没有执行
2. 如果 2 后崩溃
    * redo log 处于 prepare
    * binlog 没有对应数据, 从库中没有对应数据
    * 相当于该事务未执行
3. 如果 3 后崩溃
    * redo log 处于 prepare
    * binlog 有对应数据, 从库中有对应数据
    * 相当于该事务已执行
    * 使用 redo log  恢复当前库  
4. 如果 4 后崩溃
    * redo log 处于 commit
    * binlog 有对应数据, 从库中有对应数据
    * 相当于该事务已执行
    * 使用 redo log  恢复当前库
5. 如果 5 后崩溃 -- 事务已完成

# 3.3 不能先写 redo log, 再写 binlog
1. 修改内存中的数据
2. 写入 binlog -- 主从复制  --- prepare
3. 写入 redo log
4. binlog: prepare -> commit
5. 提交事务

如果, 执行 2 后 MySQL 意外重启,
需要手动删除 binlog, 会自找烦恼
而, redo log 会自动处理

# 3.4 不使用两阶段提交: 先写 redo log, 再写 binlog
1. 修改内存中的数据
2. 写入 redo log
3. 写入 binlog -- 主从复制
4. 提交事务

如果执行完 2, MySQL 意外重启了
* 使用 redo log 恢复了数据
* binlog 不包括修改, 导致主从不一致

# 3.5 不使用两阶段提交: 不能先写 binlog , 再写 redo log
1. 修改内存中的数据
2. 写入 binlog -- 主从复制
3. 写入 redo log
4. 提交事务

如果执行完 2, MySQL 意外重启了
* binlog 包括修改, 从机器获取了修改的内容
* redo log 没有修改的数据, 主机器没有修改的数据
* 导致主从不一致

# 3.6 只使用 binlog
* binlog 不支持崩溃后恢复

# 3.7 只使用 redo log
* redo log 使用 固定的, 循环使用的 存储空间, 无法归档数据
```








## 0. 总结
```
* 会损耗性能
* 日志最好不要和数据放在同一个磁盘
```

## 1. 慢查询日志
```
默认关闭

SHOW VARIABLES LIKE '%slow_query_log%';          # 1. 查看慢查询日志是否开启及日志文件位置
SET  GLOBAL slow_query_log='ON';                 # 2. 开启慢查询日志
SHOW VARIABLES LIKE '%slow_query_log%';          # 3. 再次查看慢查询日志是否开启及日志文件位置

SHOW GLOBAL  VARIABLES LIKE '%long_query_time%'; # 4. 查看慢查询的时间阈值
SHOW SESSION VARIABLES LIKE '%long_query_time%'; #
SET  GLOB AL long_query_time = 1;                # 5. 设置慢查询的时间阈值
SET  SESSION long_query_time = 1;                #
SHOW GLOBAL  VARIABLES LIKE '%long_query_time%'; # 6. 再次查看慢查询的时间阈值
SHOW SESSION VARIABLES LIKE '%long_query_time%'; #

SHOW STATUS LIKE 'Slow_queries';                 # 7. 查看慢查询的次数
SELECT course_id,class_id,name,create_time,student_id
FROM student_info
WHERE student_id = 123110;                       # 8. 执行慢查询
SHOW STATUS LIKE 'Slow_queries';                 # 9. 再次查看慢查询的次数

                                                 # 10. 切换到慢查询目录
mysqldumpslow -s t -t 5 ....log                  # 11. 查询耗时最长的 5 条慢查询

SET  GLOBAL slow_query_log='OFF';                # 12. 开启慢查询日志
SHOW VARIABLES LIKE '%slow_query_log%';          # 13. 再次查看慢查询日志是否开启及日志文件位置


# 重建慢查询日志
SET GLOBAL slow_query_log=ON;        # 要打开慢查询日志
mysqladmin -uroot -p flush-logs slow # 重建慢查询日志
```

## 2. 通用查询日志
```
默认关闭

SELECT @@GLOBAL.general_log;      # 是否开启
SELECT @@GLOBAL.general_log_file; # 日志位置
SHOW VARIABLES LIKE '%general%';  # 日志信息
mysqladmin -uroot -p flush-logs;  # 刷新日志
```

## 3. 错误日志
```
默认开启, 无法关闭

SHOW VARIABLES LIKE 'log_err%';   # 日志信息
mysqladmin -uroot -p flush-logs;  # 刷新日志
```

## 4. 中继日志
```
主从架构中的从服务器存放
```

## 6. undo log
```
* 记录的是 逻辑操作
* 比如 执行 INSERT 操作, 就记录一条 DELETE 操作
* 用于事务的回滚
```



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

## 5. redo log
```
* 记录的是 物理操作
* 为解决 服务器 或 操作系统 意外崩溃导致数据丢失的情况
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
```

## 6. undo log
```
* 记录的是 逻辑操作
* 比如 执行 INSERT 操作, 就记录一条 DELETE 操作
* 用于事务的回滚
```

## 7. 二进制日志
```
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

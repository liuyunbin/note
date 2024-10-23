
## 1. 存储引擎基础
```
SHOW ENGINES;                           # 查看存储引擎
SHOW VARIABLES LIKE '%storage_engine%'; # 查看默认引擎
SET DEFAULT_STORAGE_ENGINE=MyISAM;      # 设置默认引擎

DROP TABLE IF EXISTS student;                 # 1. 删除之前的表
CREATE TABLE student (id INT, name VARCHAR(20)) ENGINE = MyISAM;
                                              # 2. 创建表时, 设置存储引擎 MyISAM
SHOW   CREATE TABLE student;                  # 3. 查看存储引擎
EXPLAIN SELECT count(*) FROM student;         # 4. 查看执行计划: Select tables optimized away
ALTER  TABLE student ENGINE = InnoDB;         # 5. 修改表的存储引擎为 InnoDB
SHOW   CREATE TABLE student;                  # 6. 查看存储引擎
EXPLAIN SELECT count(*) FROM student;         # 7. 查看执行计划
```

## 2. 引擎类别
```
# 2.1 InnoDB (默认 建议)
* 5.5 后的默认存储引擎
* 支持事务
* 支持外键
* 支持行锁和表锁
* 崩溃后可以自动恢复 (利用事务)
* 相比较 MyISA, 需要更多的磁盘空间和内存
* 相比较 MyISA, 会在内存中缓存索引和真实数据
* 相比较 MyISA, 效率低一些
* count(*) 需要完整扫描表

# 2.2 MyISAM
* 不支持事务, 行锁, 外键
* 崩溃后无法安全恢复 (没有事务)
* 5.5 之前默认的存储引擎
* 相比较 InnoDB, 效率高一些
* 单独存储函数, 所以 count(*) 为常量值

# 2.3 Archive 引擎：用于数据存档
* 只支持插入和查询
* 查询效率低
* 支持索引

# 2.4 Blackhole: 丢弃写操作，读操作会返回空内容

# 2.5 CSV: 存储数据时，以逗号分隔各个数据项
* 不支持索引
* 可以使用文本编辑器编辑文件

# 2.6 Memory: 置于内存的表
* 支持索引
* 纯内存操作, 效率高
* 受制于内存大小, 表一般不大
* 数据容易丢失

# 2.7 Federated: 访问远程表

# 2.8 Merge: 管理多个MyISAM表构成的表集合

# 2.9 NDB: 集群专用存储引擎
```

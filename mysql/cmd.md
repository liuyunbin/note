
## 命令及相关配置
```
mysqld       启动服务器 [mysqld]、[server]
mysqld_safe  启动服务器 [mysqld]、[server]、[mysqld_safe]
mysql        启动客户端 [mysql]、[client]
mysqladmin   启动客户端 [mysqladmin]、[client]
mysqldump    启动客户端 [mysqldump]、[client]

mysqldump -uroot -p --all-databases                             > back.sql # 备份所有的库 + 表
mysqldump -uroot -p --databases database_name_1 database_name_2 > back.sql # 备份指定 库 + 表
mysqldump –uroot –p    database_name table_name_1 table_name_2  > back.sql # 备份表
mysqldump -uroot -p    database_name table_name_1 --where="id < 10 " > back.sql
                                        # 备份指定条件的表
mysqldump -uroot -p database_name --ignore-table=database_name.student > back.sql
                                        # 忽略指定条件的表
mysqldump -uroot -p database_name --no-data        > back.sql # 只备份表结果, 不备份数据
mysqldump -uroot -p database_name --no-create-info > back.sql # 只备份数据,   不备份结构
    
mysqldump –uroot –p --routines database_name table_name_1 table_name_2  > back.sql
                                        # 备份表 存储过程 函数
mysqldump –uroot –p --events database_name table_name_1 table_name_2    > back.sql
                                        # 备份表 事件
                                        
mysql –u root –p [database_name] < backup.sql # 还原数据

mysql> source back.sql;  # 还原数据

# 文本文件
SELECT * FROM student INTO OUTFILE back.txt                                   # 导出数据

SELECT .. INTO OUTFILE ..
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
LINES TERMINATED BY '\n' FROM ..
                                # 保存数据到文件, 指定行和列的分隔符 以及字符串的引号

mysql -uroot -p            --execute="SELECT * FROM account;" test > back.txt
mysql -uroot -p --vertical --execute="SELECT * FROM student;" test > back.txt # 一条记录多行显示
mysql -uroot -p --xml      --execute="SELECT * FROM student;" test > back.xml
mysql -uroot -p --html     --execute="SELECT * FROM student;" test > back.html

LOAD DATA INFILE back.txt INTO TABLE test.student; # 导入数据
LOAD DATA INFILE back.txt INTO TABLE test.student FIELDS TERMINATED BY ',' ENCLOSED BY '\"';
                                                   # 指定行和列的分隔符
mysqlimport -uroot -p atguigu back.txt --fields-terminated-by=',' --fields-optionally-enclosed-by='\"'

set global max_allowed_packet=64*1024*1024 # 设置插入的上限

```

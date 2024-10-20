
## 慢查询日志
```
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

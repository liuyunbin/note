
## 触发器
### 1. 说明
```
* 可用于自动维护一些信息, 比如 日志
* 可用于检查入参的错误
* 底层表变化时, 需要修改触发器
* 由于操作是自动的, 不容易发现错误
* OLD 获取旧数据, NEW 获取新数据

CREATE TRIGGER trigger_name
[BEFORE|AFTER]  [INSERT|UPDATE|DELETE]
ON table_name FOR EACH ROW ...

DROP TRIGGER   table_name.trigger_name; # 删除触发器
```

### 2. 测试
```
# 1. 日志记录
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DROP   TABLE IF EXISTS student_log;
CREATE TABLE student_log (log_time DATETIME, log_name VARCHAR(20));

DROP   TRIGGER   IF EXISTS trigger_name;
CREATE TRIGGER trigger_name AFTER INSERT ON student FOR EACH ROW
INSERT INTO student_log values(now(), "insert");
SELECT * FROM student; 
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student; 
SELECT * FROM student_log;

# 2. 检查入参 (只是测试, 用唯一键更合适)
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DROP   TABLE IF EXISTS student_log;
CREATE TABLE student_log (log_time DATETIME, log_name VARCHAR(20));

DROP   TRIGGER   IF EXISTS trigger_name;
DELIMITER $
CREATE TRIGGER trigger_name
BEFORE INSERT ON student FOR EACH ROW
BEGIN
    DECLARE num int DEFAULT(0);
    
    SELECT count(*) into num FROM student WHERE name = NEW.name;
    
    IF num != 0 THEN
        SIGNAL SQLSTATE 'HY000' SET MESSAGE_TEXT = '数据已存在, 不允许插入';
    END IF;
    
    INSERT INTO student_log values(now(), "insert");
END $
DELIMITER ;

SELECT * FROM student; 
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student; 
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student;
SELECT * FROM student_log;
```

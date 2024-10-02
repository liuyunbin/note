
## 汇总
```
SET  @@GLOBAL.log_bin_trust_function_creators = 1; # 设置全局系统变量, 服务器重启失效
SET @@PERSIST.log_bin_trust_function_creators = 1; # 设置全局系统变量, 服务器重启依然保留
SET @@SESSION.log_bin_trust_function_creators = 1; # 设置会话系统变量, 服务器重启失效
SET @name = 'Tom'; # 设置会话用户变量
SET  name = 'Tom'; # 设置局部变量
```

## 1. 游标: 用于定位某条记录
### 1.1 说明
```
* 游标使用过程会对数据加锁
* 耗内存资源

DECLARE cursor_name CURSOR FOR select ....; # 1. 定义游标
OPEN    cursor_name;                        # 2. 打开游标
FETCH   cursor_name INTO var_name ...;      # 3. 使用游标
CLOSE   cursor_name;                        # 4. 关闭游标, 需要及时关闭, 否则消耗系统资源
```

### 1.2 实例
#### 1.2.1 数据准备
```
USE    test;
DROP   TABLE IF EXISTS employees;
CREATE TABLE employees(id INT, name VARCHAR(20), salary INT);
INSERT INTO  employees values(1, "张三",  7000);
INSERT INTO  employees values(2, "李四",  8000);
INSERT INTO  employees values(3, "王五",  9000);
INSERT INTO  employees values(4, "赵六", 10000);
INSERT INTO  employees values(4, "田七", 11000);
```

#### 1.2.2 定义存储过程
```
USE  test;
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name(IN total_salary INT, OUT ret int, INOUT sum_salary INT, INOUT count_salary INT)
BEGIN
  DECLARE  curr_salary INT DEFAULT 0;
  DECLARE v_not_found  INT DEFAULT FALSE;
  DECLARE cursor_name CURSOR FOR SELECT salary FROM employees ORDER BY salary DESC;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_not_found = TRUE;  # 游标无数据时 设置变量

  OPEN    cursor_name;

  add_loop: LOOP
      FETCH cursor_name INTO curr_salary;
      IF v_not_found THEN
        SET ret = -1;
        LEAVE add_loop;
      END IF;
      SET sum_salary   = sum_salary + curr_salary;
      SET count_salary = count_salary + 1;
      IF sum_salary > total_salary THEN
        SET ret = 0;
        LEAVE add_loop;
      END IF;
  END LOOP add_loop;

  CLOSE   cursor_name;
END $
DELIMITER ;
```

#### 1.2.3 测试
```
SET @ret          = 0;
SET @sum_salary   = 0;
SET @count_salary = 0;
CALL   procedure_name(20000, @ret, @sum_salary, @count_salary);   # 正常获取
SELECT @ret, @sum_salary, @count_salary;
CALL   procedure_name(200000, @ret, @sum_salary, @count_salary);  # 测试报错
SELECT @ret, @sum_salary, @count_salary;
```

## 2. 触发器
### 2.1 说明
```
* 可用于自动维护一些信息, 比如 日志
* 可用于检查入参的错误
* 底层表变化时, 需要修改触发器
* 由于操作是自动的, 不容易发现错误
* OLD 获取旧数据, NEW 获取新数据

CREATE TRIGGER trigger_name
[BEFORE|AFTER]  [INSERT|UPDATE|DELETE]
ON table_name FOR EACH ROW ...

DROP TRIGGER   table_name.trigger_name;               # 删除触发器
```

### 2.2 测试
#### 2.2.1 日志记录
```
USE test;
DROP TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DROP TABLE IF EXISTS student_log;
CREATE TABLE student_log (log_time DATETIME, log_name VARCHAR(20));

DROP   TRIGGER   IF EXISTS trigger_name;
CREATE TRIGGER trigger_name AFTER INSERT ON student FOR EACH ROW
INSERT INTO student_log values(now(), "insert");
SELECT * FROM student;
SELECT * FROM student_log;
INSERT INTO student VALUES(1, "张三");
SELECT * FROM student;
SELECT * FROM student_log;
```

#### 2.2.2 检查入参 (只是测试, 用唯一键更合适)
```
USE test;
DROP TABLE IF EXISTS student;
CREATE TABLE student (id INT, name VARCHAR(20));
DROP TABLE IF EXISTS student_log;
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

round -- 不一定是直观 的四舍五入

current_timestamp()
current_date()
now()

## 练习子查询
```
# 1. 为什么使用数据库
* 数据持久化
* 效率

DDL: create drop alter rename truncate

DDL(数据定义语言): CREATE DROP   ALTER
DML(数据操作语言): INSERT UPDATE SELECT DELETE
DCL(数据控制语言): GRANT  REVOKE COMMIT ROLLBACK SAVEPOINT

source ...

round -- 不一定是直观 的四舍五入

DB: 数据库 Database
DBMS: 数据库管理系统 Database Management System
SQL: 结构化查询语言 Structured Query Language

RDBMS: 关系型数据库
* 将复杂的关系转化为二元的关系, 表格
* 表之间通过外键来关联

E-R(entity-relationship 实体-联系)模型中有三个主要概念是 实体集 属性集 联系集
一个实体集(class)   == 一个表(table)
一个实体(instance)  == 一行(row), 一条记录(record)
一个属性(attribute) == 一列(column), 一个字段(field)

表之间的关系
一对一: 用的不多, 可以使用一张表, 但会冗余
一对多
多对多
自引用

单引号: 字符串 日期
双引号: 别名
反引用: 与关键字冲突时, 使用

库名 表名 表别名 字段名 字段别名 小写, 其他建议大写

## 其他
mysql -D <库名> -h <域名> -u <用户名> -p<密码>  # 登录
myqsl -D testdb < 1.sql                         # 从文件导入
mysqldump database_name table_name > 1.sql      # 导出到文件
select .. into outfile .. fields terminated by ',' optionally enclosed by '"' lines terminated by '\n' from ..
                                                # 保存数据到文件

mysql_install_db --user=mysql --ldata=/var/lib/mysql # 添加用户 mysql 使mysqld 可以使用 systemctl 启动

set global max_allowed_packet=64*1024*1024 # 设置插入的上限

current_timestamp()
current_date()
now()


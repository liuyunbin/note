
## 汇总
```
SET  @@GLOBAL.log_bin_trust_function_creators = 1; # 设置全局系统变量, 服务器重启失效
SET @@PERSIST.log_bin_trust_function_creators = 1; # 设置全局系统变量, 服务器重启依然保留
SET @@SESSION.log_bin_trust_function_creators = 1; # 设置会话系统变量, 服务器重启失效
SET @name = 'Tom'; # 设置会话用户变量
SET  name = 'Tom'; # 设置局部变量


```

```


## 1. 存储过程
### 1.1 优缺点
```
* 提前编译, 效率高
* 简化操作
* 提高复用
* 减少操作失误
* 减少网上传输的数据
* 提高了数据安全
* 没返回值
* 不好调试
* 分表时, 不好维护
* 跨数据库不好移植
* 不好做版本管理
```

### 1.2 说明
```
DELIMITER $
CREATE PROCEDURE procedure_name(...) ------- IN, OUT, INOUT
[characteristics ...]
BEGIN
    ...
END $
DELIMITER ;

characteristics:
* LANGUAGE SQL ----------- 语言 SQL
* DETERMINISTIC ---------- 相同的输入会得到相同的输出
* NOT DETERMINISTIC ------ 相同的输入不一定会得到相同的输出 ---- 默认值
* NO SQL ----------------- 不包含任何 SQL 语句
* CONTAINS SQL ----------- 不包含任何 SQL 语句, 但是并不包含读写数据的SQL语句 ---- 默认
* READS SQL DATA --------- 包含读数据的 SQL 语句
* MODIFIES SQL DATA ------ 包含写数据的 SQL 语句
* SQL SECURITY DEFINER --- 只允许创建者或定义者使用 --- 默认
* SQL SECURITY INVOKER --- 允许所有人使用
* COMMENT string --------- 注释信息

CALL procedure_name(...)
```

### 1.3 示例
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    SELECT 123;
END $
DELIMITER ;

CALL  procedure_name();
SHOW  CREATE PROCEDURE procedure_name;
```

## 2. 函数
### 2.1 和存储过程的区别
```
* 有返回值
* 参数只能是 IN
* 需要设置: SET GLOBAL log_bin_trust_function_creators = 1
```

### 2.2 说明
```
DELIMITER $
CREATE FUNCTION function_name(...)
[characteristics ...]
RETURNS ...
BEGIN
   ...
END $
DELIMITER ;

SELECT procedure_name(...)
```

### 2.3 实例
```
SET GLOBAL log_bin_trust_function_creators = 1; # 使用 root 用户或有权限的用户设置

DROP FUNCTION  IF EXISTS function_name;
DELIMITER $
CREATE FUNCTION function_name()
RETURNS INT
BEGIN
   RETURN 123;
END $
DELIMITER ;

SELECT function_name();
SHOW CREATE FUNCTION function_name;
```

## 3. 变量
### 3.1 全局系统变量
```
SHOW   GLOBAL  VARIABLES LIKE 'character%';    # 查询全局系统变量
SELECT @@GLOBAL.character_set_client;          # 查询全局系统变量
SET    @@global.character_set_client = 变量值;       # 设置全局系统变量 -- 不能跨服务器重启
SET            GLOBAL character_set_client = 变量值; # 设置全局系统变量 -- 不能跨服务器重启
SET    PERSIST GLOBAL character_set_client = 变量值; # 设置全局系统变量 -----能跨服务器重启
```

### 3.2 会话系统变量
```
* 初始值可以从全局系统变量拷贝

SHOW   SESSION VARIABLES LIKE 'character%';     # 查询会话系统变量
SELECT @@SESSION.character_set_client;          # 查询会话系统变量
SET    @@session.character_set_client = 变量值; # 设置会话系统变量
SET    SESSION   character_set_client = 变量值; # 设置会话系统变量
```

### 3.3 会话用户变量
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);
SET    @num = 100;                      # 设置会话用户变量
SELECT @num;                            # 查看会话用户变量
SELECT count(*) INTO @num FROM student; # 设置会话用户变量
SELECT @num;                            # 查看会话用户变量
```

### 3.4 局部变量
```
* 只在BEGIN 和 END 之间使用, 定义只能放在开头
* 需要指定类型
* DECLARE 定义
```

### 3.5 测试
#### 3.5.1: SET SELECT
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    DECLARE num  int;
    SET     num  = 10;
    SELECT  num;
END $
DELIMITER ;

CALL procedure_name()
```

#### 3.5.2: SET DEFAULT SELECT
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    DECLARE num  int DEFAULT 100;
    SELECT  num;
    SET     num  = 10;
    SELECT  num;
END $
DELIMITER ;

CALL procedure_name()
```

#### 3.5.3: SELECT INTO
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);

DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
    DECLARE num int;
    SELECT count(*) INTO num FROM student;
    SELECT  num;
END $
DELIMITER ;

CALL procedure_name()
```

#### 3.5.4 : 混用局部变量和用户会话变量
```
USE    test;
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);

DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name(OUT num int)
BEGIN
    SELECT count(*) INTO num FROM student;
END $
DELIMITER ;

SET    @num = 10;
SELECT @num;
CALL   procedure_name(@num);
SELECT @num;
```

## 4. 流程控制
### 4.1 语句: IF
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE num INT;
  SET num = 3;
  IF num = 1 THEN
    select "num 1", num;
  ELSEIF num = 2 THEN
    select "num 2", num;
  ELSE
    select "num 3", num;
  END IF;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.2 语句: CASE (情况一: 类似 switch)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE num INT;
  SET num = 3;
  CASE num
	WHEN 1 THEN
    select "num 1", num;
  WHEN 2 THEN
    select "num 2", num;
	ELSE
    select "num 3", num;
  END CASE;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.2 语句: CASE (情况二)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE num INT;
  SET num = 3;
  CASE
	WHEN num = 1 THEN
    select "num 1", num;
  WHEN num = 2 THEN
    select "num 2", num;
	ELSE
    select "num 3", num;
  END CASE;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.3 语句: LOOP
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE id INT DEFAULT 0;
  add_loop: LOOP
    SET id = id +1;
    IF id > 3 THEN
      LEAVE add_loop;
    ELSE
      select id;
    END IF;
  END LOOP add_loop;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.4 语句: WHILE
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE i INT DEFAULT 0;

	add_while: WHILE i < 10 DO
		SET i = i + 1;
	END WHILE add_while;

	SELECT i;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.5 语句: REPEAT (类似 do ... while)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE i INT DEFAULT 0;

  add_repeat: REPEAT
		SET i = i + 1;
	UNTIL i >= 10
	END REPEAT add_repeat;

	SELECT i;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.6 语句: ITERATE(与 continue 类似)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE id INT DEFAULT 0;
  add_loop: LOOP
    SET id = id +1;
    IF id < 10 THEN
      ITERATE add_loop;
    ELSEIF id > 13 THEN
      LEAVE add_loop;
    END IF;

    select id;
  END LOOP add_loop;
END $
DELIMITER ;

CALL procedure_name();
```

### 4.7 语句: LEAVE(与 break 类似)
```
DROP PROCEDURE IF EXISTS procedure_name;
DELIMITER $
CREATE PROCEDURE procedure_name()
BEGIN
  DECLARE id INT DEFAULT 0;
  add_loop: LOOP
    SET id = id +1;
    IF id > 3 THEN
      LEAVE add_loop;
    ELSE
      select id;
    END IF;
  END LOOP add_loop;
END $
DELIMITER ;

CALL procedure_name();
```

## 5. 异常处理
### 5.1 定义条件: 方便后续使用
```
DECLARE 错误名称 CONDITION FOR 错误码（或错误条件）

错误码: 整形
错误条件: 长度为 5 的字符串

DECLARE Field_Not_Be_NULL CONDITION FOR 1048;
DECLARE Field_Not_Be_NULL CONDITION FOR SQLSTATE '23000';
```

### 5.2 定义程序: 发生错误执行的代码
```
DECLARE 处理方式 HANDLER FOR 错误类型 处理语句
SIGNAL  错误类型 .....     ------ 抛出错误

处理方式:
* CONTINUE：表示遇到错误不处理，继续执行。
* EXIT：表示遇到错误马上退出
* UNDO：表示遇到错误后撤回之前的操作 -- MySQL中暂时不支持这样的操作

错误类型:
* SQLSTATE 字符串错误码: 上述定义的错误条件
* MySQL_error_code: 上述定义的错误码
* 错误名称: 见上述定义。
* SQLWARNING:   匹配所有以01开头的SQLSTATE错误代码
* NOT FOUND:    匹配所有以02开头的SQLSTATE错误代码
* SQLEXCEPTION: 匹配所有没有被SQLWARNING或NOT FOUND捕获的SQLSTATE错误代码

处理语句: 简单语句 或 BEGIN ... END 编写的复合语句
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



## 1. 存储过程
```
# 1. 优缺点
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

# 2. 说明
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

# 3. 示例
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
```
# 1. 和存储过程的区别
* 有返回值
* 参数只能是 IN
* 需要设置: SET GLOBAL log_bin_trust_function_creators = 1

# 2. 说明
DELIMITER $
CREATE FUNCTION function_name(...)
[characteristics ...]
RETURNS ...
BEGIN
   ...
END $
DELIMITER ;

SELECT procedure_name(...)

# 3. 实例
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
```
# 1. 全局变量
SHOW   GLOBAL  VARIABLES LIKE 'character%';    # 查询全局系统变量
SHOW   SESSION VARIABLES LIKE 'character%';    # 查询会话系统变量

SELECT  @@GLOBAL.character_set_client;         # 查询全局系统变量
SELECT @@SESSION.character_set_client;         # 查询会话系统变量

SET    @@GLOBAL.character_set_client = 变量值; # 设置全局系统变量 -- 不能跨服务器重启
SET   @@PERSIST.character_set_client = 变量值; # 设置全局系统变量 -- 能跨服务器重启
SET   @@session.character_set_client = 变量值; # 设置会话系统变量

# 2. 会话用户变量
DROP   TABLE IF EXISTS student;
CREATE TABLE student (id INT);
SET    @num = 100;                      # 设置会话用户变量
SELECT @num;                            # 查看会话用户变量
SELECT count(*) INTO @num FROM student; # 设置会话用户变量
SELECT @num;                            # 查看会话用户变量

# 3. 局部变量
* 只在BEGIN 和 END 之间使用, 定义只能放在开头
* 需要指定类型
* DECLARE 定义

# 4. 测试
# 4.1: SET SELECT
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

# 4.2: SET DEFAULT SELECT
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

# 4.3: SELECT INTO
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

# 4.4 混用局部变量和用户会话变量
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
```
# 1. 语句: IF
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

# 2. 语句: CASE (情况一: 类似 switch)
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

# 3. 语句: CASE (情况二)
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

# 4. 语句: LOOP
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

# 5. 语句: WHILE
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

# 6. 语句: REPEAT (类似 do ... while)
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

# 7. 语句: ITERATE(与 continue 类似)
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

# 8. 语句: LEAVE(与 break 类似)
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
```
# 1. 定义条件: 方便后续使用
DECLARE 错误名称 CONDITION FOR 错误码（或错误条件）

错误码: 整形
错误条件: 长度为 5 的字符串

DECLARE Field_Not_Be_NULL CONDITION FOR 1048;
DECLARE Field_Not_Be_NULL CONDITION FOR SQLSTATE '23000';

# 2. 定义程序: 发生错误执行的代码
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

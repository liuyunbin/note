
## 1. 存储过程
```
# 1.1 优缺点
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

# 1.2 说明
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

# 1.3 示例
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
# 2.1 和存储过程的区别
* 有返回值
* 参数只能是 IN
* 需要设置: SET GLOBAL log_bin_trust_function_creators = 1

# 2.2 说明
DELIMITER $
CREATE FUNCTION function_name(...)
[characteristics ...]
RETURNS ...
BEGIN
   ...
END $
DELIMITER ;

SELECT procedure_name(...)

# 2.3 实例
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

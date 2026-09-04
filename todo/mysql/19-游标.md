
## 游标: 用于定位某条记录
### 1. 说明
```
* 游标使用过程会对数据加锁
* 耗内存资源

DECLARE cursor_name CURSOR FOR select ....; # 1. 定义游标
OPEN    cursor_name;                        # 2. 打开游标
FETCH   cursor_name INTO var_name ...;      # 3. 使用游标
CLOSE   cursor_name;                        # 4. 关闭游标, 需要及时关闭, 否则消耗系统资源
```

### 2. 实例
```
# 2.1 数据准备
DROP   TABLE IF EXISTS employees;
CREATE TABLE employees(id INT, name VARCHAR(20), salary INT);
INSERT INTO  employees values(1, "张三",  7000);
INSERT INTO  employees values(2, "李四",  8000);
INSERT INTO  employees values(3, "王五",  9000);
INSERT INTO  employees values(4, "赵六", 10000);
INSERT INTO  employees values(4, "田七", 11000);

# 2.2 定义存储过程
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

# 2.3 测试
SET @ret          = 0;
SET @sum_salary   = 0;
SET @count_salary = 0;
CALL   procedure_name(20000, @ret, @sum_salary, @count_salary);   # 正常获取
SELECT @ret, @sum_salary, @count_salary;
CALL   procedure_name(200000, @ret, @sum_salary, @count_salary);  # 测试报错
SELECT @ret, @sum_salary, @count_salary;
```


## 1. 修改密码
```
SET PASSWORD                   =PASSWORD('123456');    # 修改当前用户密码 -- 旧版本 5.7
SET PASSWORD FOR user@hostname =PASSWORD('123456');    # 修改其他用户密码 -- 旧版本 5.7
SET PASSWORD                   =new_password;          # 修改当前用户密码 -- 新版本 8.0 -- 不建议使用
SET PASSWORD FOR user@hostname=new_password;           # 修改其他用户密码 -- 新版本 8.0 -- 不建议使用
ALTER USER user@hostname IDENTIFIED BY 'new_password'; # 修改其他用户密码 -- 新版本 8.0
ALTER USER user@hostname IDENTIFIED WITH caching_sha2_password BY 'new_password';
                                                       # 修改其他用户密码, 客户端为 8.0
ALTER USER user@hostname IDENTIFIED WITH mysql_native_password BY 'new_password';
                                                       # 修改其他用户密码, 客户端为 5.7
```

## 2. 忘记 root 密码 或 恢复 root 权限-- MariaDB 5.5.68 --- centos 7
```
sudo systemctl list-unit-files | grep mariadb # 1. 查看 mariadb 服务的名称
sudo systemctl stop mariadb.service;          # 2. 停止服务器
sudo mysqld_safe --skip-grant-tables &        # 3. 启动服务器, 跳过密码和权限判断
mysql -u root;                                # 4. 连接 MySQL, 不需要密码
FLUSH PRIVILEGES;                             # 5. 刷新权限, 使得权限管理生效
SET PASSWORD FOR 'root'@'localhost' = PASSWORD('root');
                                              # 6. 设置新密码(可选)
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' WITH GRANT OPTION;
                                              # 7. 赋予权限(可选)
mysqladmin -u root -p shutdown;               # 8. 使用新密码停止服务
sudo systemctl start mariadb.service;         # 9. 启动服务

见: https://dev.mysql.com/doc/refman/9.0/en/resetting-permissions.html
```

## 3. 忘记 root 密码 或 恢复 root 权限----- MySQL 8.0.39 --- ubuntu 22.04
```
sudo systemctl list-unit-files | grep mysql   # 1. 查看 mysql 服务的名称
sudo systemctl stop   mysql.service;          # 2. 停止服务器
sudo mkdir -p /var/run/mysqld                 # 3. 新建目录
sudo chown mysql:mysql /var/run/mysqld        # 4. 改变归属
sudo mysqld_safe --skip-grant-tables &        # 5. 启动服务器, 跳过密码和权限判断
mysql -u root;                                # 6. 连接 MySQL, 不需要密码
FLUSH PRIVILEGES;                             # 7. 刷新权限, 使得权限管理生效
ALTER USER 'root'@'localhost' IDENTIFIED BY 'root';
                                              # 8. 设置新密码(可选)
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' WITH GRANT OPTION;
                                              # 9. 赋予权限(可选)
mysqladmin -u root -p shutdown;               # 10. 使用新密码停止服务
sudo systemctl start   mysql.service;         # 11. 启动服务

见: https://dev.mysql.com/doc/refman/9.0/en/resetting-permissions.html
```

##  4. 权限使用原则
```
* 只赋予满足要求的最小权限
* 限制用户登录的主机, root 只允许本机登录
* 定期删除不用的用户
* 权限可以叠加
```

## 5. 权限刷新
```
* 服务端
    * GRANT, REVOKE, SET PASSWORD, RENAME USER --- 不需要刷新权限
    * INSERT, UPDATE, or DELETE -------------------- 需要刷新权限 --- 不推荐
* 客户端
    * 表和列的权限, 下一次请求的时候就会生效
    * 库的权限, 客户端使用 use ... 的时候才生效, 但客户端可能缓存库名称
    * 密码那些不会影响到已连接的客户端
* 修改权限后, 客户端最好重连

见: https://dev.mysql.com/doc/refman/9.0/en/privilege-changes.html
```

## 6. 新建用户并赋予权限
```
SELECT user,host,plugin FROM mysql.user;           # 1. 查看用户及其加密插件
SHOW VARIABLES LIKE 'validate_password%';          # 2. 查看密码要求:
                                                   #    * 大小写字母 数字 特殊字符
                                                   #    * 至少 8 个字符
CREATE USER 'dba1'@'%' IDENTIFIED BY 'Dba123456@'; # 3. 创建用户
                                                   # 4. 授予权限
GRANT  SELECT         ON test.* TO   'dba1'@'%';   #    * 库的查询权限
GRANT  ALL PRIVILEGES ON test.* TO   'dba1'@'%';   #    * 库的全部权限
SHOW   GRANTS FOR 'dba1'@'%';                      # 5. 查看用户权限
REVOKE ALL PRIVILEGES ON test.* FROM 'dba1'@'%';   # 6. 回收用户权限
DROP   USER 'dba1'@'%';                            # 7. 删除用户
```

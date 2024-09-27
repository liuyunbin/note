
## 安装及初始化
```

sudo apt install mysql-server  # 1. 安装软件
mysql_secure_installation      # 2. 基本安全设置
                               #   * 配置 root 使用 Linux root 用户认证
                               #   * 禁止 root 远程登录
                               #   * 删除匿名用户
                               #   * 删除测试数据库
# 2. 启动 MySQL 并设置为开机自动启动

sudo systemctl enable     mysql.service # 开机自动启动
sudo systemctl start      mysql.service # 启动服务
sudo systemctl is-active  mysql.service # 查看是否已启动
sudo systemctl is-enabled mysql.service # 查看是否开机自动启动

## 3. 修改编码为 utf8mb4 --- 8.0 及以后的版本不需要修改了
mysql -e "show variables like 'character%';"                     # 1. 查看编码和字符集
mysql -e "show variables like 'collation_%'"                     #
mysql --help --verbose 2> /dev/null | grep -A1 'Default options' # 2. 查看 MySQL 的配置文件
default-character-set = utf8mb4                                  # 3. 修改配置文件中的编码
systemctl restart mysql                                          # 4. 重启 MySQL
mysql -e "show variables like 'character%';"                     # 5. 再次查看编码和字符集
mysql -e "show variables like 'collation_%'"                     #

## 4. 开启防火墙
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-services                 # 5. 再次查看目前开启的服务

## 5. 允许远程访问
ss -tal | grep mysql                                             # 1. 查看 MySQL 是否允许远程访问
mysql --help --verbose 2> /dev/null | grep -A1 'Default options' # 2. 查看 MySQL 的配置文件
bind-address           = 127.0.0.1                               # 3. 注释掉对应的配置
mysqlx-bind-address    = 127.0.0.1                               #
systemctl restart mysql                                          # 4. 重启 MySQL
ss -tal | grep mysql                                             # 5. 再次查看 MySQL 是否允许远程访问
```



## 0. 安装及启动
apt install firewalld                      # 1. 安装
systemctl list-unit-files | grep firewall  # 2. 查看服务名称
systemctl enable  firewalld.service        # 3. 设置开机启动
systemctl start   firewalld.service        # 4. 启动

## 1. 开启防火墙服务
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-services                 # 4. 再次查看目前开启的服务

## 2. 关闭防火墙服务
firewall-cmd --list-services                    # 1. 查看目前开启的服务
firewall-cmd --permanent --remove-service=mysql # 2. 永久移除服务
firewall-cmd --reload                           # 3. 重新加载防火墙
firewall-cmd --list-services                    # 4. 再次查看目前开启的服务

## 3. 开启防火墙端口号
firewall-cmd --list-ports                    # 1. 查看所有打开的端口
firewall-cmd --permanent --add-port=80/tcp   # 2. 永久开启添加端口
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-ports                    # 4. 再次查看所有打开的端口

## 4. 关闭防火墙端口号
firewall-cmd --list-ports                     # 1. 查看所有打开的端口
firewall-cmd --permanent --remove-port=80/tcp # 2. 永久移除端口
firewall-cmd --reload                         # 3. 重新加载防火墙
firewall-cmd --list-ports                     # 4. 再次查看所有打开的端口

## 5. 拒绝所有的包
firewall-cmd --query-panic  # 查看是否拒绝
firewall-cmd --panic-on     # 拒绝所有包
firewall-cmd --query-panic  # 查看是否拒绝

## 6. 取消拒绝所有的包
firewall-cmd --query-panic  # 查看是否拒绝
firewall-cmd --panic-off    # 取消拒绝状态
firewall-cmd --query-panic  # 查看是否拒绝

## 7. 将当前防火墙的规则永久保存
firewall-cmd --runtime-to-permanent

## 8. 查看所有的内容
firewall-cmd --list-all
firewall-cmd --list-all-policies



## 0. 安装及启动
```
sudo apt install firewalld                      # 1. 安装
     systemctl list-unit-files | grep firewall  # 2. 查看服务名称
sudo systemctl enable  firewalld.service        # 3. 设置开机启动
sudo systemctl start   firewalld.service        # 4. 启动
```

## 1. 开启防火墙服务
```
sudo firewall-cmd --list-services                 # 1. 查看目前开启的服务
sudo firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
sudo firewall-cmd --reload                        # 3. 重新加载防火墙
sudo firewall-cmd --list-services                 # 4. 再次查看目前开启的服务
```

## 2. 关闭防火墙服务
```
sudo firewall-cmd --list-services                    # 1. 查看目前开启的服务
sudo firewall-cmd --permanent --remove-service=mysql # 2. 永久移除服务
sudo firewall-cmd --reload                           # 3. 重新加载防火墙
sudo firewall-cmd --list-services                    # 4. 再次查看目前开启的服务
```

## 3. 开启防火墙端口号
```
sudo firewall-cmd --list-ports                    # 1. 查看所有打开的端口
sudo firewall-cmd --permanent --add-port=80/tcp   # 2. 永久开启添加端口
sudo firewall-cmd --reload                        # 3. 重新加载防火墙
sudo firewall-cmd --list-ports                    # 4. 再次查看所有打开的端口
```

## 4. 关闭防火墙端口号
```
sudo firewall-cmd --list-ports                     # 1. 查看所有打开的端口
sudo firewall-cmd --permanent --remove-port=80/tcp # 2. 永久移除端口
sudo firewall-cmd --reload                         # 3. 重新加载防火墙
sudo firewall-cmd --list-ports                     # 4. 再次查看所有打开的端口
```

## 5. 拒绝所有的包
```
sudo firewall-cmd --query-panic  # 查看是否拒绝
sudo firewall-cmd --panic-on     # 拒绝所有包
sudo firewall-cmd --query-panic  # 查看是否拒绝
```

## 6. 取消拒绝所有的包
```
sudo firewall-cmd --query-panic  # 查看是否拒绝
sudo firewall-cmd --panic-off    # 取消拒绝状态
sudo firewall-cmd --query-panic  # 查看是否拒绝
```

## 7. 将当前防火墙的规则永久保存
```
sudo firewall-cmd --runtime-to-permanent
```

## 8. 查看所有的内容
```
sudo firewall-cmd --list-all
sudo firewall-cmd --list-all-policies
```


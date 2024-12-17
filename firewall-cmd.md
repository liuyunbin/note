
## 0. 安装及启动 firewall-cmd
```
apt install firewalld                      # 1. 安装
systemctl list-unit-files | grep firewall  # 2. 查看服务名称
systemctl enable  firewalld.service        # 3. 设置开机启动
systemctl start   firewalld.service        # 4. 启动
```

## 1. 开启防火墙服务
```
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-services                 # 4. 再次查看目前开启的服务
```

## 2. 关闭防火墙服务
```
firewall-cmd --list-services                    # 1. 查看目前开启的服务
firewall-cmd --permanent --remove-service=mysql # 2. 永久移除服务
firewall-cmd --reload                           # 3. 重新加载防火墙
firewall-cmd --list-services                    # 4. 再次查看目前开启的服务
```

## 3. 开启防火墙端口号
```
firewall-cmd --list-ports                    # 1. 查看所有打开的端口
firewall-cmd --permanent --add-port=80/tcp   # 2. 永久开启添加端口
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-ports                    # 4. 再次查看所有打开的端口
```

## 4. 关闭防火墙端口号
```
firewall-cmd --list-ports                     # 1. 查看所有打开的端口
firewall-cmd --permanent --remove-port=80/tcp # 2. 永久移除端口
firewall-cmd --reload                         # 3. 重新加载防火墙
firewall-cmd --list-ports                     # 4. 再次查看所有打开的端口
```

## 5. 拒绝所有的包
```
firewall-cmd --query-panic  # 查看是否拒绝
firewall-cmd --panic-on     # 拒绝所有包
firewall-cmd --query-panic  # 查看是否拒绝
```

## 6. 取消拒绝所有的包
```
firewall-cmd --query-panic  # 查看是否拒绝
firewall-cmd --panic-off    # 取消拒绝状态
firewall-cmd --query-panic  # 查看是否拒绝
```

## 7. 将当前防火墙的规则永久保存
```
firewall-cmd --runtime-to-permanent
```

## 8. 查看所有的内容
```
firewall-cmd --list-all
firewall-cmd --list-all-policies
```

## 9. 设置端口号转发 -- 有问题 -- 可以使用 ssh 端口转发
```
firewall-cmd --list-forward-ports              # 1. 查看端口转发
firewall-cmd --query-masquerade                # 2. 检查是否允许伪装IP
firewall-cmd --permanent --add-port=81/tcp;    # 3. 防火墙开启端口
firewall-cmd --permanent --add-port=8181/tcp;  #
firewall-cmd --permanent --add-masquerade;     # 4. 允许伪装 IP
firewall-cmd --permanent --add-forward-port=port=8181:proto=tcp:toaddr=127.0.0.1:toport=81
                                               # 5. 端口转发
firewall-cmd --reload;                         # 6. 重新加载防火墙
firewall-cmd --list-forward-ports              # 7. 再次查看端口转发
```

## 10. 停止端口号转发
```
firewall-cmd --list-forward-ports              # 1. 查看端口转发
firewall-cmd --query-masquerade                # 2. 检查是否允许伪装IP
firewall-cmd --permanent --remove-masquerade   # 3. 永久禁止防火墙伪装IP
firewall-cmd --permanent --remove-forward-port=port=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 4. 移除端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --reload                          # 5. 重新加载防火墙
firewall-cmd --list-forward-ports              # 6. 再次查看端口转发
```
## 11. 设置端口号转发(rich language) -- 远程访问有问题 -- 可以使用 ssh 端口转发
```
firewall-cmd --permanent --delete-policy=portforward; # 1. 删除旧策略 (可选)
firewall-cmd --permanent --new-policy=portforward;    # 2. 新增新策略
firewall-cmd --permanent --add-port=82/tcp;           # 3. 添加端口号
firewall-cmd --permanent --add-port=8282/tcp;
firewall-cmd --permanent --policy=portforward --add-ingress-zone=HOST; # 4. 设置入口
firewall-cmd --permanent --policy=portforward --add-egress-zone=ANY;   # 5. 设置出口
firewall-cmd --permanent --policy=portforward --add-rich-rule='rule family="ipv4" forward-port port="8282" protocol="tcp" to-port="82" to-addr="127.0.0.1"';            # 6. 设置端口转发
firewall-cmd --reload;                                # 7. 重新加载防火墙
```


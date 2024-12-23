
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

## 9. 端口转发
```
# 1. 测试环境: 三台虚拟机
192.168.198.10 -- 以下简称 host-10
192.168.198.20 -- 以下简称 host-20
192.168.198.30 -- 以下简称 host-30

# 2. 问题
1. host-10 上有服务
2. host-20 可以直接访问 host-10 上的服务
3. host-30 无法直接访问 host-10 上的服务
4. host-30 可以直接访问 host-20

# 3. 基础设置
1. host-10 开启防火墙端口号: sudo firewall-cmd --add-port=1234/tcp;
2. host-10 开启防火墙端口号: sudo firewall-cmd --add-port=4567/tcp;
3. host-10 启动服务: nc -lkv 1234
4. host-20 开启防火墙端口号: sudo firewall-cmd --add-port=4567/tcp;

# 4. 解决一 (在 host-20 上不能访问转发的端口)
1. 在 host-20 上开启端口转发
    1.1 查看端口转发: sudo firewall-cmd --list-forward-ports
    1.2 执行端口转发, 将本机的 4567 端口转发到 host-10 的 1234
        sudo firewall-cmd --add-forward-port=port=4567:proto=tcp:toaddr=192.168.198.10:toport=1234
    1.3 开启伪装 IP: sudo firewall-cmd --add-masquerade
    1.4 此时, 4567 并没有处于监听状态: ss -taln
2. 此时, host-20 上访问失败: nc 192.168.198.20 4567
3. 此时, host-30 上访问成功: nc 192.168.198.20 4567
    host-30 -> host-20:4567
    host-20 -> host-10:1234
4. 在 host-20 上移除端口转发:
    sudo firewall-cmd --remove-forward-port=port=4567:proto=tcp:toaddr=192.168.198.10:toport=1234
5. 在 host-20 上禁止IP伪装: sudo firewall-cmd --remove-masquerade

# 5. 解决二 (在 host-10 上不能访问转发的端口)
1. 在 host-10 上开启端口转发
    1.1 查看端口转发: sudo firewall-cmd --list-forward-ports
    1.2 执行端口转发, 将本机的 4567 端口转发到 host-10 的 1234
        sudo firewall-cmd --add-forward-port=port=4567:proto=tcp:toaddr=192.168.198.10:toport=1234
    1.3 不需要开启伪装 IP
    1.4 此时, 4567 并没有处于监听状态: ss -taln
2. 此时, host-10 上访问失败: nc 192.168.198.10 4567
3. 此时, host-20 上访问成功: nc 192.168.198.10 4567 (实际上是与 1234 相连)
    host-20 -> host-10:1234
4. 在 host-10 上移除端口转发:
    sudo firewall-cmd --remove-forward-port=port=4567:proto=tcp:toaddr=192.168.198.10:toport=1234

# 6. 解决三 rich language -- 只允许 非本机访问 -- 使用 vps 验证
1. sudo firewall-cmd --permanent --delete-policy=portforward; # 1. 删除旧策略 (可选)
2. sudo firewall-cmd --permanent --new-policy=portforward;    # 2. 新增新策略
3. sudo firewall-cmd --permanent --add-port=1234/tcp;         # 3. 添加端口号
4. sudo firewall-cmd --permanent --add-port=4567/tcp;
5. sudo firewall-cmd --permanent --policy=portforward --add-ingress-zone=ANY;  # 4. 设置入口网络访问
6. sudo firewall-cmd --permanent --policy=portforward --add-egress-zone=ANY;   # 5. 设置出口
7. sudo firewall-cmd --permanent --policy=portforward --add-rich-rule='rule family="ipv4" forward-port port="4567" protocol="tcp" to-port="1234" to-addr="144.168.57.124"';     # 6. 设置端口转发
8. sudo firewall-cmd --reload;                            # 7. 重新加载防火墙
9. 启动服务: nc -lkv 1234
10. 此时, 4567 不处于监听状态: ss -taln
11.   本机访问: nc 144.168.57.124 4567 -- 失败
12. 非本机访问: nc 144.168.57.124 4567 -- 成功 (实际上是与 1234 相连)

# 7. 解决三 rich language -- 只允许 非本机访问 -- 使用 vps 验证
1. sudo firewall-cmd --permanent --delete-policy=portforward; # 1. 删除旧策略 (可选)
2. sudo firewall-cmd --permanent --new-policy=portforward;    # 2. 新增新策略
3. sudo firewall-cmd --permanent --add-port=1234/tcp;         # 3. 添加端口号
4. sudo firewall-cmd --permanent --add-port=4567/tcp;
5. sudo firewall-cmd --permanent --policy=portforward --add-ingress-zone=HOST; # 4. 设置入口本机访问
6. sudo firewall-cmd --permanent --policy=portforward --add-egress-zone=ANY;   # 5. 设置出口
7. sudo firewall-cmd --permanent --policy=portforward --add-rich-rule='rule family="ipv4" forward-port port="4567" protocol="tcp" to-port="1234" to-addr="144.168.57.124"';     # 6. 设置端口转发
8. sudo firewall-cmd --reload;                            # 7. 重新加载防火墙
9. 启动服务: nc -lkv 1234
10. 此时, 4567 不处于监听状态: ss -taln
11. 非本机访问: nc 144.168.57.124 4567 -- 成功 (实际上是与 1234 相连)
12.   本机访问: nc 144.168.57.124 4567 -- 失败
```


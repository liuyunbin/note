
## 1. 五台虚拟机
```
192.168.198.10 -- 以下简称 host-10
192.168.198.20 -- 以下简称 host-20
192.168.198.30 -- 以下简称 host-30
192.168.198.40 -- 以下简称 host-40
192.168.198.50 -- 以下简称 host-50
```

## 2. 每台虚拟机上依次执行
```
sudo firewall-cmd --permanent --add-port=1234/tcp; # 1. 开启端口号
sudo firewall-cmd --permanent --add-port=4567/tcp; # 2. 开启端口号
sudo firewall-cmd --reload;                        # 3. 重新加载防火墙
sudo firewall-cmd --list-ports;                    # 4. 查看所有打开的端口
```

## 3. 当前环境
```
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 host-30 是本机机器
* host-20   可以访问 host-10 的服务
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务
```

### 3.1 方案一
```
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
```

### 方案三 rich language -- 使用 vps 验证
```
1. sudo firewall-cmd --permanent --delete-policy=portforward; # 1. 删除旧策略 (可选)
2. sudo firewall-cmd --permanent --new-policy=portforward;    # 2. 新增新策略
3. sudo firewall-cmd --permanent --add-port=1234/tcp;         # 3. 添加端口号
4. sudo firewall-cmd --permanent --add-port=4567/tcp;
5. sudo firewall-cmd --permanent --policy=portforward --add-ingress-zone=ANY;  # 4. 设置入口网络访问
6. sudo firewall-cmd --permanent --policy=portforward --add-egress-zone=ANY;   # 5. 设置出口
7. sudo firewall-cmd --permanent --policy=portforward --add-rich-rule='rule family="ipv4" forward-port port="4567" protocol="tcp" to-port="1234" to-addr="144.168.57.124"';
                                                          # 6. 设置端口转发
8. sudo firewall-cmd --reload;                            # 7. 重新加载防火墙
9. 启动服务: nc -lkv 1234
10. 此时, 4567 不处于监听状态: ss -taln
11.   本机访问: nc 144.168.57.124 4567 -- 失败
12. 非本机访问: nc 144.168.57.124 4567 -- 成功 (实际上是与 1234 相连)
```


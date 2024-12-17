
## ubuntu 24.04 修改 sshd 端口号
```
1. 修改 /usr/lib/systemd/system/ssh.socket 里的 ListenStream
2. 重新加载配置: systemctl daemon-reload
3. 重启服务: systemctl restart ssh.socket
```

## 常用命令
```
密钥登录主目录权限不能是 777

ssh -p port        # 指定服务器端口号
ssh -F             # 指定配置文件
ssh -l lyb 1.2.3.4
ssh    lyb@1.2.3.4
ssh -i ~/.ssh/id_rsa lyb # 指定私钥文件名

ssh-keygen -t rsa              # 指定密钥算法, 默认就是 rsa
ssh-keygen -b 1024             # 指定密钥的二进制位数
ssh-keygen -C username@host    # 指定注释
ssh-keygen -f lyb              # 指定密钥的文件
ssh-keygen -R username@host    # 将 username@host 的公钥移出 known_hosts 文件

ssh-copy-id -i ~/id_rsa username@host # 添加公钥到服务器中的 ~/.ssh/authorized_keys
                                      # -i 未指定时, 将使用 ~/.ssh/id_rsa.pub
```

## ssh 客户端的常见配置
```
~/.ssh/config, /etc/ssh/ssh_config, man ssh_config

Host *                          # 对所有机器都生效, 使用 通配符, 配置直到下一个 host
Host 123                        # 可以起一个别名
HostName 1.2.3.4                # 远程主机
Port 2222                       # 远程端口号
BindAddress 192.168.10.235      # 本地 IP
User lyb                        # 用户名
IdentityFile ~/.ssh/id.rsa      # 密钥文件
                                # 此时, 使用 ssh 123 相当于使用 ssh -p 2222 lyb@1.2.3.4 -i ~/.ssh/id.rsa
DynamicForward 1080             # 指定动态转发端口
LocalForward  1234 1.2.3.4:5678 # 指定本地端口转发
RemoteForward 1234 1.2.3.4:5678 # 指定远程端口转发
```

## 服务端的常见配置
```
/etc/ssh/sshd_config, man sshd_config

AllowTcpForwarding yes     # 是否允许端口转发, 默认允许
ListenAddress 1.2.3.4      # 监听地址
PasswordAuthentication     # 指定是否允许密码登录，默认值为 yes
Port 22                    # 监听端口号
GatewayPorts no            # 远程转发时, 是否允许其他主机使该端口号, 默认不允许
```

## 端口转发
```
# 1. 基础
0. 网络机器: net_a, net_b, net_c
1.   路由器: route
2. 本地机器: host_a, host_b, host_c
3. 本地机器之间可以直接相互连接
4. 网络机器之间可以直接相互连接
5. host_a 通过路由器可以直接访问网络机器
6. 除 host_a 外的本地机器不能通过路由器直接访问网络机器
7. 网络机器不能直接访问本地机器

# 2. 测试一: 除 host_a 外的本地机器如何访问网络机器 (本地端口转发)
在 host_b 上执行: ssh -L host_b_port:net_a_ip:net_a_port host_a_user@host_a_ip
此时, 连接建立的方向: host_b -> host_a -> route -> net_a
此时, 访问 host_b_ip:host_b_port 相当于访问 net_a_ip:net_a_port
在 host_c 上执行: ssh -p host_b_port net_a_user@host_b_ip
相当于: ssh -p net_a_port net_a_user@net_a_ip
数据流的方向: host_c -> host_b -> host_a -> route -> net_a
数据流的方向和连接方向相同

# 3. 测试二: 网络机器如何访问本地机器上的服务 (远程端口转发)
在 host_a 上执行: ssh -R net_a_port:host_b_ip:host_b_port net_a_user@net_a_ip
此时, 连接建立的方向: host_a -> route -> net_a
此时, 访问 net_a_ip:net_a_port 相当于访问 host_b_ip:host_b_port
在 net_b 上执行: ssh -p net_a_port host_b_user@net_a_ip
相当于: ssh -p host_b_port host_b_user@host_b_ip
数据流的方向: net_b -> net_a -> route -> host_a -> host_b
数据流的方向和连接方向相反

# 4. 总结
本地端口转发:
* 现状:
    host_b -> net_a  失败
    host_a -> net_a  成功
    hoat_b -> host_a 成功
    host_a -> host_b 成功或失败
* 目标:
    host_b -> net_a 成功
* 实现:
    在 host_b 执行: ssh -CqTnN -L host_b_port:net_a_ip:net_a_port host_a_user@host_a_ip
    此时, 访问: host_b_ip:host_b_port 相当于访问 net_a_ip:net_a_port

远程端口转发:
* 现状:
    net_a  -> host_a 失败
    host_a -> net_a  成功
* 目标:
    net_a -> host_a 成功
* 实现:
    在 host_a 执行:  ssh -CqTnN -R net_a_port:host_a_ip:host_a_port net_a_user@net_a_ip
    此时, 访问: net_a_ip:net_a_port 相当于访问 host_a_ip:host_a_port
    需要在 net_a 上配置 GatewayPorts

动态端口转发:
* ssh -CqTnN -D host_a_port host_a_user@host_a_ip
* 在 host_a_ip:host_a_port 启动 socks5 服务
```


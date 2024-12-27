
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
AllowTcpForwarding yes     # 是否允许本地端口转发
```

## 端口转发
#### 0. 公共说明
```
# 1. 五台虚拟机
192.168.198.10 -- 以下简称 host-10
192.168.198.20 -- 以下简称 host-20
192.168.198.30 -- 以下简称 host-30
192.168.198.40 -- 以下简称 host-40
192.168.198.50 -- 以下简称 host-50

# 2. 每台虚拟机上依次执行
sudo firewall-cmd --permanent --add-port=1234/tcp; # 1. 开启端口号
sudo firewall-cmd --permanent --add-port=4567/tcp; # 2. 开启端口号
sudo firewall-cmd --reload;                        # 3. 重新加载防火墙
sudo firewall-cmd --list-ports;                    # 4. 查看所有打开的端口

# 3. 允许本地端口转发 -- 需要 root 权限
在 /etc/ssh/sshd_config 内添加配置项: AllowTcpForwarding yes
重启 sshd 服务: sudo systemctl restart sshd;

# 4. 允许远程端口转发 -- 需要 root 权限
在 /etc/ssh/sshd_config 内添加配置项: GatewayPorts yes
重启 sshd 服务: sudo systemctl restart sshd;
```

#### 1. 本地端口转发
```
# 0. 定义
将本机端口的访问, 转发到本机的其他端口 或 其他机器的端口

# 1. 情景一: 内网访问外网
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 host-30 是本机机器
* host-20   可以访问 host-10 的服务
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务

方案一
1. 在 host-20 上设置允许本地端口转发
2. 在 host-20 上执行: ssh -CqTnNf -L 0.0.0.0:4567:host-10:1234 lyb@host-20
    将本机的 4567 端口号的数据, 转发到 host-10 的 1234 端口号
    此时, host-20 和 host-20:22 建立了连接
    此时, 本机的 4567 端口处于监听状态: ss -taln
3. host-30 连接 host-20 的 4567 端口号: nc host-20 4567
    此时, host-30 和 host-20:4567 端口号建立了连接
    此时, host-20 和 host-10:1234 端口号建立了连接
    此时, host-10:1234 收到 host-20 的数据
    建立端口转发: host-20 -> host-10
    数据流: host-30 -> host-20:4567 (明文, 跨机器)
            host-20 -> host-20:22   (已使用 ssh 加密) (设置端口转发时已建立好的)
            host-20 -> host-10:1234 (已使用 ssh 加密)
    建立连接和数据流的方向是一致的

方案二
1. 在 host-20 上设置允许本地端口转发
2. 在 host-30 上执行: ssh -CqTnNf -L 0.0.0.0:4567:host-10:1234 lyb@host-20
    将本机的 4567 端口号的数据, 经由 host-20, 转发到 host-10 的 1234 端口号
    此时, host-30 和 host-20:22 建立了连接
    此时, 本机的 4567 端口处于监听状态: ss -taln
3. host-30 连接 host-30 的 4567 端口号: nc host-30 4567
    此时, host-30 和 host-30:4567 端口号建立了连接
    此时, host-20 和 host-10:1234 端口号建立了连接
    此时, host-10:1234 收到 host-20 的数据
    建立端口转发: host-30 -> host-20 -> host-10
    数据流: host-30 -> host-30:4567 (明文, 本机器)
            host-30 -> host-20:22   (已使用 ssh 加密) (设置端口转发时已建立好的)
            host-20 -> host-10:1234 (已使用 ssh 加密)
    建立连接和数据流的方向是一致的

# 2. 情景二: 穿越防火墙
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 是网络机器
* host-30 是本机机器
* host-30   可以访问 host-20
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务

方案同上
```

#### 2. 远程端口转发
```
# 0. 定义
将远程端口的访问, 转发到本机的其他端口 或 其他机器的端口

# 1. 情景一: 外网访问内网
* host-10 host-20 是网络机器
* host-30 是本地机器, 运行的服务: nc -lkv 1234
* host-30   可以访问 host-10 host-20
* host-10 host-20 不可以访问 host-30
* 问: host-10 host-20 如何访问 host-30 的服务

方案一:
1. 在 host-20 上设置允许远程端口转发 -- 如果只是本机访问的话, 不需要设置
2. 在 host-30 执行: ssh -CqTnNf -R 0.0.0.0:4567:host-30:1234 lyb@host-20
    将 host-20 的 4567 端口号的数据, 经由 host-30 转发到 host-30 的 1234 端口号
    此时, host-30 和 host-20:22 建立了连接
    此时, host-20 上的 4567 处于监听状态: ss -taln
3. host-10 连接 host-20 的 4567 端口号: nc host-20 4567
    此时, host-10 和 host-20:4567 端口号建立了连接
    此时, host-30 和 host-30:1234 端口号建立了连接
    此时, host-30:1234 收到 host-30 的数据
    建立端口转发: host-30 -> host-20
    数据流: host-10    -> host-20:4567 (明文, 跨机器)
            host-20:22 -> host-30      (已使用 ssh 加密) (设置端口转发时已建立好的)
            host-30    -> host-30:1234 (已使用 ssh 加密)
    建立连接和数据流的方向是相反
4. host-20 连接 host-20 的 4567 端口号: nc host-20 4567
    和上面类似, 但 host-20 -> host-20:4567 (明文, 本机器)
```

#### 3. 动态端口转发
```
# 0. 定义
使用 socks 协议, 不明确转发的端口号, 由客户端指定

# 1. 情景一: 穿越防火墙
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 是网络机器
* host-30 是本机机器
* host-30   可以访问 host-20
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务

方案一
1. 在 host-20 上开启动态端口转发: ssh -CqTnNf -D 0.0.0.0:4567 host-20
2. 在 host-30 上执行: nc --proxy host-20:4567 --proxy-type socks4  host-10 1234
    数据流: host-30 -> host-20:4567 -> host-20 -> host-10:1234
    host-30 -> host-20:4567 是跨机器的明文

方案二
1. 在 host-30 上开启动态端口转发: ssh -CqTnNf -D 0.0.0.0:4567 host-20
2. 在 host-30 上执行: nc --proxy host-30:4567 --proxy-type socks4  host-10 1234
    数据流: host-30 -> host-30:4567 -> host-20 -> host-10:1234
    host-30 -> host-30:4567 是本机器的明文
```


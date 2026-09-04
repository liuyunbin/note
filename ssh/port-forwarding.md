
## 1. 公共说明
### 1.1 五台虚拟机
```
192.168.198.10 -- 以下简称 host-10
192.168.198.20 -- 以下简称 host-20
192.168.198.30 -- 以下简称 host-30
192.168.198.40 -- 以下简称 host-40
192.168.198.50 -- 以下简称 host-50
```

### 1.2 每台虚拟机上依次执行
```
sudo firewall-cmd --permanent --add-port=1234/tcp; # 1. 开启端口号
sudo firewall-cmd --permanent --add-port=4567/tcp; # 2. 开启端口号
sudo firewall-cmd --reload;                        # 3. 重新加载防火墙
sudo firewall-cmd --list-ports;                    # 4. 查看所有打开的端口
```

### 1.3 允许本地端口转发 -- 需要 root 权限
```
在 /etc/ssh/sshd_config 内添加配置项: AllowTcpForwarding yes
重启 sshd 服务: sudo systemctl restart sshd;
```

### 1.4 允许远程端口转发 -- 需要 root 权限
```
在 /etc/ssh/sshd_config 内添加配置项: GatewayPorts yes
重启 sshd 服务: sudo systemctl restart sshd;
```

## 2. 本地端口转发
### 2.1 定义
```
将本机端口的访问, 转发到本机的其他端口 或 其他机器的端口
```

### 2.2 情景一: 内网访问外网
```
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 host-30 是本机机器
* host-20   可以访问 host-10 的服务
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务
```

#### 2.2.1 方案一
```
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
```

#### 2.2.2 方案二
```
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
```

### 2.3 情景二: 穿越防火墙
```
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 是网络机器
* host-30 是本机机器
* host-30   可以访问 host-20
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务

方案同上
```

## 3. 远程端口转发
### 3.1 定义
```
将远程端口的访问, 转发到本机的其他端口 或 其他机器的端口
```

### 3.2 情景一: 外网访问内网
```
* host-10 host-20 是网络机器
* host-30 是本地机器, 运行的服务: nc -lkv 1234
* host-30   可以访问 host-10 host-20
* host-10 host-20 不可以访问 host-30
* 问: host-10 host-20 如何访问 host-30 的服务
```

### 3.2.1 方案一:
```
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

## 4. 动态端口转发
### 4.1 定义
```
使用 socks 协议, 不明确转发的端口号, 由客户端指定
```

### 4.2 情景一: 穿越防火墙
```
* host-10 是网络机器, 运行的服务: nc -lkv 1234
* host-20 是网络机器
* host-30 是本机机器
* host-30   可以访问 host-20
* host-30 不可以访问 host-10 的服务, 但可以访问 host-20
* 问: host-30 如何访问 host-10 的服务
```

#### 4.2.1 方案一
```
1. 在 host-20 上开启动态端口转发: ssh -CqTnNf -D 0.0.0.0:4567 host-20
2. 在 host-30 上执行: nc --proxy host-20:4567 --proxy-type socks4  host-10 1234
    数据流: host-30 -> host-20:4567 -> host-20 -> host-10:1234
    host-30 -> host-20:4567 是跨机器的明文
```

#### 4.2.2 方案二
```
1. 在 host-30 上开启动态端口转发: ssh -CqTnNf -D 0.0.0.0:4567 host-20
2. 在 host-30 上执行: nc --proxy host-30:4567 --proxy-type socks4  host-10 1234
    数据流: host-30 -> host-30:4567 -> host-20 -> host-10:1234
    host-30 -> host-30:4567 是本机器的明文
```


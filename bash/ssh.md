
### 密钥登录
主目录权限不能是 777

### 常用命令
```
ssh -N -D A_PORT B_IP
            # 功能:
            #   动态端口转发
            #   将本地到 A_PORT 的请求转发到 B_IP
            #   使用 SOCKS5 协议
ssh -N -L A_PORT:C_IP:C_PORT B_IP
            # 功能:
            #   本地端口转发
            # 目标:
            #    A_IP:A_PORT --> C_IP:C_PORT
            # 现状:
            #    A_IP --> C_IP 失败
            #    B_IP --> C_IP 成功
            #    A_IP --> B_IP 成功
            #    B_IP --> A_IP 成功 或 失败都行
            # 实现:
            #   * 在 A_IP 机器上执行: ssh -N -L A_PORT:C_IP:C_PORT B_IP
            #   * 发往 A_IP 机器的端口号 A_PORT 的请求, 经由 B_IP 机器, 转发到 C_IP 机器的 C_PORT 端口
            #   * 即: A_IP:A_PORT --> B_IP --> C_IP:C_PORT
ssh -N -R A_PORT:C_IP:C_PORT A_IP
            # 功能:
            #   远程端口转发
            # 目标:
            #    A_IP:A_PORT --> C_IP:C_PORT
            # 现状:
            #    A_IP --> C_IP 失败
            #    B_IP --> C_IP 成功
            #    A_IP --> B_IP 成功 或 失败都行
            #    B_IP --> A_IP 成功
            # 实现:
            #   * 在 B_IP 机器上执行: ssh -N -R A_PORT:C_IP:C_PORT A_IP
            #   * 发往 A_IP 机器的端口号 A_PORT 的请求, 经由 B_IP 机器, 转发到 C_IP 机器的 C_PORT 端口
            #   * 即: A_IP:A_PORT --> B_IP --> C_IP:C_PORT
            #   * 如果要支持其他主机通过 A_IP 访问 C_IP, 需要在 A_IP 的 ssh 配置 GatewayPorts
ssh -N             # 不登录 shell, 只用于端口转发
ssh -p port        # 指定服务器端口号
ssh -f             # 在后台运行
ssh -t             # 开启交互式 shell
ssh -C             # 压缩数据
ssh -F             # 指定配置文件
ssh -q             # 不输出任何警告信息
ssh -l lyb 1.2.3.4
ssh        1.2.3.4
ssh    lyb@1.2.3.4
ssh -i ~/.ssh/id_rsa lyb # 指定私钥文件名

ssh-keygen -t rsa              # 指定密钥算法, 默认就是 rsa
ssh-keygen -b 1024             # 指定密钥的二进制位数
ssh-keygen -C username@host    # 指定注释
ssh-keygen -f lyb              # 指定密钥的文件
ssh-keygen -R username@host    # 将 username@host 的公钥移出 known_hosts 文件

ssh-copy-id -i ~/id_rsa username@host # 添加公钥到服务器中的 ~/.ssh/authorized_keys
                                      # -i 未指定时, 将使用 ~/.ssh/id_rsa.pub

#### ssh 客户端的常见配置: ~/.ssh/config, /etc/ssh/ssh_config, man ssh_config
Host *                          # 对所有机器都生效, 使用 通配符, 配置直到下一个 host
Host 123                        # 可以起一个别名
HostName 1.2.3.4                # 远程主机
Port 2222                       # 远程端口号
BindAddress 192.168.10.235      # 本地 IP
User lyb                        # 用户名
IdentityFile ~/.ssh/id.rsa      # 密钥文件
                                # 此时, 使用 ssh 123 相当于使用 ssh -p 2222 lyb@1.2.3.4
DynamicForward 1080             # 指定动态转发端口
LocalForward  1234 1.2.3.4:5678 # 指定本地端口转发
RemoteForward 1234 1.2.3.4:5678 # 指定远程端口转发

#### ssh 服务端的常见配置: /etc/ssh/sshd_config, man sshd_config
AllowTcpForwarding yes     # 是否允许端口转发, 默认允许
ListenAddress 1.2.3.4      # 监听地址
PasswordAuthentication     # 指定是否允许密码登录，默认值为 yes
Port 22                    # 监听端口号
GatewayPorts no            # 远程转发时, 是否允许其他主机使改端口号, 默认不允许
```


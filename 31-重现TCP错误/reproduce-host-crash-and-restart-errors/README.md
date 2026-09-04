
#### 简介
重现主机崩溃后重启的情况

#### 模拟服务器主机崩溃后重启：
01. 调用 `system("sudo ip addr add 192.168.1.100/8 dev enp2s0");` 添加服务器的 IP
02. 调用 `system("sudo ip addr add 192.168.1.200/8 dev enp2s0");` 添加客户端的 IP
03. 调用 `socket()` `bind()` 绑定服务器 IP
04. 调用 `listen()` 启动服务器，使其处于监听状态
05. 调用 `socket()` `bind()` 绑定客户端 IP
06. 调用 `connect()` 连接服务器
07. 调用 `accept()` 接受客户端的连接
08. 调用 `system("sudo ip addr del 192.168.1.100/8 dev enp2s0");` 删除服务器的 IP 模拟服务器主机崩溃
09. 调用 `close()` 关闭服务器的已连接 socket
10. 调用 `close()` 关闭服务器的监听 socket
11. 调用 `system("sudo ip addr add 192.168.1.100/8 dev enp2s0");` 添加服务器的 IP 模拟服务器主机重启
12. 客户端调用 `write()` 将返回成功
13. 客户端调用 `read()`，将返回错误
14. 调用 `system("sudo ip addr del 192.168.1.100/8 dev enp2s0");` 删除服务器的 IP
15. 调用 `system("sudo ip addr del 192.168.1.200/8 dev enp2s0");` 删除客户端的 IP

代码见 [reproduce-host-crash-and-restart-errors](./reproduce-host-crash-and-restart-errors.cc)

#### 分析： 
1. 当对端主机崩溃时，对端已发不出任何消息，重启后，
2. 如果本端调用 `read()` 将阻塞
3. 如果本端调用 `write()` 将返回成功，本端内核尝试发送数据时，但由于对端主机已崩溃后重启，之前所有的连接信息都丢失了，所以对端内核将向本端内核发送 `RST`
    1. **在此之后** ，如果本端继续 `write()` ，本端内核将向本端进程发送 `SIGPIPE`，给信号的默认行为为结束进程，如果忽略该信号 或 捕获该信号而不退出，`write()` 将返回 `EPIPE` 错误
    2. 如果调用 `read()`，将返回 `ECONNRESET` 错误

#### 解决：
1. 忽略 `SIGPIPE` 信号，检测每一个 `read()` `write()` 的返回值
2. 设置一个读超时


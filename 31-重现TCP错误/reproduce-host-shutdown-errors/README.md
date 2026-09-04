
#### 重现主机关机的情况：

#### 模拟服务器主机关机：
01. 调用 `system("sudo ip addr add 192.168.1.100/8 dev enp2s0");` 添加服务器的 IP
02. 调用 `system("sudo ip addr add 192.168.1.200/8 dev enp2s0");` 添加客户端的 IP
03. 调用 `socket()` `bind()` 绑定服务器 IP
04. 调用 `listen()` 启动服务器，使其处于监听状态
05. 调用 `socket()` `bind()` 绑定客户端 IP
06. 调用 `connect()` 连接服务器
07. 调用 `accept()` 接受客户端的连接
08. 调用 `close()` 关闭服务器的已连接 socket
09. 调用 `close()` 关闭服务器的监听 socket
10. 调用 `system("sudo ip addr del 192.168.1.100/8 dev enp2s0");` 删除服务器的 IP，8、9、10 三步共同模拟服务器主机关机
11. 客户端调用 `read()` 将返回 `0`
12. 客户端再次调用 `read()` 也将返回 `0`
13. 客户端调用 `write()` 将返回成功，重复它，直到返回错误
14. 调用 `system("sudo ip addr del 192.168.1.200/8 dev enp2s0");` 删除客户端的 IP

代码见 [reproduce-host-shutdown-errors](./reproduce-host-shutdown-errors.cc)

#### 分析： 
1. 当对端关机时，对端进程将关闭所有的 socket，导致 TCP 四次挥手的前两次正常完成 或 FIN 成功发送
2. 当本端 `read()` 时，由于已经收到 `FIN`，所以 `read()` 返回 `0`
3. 当本端 `write()` 时，将返回成功，本端内核尝试发送数据时，但由于对端已关机，最终将导致 `ETIMEDOUT` 或 `ENETUNREACH` 或 `EHOSTUNREACH` 错误，**在此之后** ，如果本端继续 `write()` 将返回上述错误，**在此之后** ，如果本端继续 `write()` ，本端内核将向本端进程发送 `SIGPIPE`，给信号的默认行为为结束进程，如果忽略该信号 或 捕获该信号而不退出，`write()` 将返回 `EPIPE` 错误

#### 解决：
忽略 `SIGPIPE` 信号，检测每一个 `read()` `write()` 的返回值


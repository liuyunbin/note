
#### 重现对端进程崩溃的情况：

#### 模拟服务器进程崩溃：
1. 调用 `socket()` `bind()` `listen()` 启动服务器，使其处于监听状态
2. 调用 `socket()` `connect()` 连接服务器
3. 调用 `accept()` 接受客户端的连接
4. 调用 `close()` 关闭服务器的已连接 socket，模拟服务器进程崩溃
5. 调用 `close()` 关闭服务器的监听 socket
6. 客户端调用 `read()` 将返回 `0`
7. 客户端再次调用 `read()` 也将返回 `0`
8. 客户端调用 `write()` 将返回成功，重复它，直到返回错误

代码见 [reproduce-process-crash-errors](./reproduce-process-crash-errors.cc)

#### 分析： 
1. 当对端进程崩溃时，对端进程将关闭所有的 socket，导致 TCP 四次挥手的前两次正常完成
2. 当本端 `read()` 时，由于已经收到 `FIN`，所以 `read()` 返回 `0`
3. 当本端 `write()` 时，将返回成功，但由于对端相应的 socket 已经关闭，所以对端内核将向本端内核发送 `RST`，**在此之后** ，如果本端继续 `write()` ，本端内核将向本端进程发送 `SIGPIPE`，给信号的默认行为为结束进程，如果忽略该信号 或 捕获该信号而不退出，`write()` 将返回 `EPIPE` 错误

#### 解决：
忽略 `SIGPIPE` 信号，检测每一个 `read()` `write()` 的返回值


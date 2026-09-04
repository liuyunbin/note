
#### 简介
重现 `bind()` 常见错误：

#### 错误类型一：`EACCES`
如果服务器要绑定的端口号位于 `[1, 1024)`，却用普通权限启动，会导致此错误

#### 错误类型二：`EADDRINUSE`
情况一：
1. 启动服务器，等待客户端的连接
2. 客户端到来以后，服务器 `fork()` 子进程处理与客户端的连接，父进程退出
3. 再次启动服务器，会导致该错误

原因：
* 由于此 IP 和 端口号，已有已连接套接字在运行，所以 `bind()` 失败

模拟如下:
1. 调用 `socket()` `bind()` `listen()` 启动服务器，使其处于监听状态
2. 调用 `socket()` `connect()` 连接服务器
3. 调用 `accept()` 接受客户端的连接
4. 调用 `close()` 关闭服务器的监听 socket
5. 调用 `socket()` `bind()` 尝试绑定相同的 IP 和 端口号，发现错误
6. 调用 `close()` 关闭客户端的 socket，避免服务器处于 `TIME_WAIT` 状态

代码见 [reproduce-bind-errors-01](./reproduce-bind-errors-01.cc)

解决方法：
* 设置 socket 选项 `SO_REUSEADDR`

情况二：
1. 启动服务器，等待客户端的连接
2. 客户端到来以后，服务器与客户端的连接，然后服务器主动退出，使其处于 `TIME_WAIT`
3. 再次启动服务器，会导致该错误

原因：
* 由于此 IP 和 端口号处于 `TIME_WAIT`，所以 `bind()` 失败

模拟如下:
1. 调用 `socket()` `bind()` `listen()` 启动服务器，使其处于监听状态
2. 调用 `socket()` `connect()` 连接服务器
3. 调用 `accept()` 接受客户端的连接
4. 调用 `close()` 关闭服务器的 已连接 socket，使其处于 `TIME_WAIT` 状态
5. 调用 `close()` 关闭服务器的监听 socket
6. 调用 `close()` 关闭客户端的 socket
7. 调用 `socket()` `bind()` 尝试绑定相同的 IP 和 端口号，发现错误

代码见 [reproduce-bind-errors-02](./reproduce-bind-errors-02.cc)

解决方法：
* 设置 socket 选项 `SO_REUSEADDR`

情况三：
1. 启动服务器，等待客户端的连接
2. 换一终端，再次启动服务器，会导致该错误

原因：
* 由于此服务器已启动，所以 `bind()` 失败

模拟如下:
1. 调用 `socket()` `bind()` `listen()` 启动服务器，使其处于监听状态
2. 调用 `socket()` `bind()` 尝试绑定相同的 IP 和 端口号，发现错误

代码见 [reproduce-bind-errors-03](./reproduce-bind-errors-03.cc)

解决方法：
* 设置 socket 选项 `SO_REUSEPORT` 此选项允许两个服务器绑定完全相同的 ip 和 port 或 port 相同 而 某一 ip 为通配的情况，
在多进程或多线程中使用，可以在内核处实现负载均衡

有关 `SO_REUSEADDR` 和 `SO_REUSEPORT` 的讨论见 
<https://stackoverflow.com/questions/14388706/socket-options-so-reuseaddr-and-so-reuseport-how-do-they-differ-do-they-mean-t>


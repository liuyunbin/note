
#### 简介
重现 `connect()` 常见错误：

#### 错误一：`ECONNREFUSED`
如果服务器主机可以找到，但没有所请求的服务在运行，服务器内核会向客户端内核发送 `RST`，`connect()` 将返回 `ECONNREFUSED`

#### 错误二：`ETIMEDOUT` 或 `ENETUNREACH`
如果服务器主机也找不到，`connect()` 将返回 `ETIMEDOUT` 或 `ENETUNREACH`

代码见 [reproduce-connect-errors](./reproduce-connect-errors.cc)

#### 非阻塞 `connect()` 的使用方法：
1. 创建非阻塞套接字
2. 调用 `connect()`, 
3. 如果返回 `0`，说明直接连接成功，否则，
4. 如果错误类型不为 `EINPROGRESS` 说明连接失败，
5. 如果错误类型为   `EINPROGRESS` 说明三次握手还未完成，
6. 监测该套接字可写，并将其加入 `epoll`，
7. 当该套接字可写时，使用 `getsockopt()` 检测错误状态，若无错误，则连接成功，否则连接失败

代码见 [how-to-use-nonblock-connect](./how-to-use-nonblock-connect.cc)


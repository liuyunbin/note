
## socket 选项
```
SO_BROADCAST -- 广播
SO_KEEPALIVE -- 保持连接
SO_LINGER ----- close() 之后的内核行为
SO_RCVBUF ----- 接收缓冲区
SO_SNDBUF ----- 发送缓冲区
SO_RCVLOWAT --- 接收低水位值
SO_SNDLOWAT --- 发送低水位值
SO_RCVTIMEO --- 接收超时
SO_SNDTIMEO --- 发送超时
SO_REUSEADDR
    * 通用 IP + 端口号 已绑定时, 不能再 bind() 其他的 IP + 此端口号
    * 端口号 已有连接时, 仍可以 bind()
    * 端口号处于 TIME_WAIT 仍可以 bind()
SO_REUSEPORT -- 允许使用完全相同的绑定, 内核实现负载均衡

TCP_MAXSEG ---- 最大分节大小
TCP_NODELAY --- 禁止 Nagle 算法

IP_TTL -------- TTL 大小
```

## 服务器
1. 迭代服务器
2. 每个客户生成一个进程
3. 每个客户生成一个线程
4. 非阻塞 IO + IO 复用
5. 进程池
6. 线程池


## 目录
* [重现 TCP 错误](./reproduce-tcp-errors)
* [模拟 muduo 的日志库](./tiny-log)
* [模拟 muduo 的网络库](./tiny-net)


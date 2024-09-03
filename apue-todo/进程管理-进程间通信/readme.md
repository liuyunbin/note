
# 计算机操作系统-进程间通信
## 管道(pipe)
* 一般是半双工的
* 需要有公共的父进程
* popen() pclose()
    * 新建管道
    * fork() 子进程
    * 执行命令
    * 单方向
* 协同进程:
    * 两个方向

## 命名管道
* 一般是半双工的
* 任意进程都可以

## 域套接字
* 全双工
* 任意进程都可以

## 消息队列

## 信号量
* 命名信号量
    * `sem_open()` ------ 打开或创建信号量
    * `sem_close()` ----- 关闭信号量
    * `sem_unlink()` ---- 销毁信号量
    * `sem_wait()` ------ 信号量减一
    * `sem_post()` ------ 信号量加一
* 匿名信号量
    * `sem_init()` ------ 初始化
    * `sem_destroy()` --- 删除
    * `sem_getvalue()` -- 获取信号量的值

## 共享内存
* mmap
* munmap

## 网络套接字
* int socket(int domain, int type, int protocol)
    * domain
        * AF_INET ----- IPv4
        * AF_INET6 ---- IPv6
        * AF_UNIX ----- unix 域 socket
    * type
        * SOCK_STREAM ----- 面向连接的, 可靠的, 有序的, 双向的字节流(TCP)
        * SOCK_DGRAM ------ 固定长度的, 无连接的, 不可靠的数据报协议(UDP)
        * SOCK_SEQPACKET -- 面向连接的, 可靠的, 有序的, 双向的, 固定长度的字节流
        * SOCK_RAW -------- 原始 socket -- 可用于 ICMP
        * SOCK_NONBLOCK --- 非阻塞
        * SOCK_CLOEXEC ---- exec 时关闭
    * protocol
        * IPPROTO_TCP
        * IPPROTO_UDP
        * IPPROTO_ICMP
* shutdown: 可选择只关闭读或写, 无论引用计数是多少
* htonl: 主机字节序 -> 网络字节序
* htons: 主机字节序 -> 网络字节序
* ntohl: 网络字节序 -> 主机字节序
* ntohs: 网络字节序 -> 主机字节序
* `inet_ntop`: IP地址 二进制 -> 字符串
* `inet_pton`: IP地址 字符串 -> 二进制
* bind: IP地址和socket绑定
* listen
* connect ------ 不能重用, 报错后必须重新新建
* getsockname -- 查看本地 socket 的地址
* getpeername -- 查看对方 socket 的地址
* accept
* send ------ 发送数据, 可指定非阻塞
* sendto ---- 发送数据, 可指定非阻塞以及对方的地址
* sendmsg --- 发送数据, 可使用多个缓冲区
* recv ------ 接收数据, 可指定非阻塞或等待所有数据, 或只是查看下一数据
* recvfrom -- 接收数据, 可指定非阻塞或等待所有数据, 或只是查看下一数据, 或指定对方地址
* recvmsg --- 接收数据, 可使用多个缓冲区
* setsockopt
    * 接收缓冲区大小
    * 发送缓冲区大小
    * 触发读的最小字节数
    * 触发写的最小字节数
    * keep-alive
    * TCP 慢启动
    * 是否允许重用 bind() 的地址
    * 接收的超时时间


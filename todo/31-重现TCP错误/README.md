
#### 简介：
重新 TCP 常见错误

#### 注意：
* 本文只考虑阻塞 IO

#### 目录：
1. [重现 bind() 错误](./reproduce-bind-errors)
2. [重现 connect() 错误](./reproduce-connect-errors)
3. [重现对端进程崩溃的情况](./reproduce-process-crash-errors)
4. [重现对端主机关机的情况](./reproduce-host-shutdown-errors)
5. [重现对端主机崩溃 或 网络不可达的情况](./reproduce-host-crash-errors)
6. [重现对端主机崩溃后重启的情况](./reproduce-host-crash-and-restart-errors)

#### 其它问题：本项目未考虑发送缓冲区已满 或 接收缓冲区还有数据的情况
1. 当发送缓冲区已满时，尝试 `write()` 将阻塞，直到发送缓冲区有足够的空间存储数据 或 发生错误
2. 当接收缓冲区还有数据时，尝试 `read()` 将先处理接收缓冲区数据，再处理其它情况

#### 参考资源：
* [unix 网络编程](https://book.douban.com/subject/1500149/)


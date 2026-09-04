## 刘云宾的简历

### 个人基本信息
* 刘云宾 男
* 本科 太原理工大学（211） 计算机科学与技术
* 手机：18334706067
* 邮箱：yunbinliu@outlook.com
* GitHub：[github.com/liuyunbin](https://github.com/liuyunbin)
* 期望城市：北京

### 项目经历
#### 学习了 陈硕的网络实践课，见：[github.com/liuyunbin/learn-unp](https://github.com/liuyunbin/learn-unp)
* 实现了 ttcp，用于测试 TCP 的性能，输出服务器的 带宽 和 吞吐量
* 模拟了多机数据处理，主要利用 socket 通信，模拟解决求取大量数据的平均数 和 中位数 等等

#### 重现了 TCP 的常见错误，见：[github.com/liuyunbin/reproduce-tcp-errors](https://github.com/liuyunbin/reproduce-tcp-errors)
* 重现了 程序启动时，端口 权限 或 被占用的情况
* 重现了 客户端连接时，服务端不存在 或 不可达的情况
* 重现了 客户端连接成功后，对端 不可达，崩溃，关机 以及 之后重启的情况

#### 实现了部分 Linux 命令，见：[github.com/liuyunbin/linux-commands](https://github.com/liuyunbin/linux-commands)
* 实现了 bash，使用 dup2() 使其支持管道和重定向
* 实现了 more，使用 /dev/tty，使其任何时候都可以从终端读入控制，使用 tcgetattr() 和 tcsetattr() 设置终端不回显和无缓冲

#### 实现了简单的 STL，见：[github.com/liuyunbin/cpp-standard-library](https://github.com/liuyunbin/cpp-standard-library)
* 实现了 常见容器和适配器，例如：vector，list，deque，stack，queue 等等
* 实现了 常见算法，包括 头文件 algorithm，numeric
* 实现了 头文件 `type_traits` 的部分内容

#### 阅读了开源项目 Tinyhttpd，见：[github.com/liuyunbin/Tinyhttpd](https://github.com/liuyunbin/Tinyhttpd)
* 了解了该 HTTP 服务器的调用过程
* 解决了 多线程直接有共享数据，可能会出现的竟态问题

### 其它方面
给 Nginx 提过一个小的 Bug，见：[github.com/nginx/nginx/commit/f09eae2a7586c5149fe7eaa497c8ff1be684270f](https://github.com/nginx/nginx/commit/f09eae2a7586c5149fe7eaa497c8ff1be684270f)


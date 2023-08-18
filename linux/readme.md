
## 函数和命令需要考虑的问题
```
1. 如何处理符号链接
2. 函数是用使用字符串, 还是文件描述符, 还是 FILE*
3. 函数是否可以指定在某一目录下使用
4. 文件名称建议: 由大小写字母 数字 短横线(-) 下横线(_) 点(.) 构成
```

## 文件属性
```
   stat() -- 文件, 使用文件名称
  fstat() -- 文件, 使用文件描述符
  lstat() -- 文件, 使用符号链接本身的信息
fstatat() -- 文件, 使用文件名称, 使用文件描述符指定目录

* 文件信息(stat)
*
```

## 文件管理
* 文件类型
* 文件所属的用户和组(chown)
* 文件权限(chmod)
    * 读, 写, 执行
    * 在目录下新增或删除文件时, 至少拥有此目录的写和执行权限
    * SUID
        * 二进制文件: 程序的执行者拥有程序所有者的权限
        * 其他文件没意义
    * SGID
        * 二进制文件: 程序的执行者拥有程序所属组的权限
        * 目录: 新增的文件所属的组是此目录所属的组
        * 其他文件没意义
    * SBIT
        * 目录: 此目录下的内容只有文件所有者 或 目录所有者 或 root 用户才能删除
        * 其他文件没意义
    * 权限判断:
        * 依次判断所属用户, 所属组和其他权限
        * 前者失败时, 不判断后者
        * 假如 1.cc 的权限为 0070,
        * 所属主无权限, 所属组有权限时,
        * 对所属主也将判断为无权限
* 文件时间(touch)
    * atime: 内容访问时间, 更新可能不及时
    * mtime: 内容修改时间
    * ctime: 状态修改时间, 包括 内容 名称 权限 所属者 所属组
    * utimes(): 修改内容访问时间, 内容修改时间; 状态修改时间不能修改
* 新建目录
    * mkdir ...... 创建单层目录, 存在时报错
    * mkdir -p ... 递归创建目录, 存在时不报错
* 删除目录
    * rm -r ...... 递归删除
    * rm -rf ..... 强行删除, 文件不存在时, 忽略
* 新建临时文件(mktemp)
* 新建临时目录(mktemp -d)
* 查看目录
    * opendir() ---- 打开目录(文件名称)
    * fdopendir() -- 打开目录(文件描述符)
    * readdir() ---- 读目录
    * closedir() --- 关闭目录
    * chdir() ------ 修改当前目录(目录名称)
    * fchdir() ----- 修改当前目录(文件描述符)
    * getcwd() ----- 获取当前目录
* link()  -- 增加硬链接的引用计数
* unlink() -- 减少硬链接的引用计数, 有进程打开该文件时, 不会删除
* symlink() -- 新建符号链接
* readlink() -- 读取符号链接
* access() -- 以实际用户测试权限, 一般以有效用户测试
* umask() --- 新建文件时, 权限的屏蔽位
* truncate() -- 文件截断
* remove() -- 删除硬链接 或 目录
* rename() -- 重命名

## 不带缓冲的 IO
```
open() --- 打开文件, 原子操作
openat() --- 在某个目录下打开文件, 原子操作
close() -- 关闭文件, 原子操作
read() --- 读文件
write() -- 写文件
lseek() -- 移动文件偏移量, 可能生产空洞, 空洞不占磁盘空间
dup2() --- 复制文件描述符
fcntl()
    * 复制文件描述符(包括 exec 时, 是否关闭)
    * 查看和设置文件描述符(exec 时, 是否关闭)
    * 查看和设置文件状态标志(读写添加等等)
    * 异步属性
    * 文件锁
ioctl() -- 主要处理终端


umask() -- 屏蔽字

     chmod()
    fchmod()
    fchmodat()

    chown()
    fchown()
    fchownat()
    lchown()




rename() -- 重命名
remove() -- 减少硬链接

syslink() --- 新建符号链接
readlink() -- 读取符号链接

futimes() -- 修改文件时间
lutimes() -- 修改文件时间
utimes() --- 修改文件时间


mkdir()
rmdir()
opendir()
readdir()
closedir()



```

## 带缓冲的 IO
```
```

## 用户和组相关
```
getuid() ----- 获取进程的 实际用户 RUID
geteuid() ---- 获取进程的 有效用户 EUID
getgid() ----- 获取进程的 实际组   RGID
getegid() ---- 获取进程的 有效组   EGID

getpwuid() --- uid       --> 用户信息
getpwnam() --- username  --> 用户信息
getgrgid() --- gid       --> 组信息
getgrnam() --- groupname --> 组信息

getcwd() --- 当前目录
getwd()
get_current_dir_name()

chdir() ----- 修改当前目录
fchdir() ----

getrlimit()
setrlimit()

tcgetattr -- 获取终端属性
tcsetattr -- 设置终端属性


strerror() --- 错误码 => 提示信息

errno ---- 错误码, 线程安全
error
error_at_line
perror() ---- 输出字符串, 以及错误的原因, 一般将程序名称作为参数

mkdtemp() --

uname() -- 主机信息

gettimeofday

exit
_exit
_Exit

getenv
setenv
setjmp
longjmp

getpid
getppid
getuid
geteuid
getgid
getegid

fork
vfork

wait
waitpid

setuid
setgid
seteuid
setegid

setreuid
setregid

atexit

system

getlogin() -- 获取登录名称, 登录名称可有多个

nice
getpriority
setpriority

times

setsid()
getsid()
tcgetpgrp()
tcsetpgrp()
tcgetsid()



```

## 线程
```
* pthread_equal()
* pthread_self()
* pthread_create()
* pthread_exit()
* pthread_join() -- 等待线程终止
* pthread_cancel() -- 取消线程
* pthread_cleanup_push() -- 线程正常退出或被取消时执行
* pthread_cleanup_pop() ---
* pthread_detach() -- 线程设置为游离态
```

## 互斥锁 -- 资源的原子访问
```
* pthread_mutex_init()
* pthread_mutex_destroy()
* pthread_mutex_lock()
* pthread_mutex_trylock()
* pthread_mutex_unlock()
* pthread_mutex_timedlock()
```

## 读写锁 -- 使用于读远大于写的情况
```
* pthread_rwlock_init()
* pthread_rwlock_destroy()
* pthread_rwlock_rdlock()
* pthread_rwlock_tryrdlock()
* pthread_rwlock_wrlock()
* pthread_rwlock_trywrlock()
* pthread_rwlock_unlock()
* pthread_rwlock_timedrdlock()
* pthread_rwlock_timewrdlock()
```

## 条件变量 -- 等待某一条件满足
```
* pthread_cond_init()
* pthread_cond_destroy()
* pthread_cond_timedwait()
* pthread_cond_wait()
* pthread_cond_signal()
* pthread_cond_broadcast()
```

## 自旋锁
```
* pthread_spin_init()
* pthread_spin_destroy()
* pthread_spin_lock()
* pthread_spin_trylock()
* pthread_spin_unlock()
```

## 屏障
```
* pthread_barrierattr_init
* pthread_barrier_destroy
* pthread_barrier_wait
```


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


## IO管理
### 不带缓冲的IO

### 标准IO
* 打开文件
    * fopen() ---- 使用文件名
    * freopen() -- 重新打开
    * fdopen() --- 使用文件描述符打开
* 关闭文件: fclose()
* 读写数据(字符)
    * getc() ----- 读取字符, 可能是宏
    * fgetc() ---- 读取字符
    * getchar() -- 读取字符
    * ungetc() --- 压回字符
    * putc() ----- 输出字符, 可能是宏
    * fputc() ---- 输出字符
    * putchar() -- 输出字符
* 读写数据(行)
    * gets() ----- 读取, 不建议使用
    * puts() ----- 输出字符串, 然后输出换行符, 不建议使用
    * fgets() ---- 换行符也会被读取, 不一定能读取完整的行
    * fputs() ---- 输出字符串
* 读写数据(二进制)
    * fread() ---- 读数据
    * fwrite() --- 写数据
    * ftell() ---- 获取流位置
    * fseek() ---- 设置流位置
    * rewind() --- 重置流位置
* 格式化 IO
    * printf() --- 输出到标准输出
    * fprintf() -- 输出, 通过 FILE* 指定
    * dprintf() -- 输出, 通过文件描述符指定
    * sprintf() -- 输出到字符串
    * snprintf() -- 输出到字符串
    * vprintf() -- 使用可变参数 va
    * vfprintf() -- 使用可变参数 va
    * vdprintf() -- 使用可变参数 va
    * vsprintf() -- 使用可变参数 va
    * vsnprintf() -- 使用可变参数 va
    * scanf() ------ 输入(标准输入)
    * fscanf() ----- 输入(流)
    * sscanf() ----- 输入(字符串)
    * vscanf() ----- 使用可变参数 va
    * vfscanf() ---- 使用可变参数 va
    * vsscanf() ---- 使用可变参数 va
* 错误
    * ferror() -- 检测报错
    * feof() ---- 检测读到  eof
    * clearerr() -- 清除报错
* fileno 流 --> 文件描述符
* 缓冲 -- 1.cc
    * 全缓冲(磁盘)
        * 填满缓冲区才缓冲
    * 行缓冲(终端)
        * 要到换行符或填满缓冲区才缓冲
        * 遇到读操作(从内核)
    * 不缓冲
        * 输出错误
    * setvbuf() -- 设置缓冲类型
    * fflush() -- 强行刷新缓冲
* select
    * 返回已就绪的文件描述符的个数
    * 超时精确到微秒
    * 需要从头开始遍历文件描述符
* pselect
    * 返回已就绪的文件描述符的个数
    * 超时精确到纳秒
    * 需要从头开始遍历文件描述符
    * 可选择屏蔽的信号
* poll
    * 返回已就绪的文件描述符的数组
* epoll
    * 操作某一个文件描述符, 结构在内核, 提高了效率
* readv ---- 使用不连续的存储结构
* writev --- 使用不连续的存储结构
* readn ---- 全部读取
* writen --- 全部写入

### 终端 IO
* 规范模式: 行缓存
* 非规范模式:
* tcgetattr
* tcsetaddr
* stty
* isatty



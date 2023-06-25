
# 操作系统-僵尸进程
## 操作系统-僵尸进程-产生的原因
* 子进程退出时, 会向父进程发送 `SIGCHLD`, 同时内核会保留子进程退出的状态信息
* 但父进程未正确处理此信号, 导致内核一直保留子进程退出的状态信息

## 操作系统-僵尸进程-存在的意义
* 父进程可以获取子进程退出的状态信息

## 操作系统-僵尸进程-存在的危害
* 数量较少时没有过大的负作用
* 但大量僵尸进程会占用大量的 `PID` 以及其他系统资源, 影响系统正常使用

## 操作系统-僵尸进程-查看以及处理
* 使用 `top` 查看是否存在僵尸进程(zombie)
* 获取僵尸进程的进程号:
    * `ps --no-header -fe -o state,pid  | awk '$1 == "Z" {print $2}'`
* 获取僵尸进程的父进程号:
    * `ps --no-header -fe -o state,ppid | awk '$1 == "Z" {print $2}'`
* 杀死上一步获取的僵尸进程的父进程:
    * `kill -9 pid`

## 操作系统-僵尸进程-产生: 未处理 `SIGCHLD`
1. 父进程产生子进程
2. 子进程空循环
3. 此时, 可以看到子进程处于运行状态
4. 杀死子进程
5. 此时, 可以看到子进程处于僵尸状态

测试文件: [001-01.cc](./001-01.cc)

## 操作系统-僵尸进程-产生: 未正确处理 `SIGCHLD`
1. 父进程设置捕捉 `SIGCHLD` 时, 调用一次 `waitpid()`
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 由于有的 `SIGCHLD` 信号丢失, 所以有的子进程处于僵尸状态

测试文件: [001-02.cc](./001-02.cc)

## 操作系统-僵尸进程-预防: `SIGCHLD` 处理为 `SIG_IGN`
1. 父进程设置捕捉 `SIGCHLD` 时, 使用 `SIG_IGN` 忽略此信号
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 没有进程处于僵尸状态

测试文件: [001-03.cc](./001-03.cc)

## 操作系统-僵尸进程-预防: `SIGCHLD` 处理为 循环调用 `waitpid`
1. 父进程设置捕捉 `SIGCHLD` 时, 循环调用 `waitpid()` 直到失败
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 没有进程处于僵尸状态

测试文件: [001-04.cc](./001-04.cc)

## 操作系统-僵尸进程-预防: `SIGCHLD` 处理为 `SA_NOCLDWAIT`
1. 父进程设置捕捉 `SIGCHLD` 时, 设置 `SA_NOCLDWAIT`
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 没有进程处于僵尸状态

测试文件: [001-05.cc](./001-05.cc)

## 操作系统-僵尸进程-预防: 杀死父进程
1. 进程产生子进程作为测试的父进程
2. 测试的父进程产生测试的子进程
3. 测试的父进程产生测试的控制进程
4. 通过测试的控制进程可以看到测试的子进程处于运行状态
5. 通过测试的控制进程杀死测试的父进程
6. 通过测试的控制进程可以看到测试的子进程的父进程发生变化
7. 通过测试的控制进程杀死测试的子进程
8. 通过测试的控制进程可以看到测试的子进程并未处于僵尸状态

测试文件: [001-06.cc](./001-06.cc)

## 操作系统-僵尸进程-销毁: 杀死僵尸进程的父进程
1. 进程产生子进程作为测试的父进程
2. 测试的父进程产生测试的子进程
3. 测试的父进程产生测试的控制进程
4. 通过测试的控制进程可以看到测试的子进程处于运行状态
5. 通过测试的控制进程杀死测试的子进程
6. 通过测试的控制进程可以看到测试的子进程处于僵尸状态
7. 通过测试的控制进程杀死测试的父进程
8. 通过测试的控制进程可以看到测试的子进程消失了

测试文件: [001-07.cc](./001-07.cc)

## 操作系统-僵尸进程-测试: 产生僵尸进程不退出
1. 父进程产生子进程
2. 子进程退出
3. 此时, 可以看到子进程处于僵尸状态
4. 父进程死循环

测试文件: [001-08.cc](./001-08.cc)

## 操作系统-僵尸进程-注意事项
1. 设置 `SIGCHLD` 为 `SIG_IGN` 和 `SIG_DFL`(默认会忽略信号), 是不同的, 前者不会产生僵尸进程, 后者会
2. 发送 `SIGCHLD` 的子进程与 waitpid() 得到的子进程不一定相同

# 操作系统-孤儿进程
## 操作系统-孤儿进程-产生的场景
* 子进程未退出, 父进程已退出时, 此时子进程是孤儿进程

## 操作系统-孤儿进程-重现产生的场景
1. 进程产生子进程作为测试的父进程
2. 测试的父进程产生测试的子进程
3. 测试的父进程空循环
4. 此时, 可以看到测试的子进程的父进程是测试的父进程
5. 杀死测试的父进程
6. 此时, 可以看到测试的子进程的父进程变为 `systemd`

测试文件: [002-01.cc](./002-01.cc)

## 操作系统-孤儿进程-后续处理
* 孤儿进程的父进程将变为 `systemd`

## 操作系统-孤儿进程-处理的意义
* 保证所有进程都有父进程, 从而保证子进程退出时的资源都能被释放

## 操作系统-孤儿进程-注意事项
* 孤儿进程只是一个临时状态, 马上就会有新的父进程
* 孤儿进程只有父进程发生变化, 其他属性(比如, 进程, 进程组, 会话)不会变化

# 操作系统-孤儿进程组
## 操作系统-孤儿进程组-判断
* 该进程组内所有进程的父进程, 要么属于该进程组, 要么不属于该进程组所属的会话

## 操作系统-孤儿进程组-临界状态
* 如果进程组的某个进程的父进程退出导致该进程所属组变成孤儿进程组
* 且该进程组内有进程处于暂停状态
* 0 号进程将发送 `SIGCONT` 和 `SIGHUP` 给该孤儿进程组的每一个成员

## 操作系统-孤儿进程组-重现临界状态
01. 进程产生子进程作为测试的父进程
02. 测试的父进程新建新的进程组
03. 测试的父进程产生测试的第一个子进程
04. 测试的第一个子进程使自己暂停
05. 测试的父进程产生测试的第二个子进程
06. 此时, 新的进程组只包含测试的父进程, 测试的第一个子进程和测试的第二个子进程
07. 杀死测试的父进程
08. 此时, 新的进程组只包含测试的第一个子进程和测试的第二个子进程
09. 上述两个进程的父进程变为 systemd
10. systemd 和 两个测试的子进程不在同一个会话
11. 新的进程组变成一个孤儿进程组, 第一个测试的子进程处于暂停状态
12. 所以 0 号进程将发送 `SIGCONT` 和 `SIGHUP` 给该孤儿进程组的每一个成员

测试文件: [003-01.cc](./003-01.cc)

## 操作系统-孤儿进程组-临界状态处理的意义
* 出现临界状态一般都是程序有问题, 系统相当于加了一层保险, 避免系统资源浪费

## 操作系统-孤儿进程组-注意事项
* 会话首进程所在的进程组也属于孤儿进程组
* 孤儿进程所在的进程组不一定是孤儿进程组

# 操作系统-进程
## 操作系统-进程-新建
* fork(): 父子进程的执行顺序不确定
* vfork(): 在子进程退出或执行exec之前, 父进程处于不可被信号打断的休眠状态
* 将继承父进程的进程组, 会话

## 操作系统-进程-修改
* PID 无法变化

## 操作系统-进程-销毁
* 将向父进程发送信号 SIGCHLD, 内核会保存退出状态
* 如果此进程是该进程组的最后一个进程, 此进程退出后, 该进程组消失
* 如果此进程是该会话的最后一个进程, 此进程退出后, 该会话消失

## 操作系统-进程-其他特性
* 启动命令: 完整的启动命令, 包括路径和参数, 如果是符号链接, 只会记录和展示符号本身
* 进程名称: 启动名称去掉路径和参数, 查找或输出时, 只会使用前 15 位(一般使用15位足够了)
* 一个进程只能属于一个父进程
* 一个父进程可以有多个子进程
* 一个进程只能属于一个进程组
* 一个进程只能属于一个会话
* 实际用户和组
* 有效用户和组
* 保存用户和组
* 文件用户和组, 一般和有效的用户相同
* 附属组
* 优先级

## 操作系统-进程-状态及改变
* 就绪
* 运行(R)
* 休眠(S)(可被信号打断)(指被捕获的信号)
    * pause() 只有收到未忽略的信号才返回
    * sleep() 只有收到未忽略的信号 或 到达指定秒数才返回 -- 004-01.cc
        1. 使用 fork() 产生子进程
        2. 子进程设置信号(SIGUSR1)处理函数
        3. 子进程休眠10s
        4. 父进程休眠1s
        5. 此时, 可以看到, 子进程处于休眠状态
        6. 向子进程发送信号(SIGUSR1)
        7. 此时, 子进程被唤醒(休眠时间小于10s)
* 休眠(D)(不可被信号打断)(指被捕获的信号)
   * 调用 vfork() 后的父进程 -- 004-02.cc
        1. 使用 fork() 产生测试的父进程
        2. 测试的父进程设置信号(SIGUSR1)处理函数
        3. 测试的父进程使用 vfork() 产生测试的子进程
        4. 测试的子进程休眠10s
        5. 测试的父进程休眠1s
        6. 此时, 可以看到, 测试的父进程处于不可被打断的状态
        7. 向测试的父进程发送信号(SIGUSR1)
        8. 此时, 父进程处于不可打断的状态, 所以不会处理
        9. 测试的子进程休眠完成(休眠时间为10s)
        10. 测试的父进程处理信号, 直到结束
   * SIGSTOP 也会被阻塞 -- 004-03.cc
        1. 使用 fork() 产生测试的父进程
        2. 测试的父进程使用 vfork() 产生测试的子进程
        3. 测试的子进程休眠10s
        4. 测试的父进程休眠1s
        5. 此时, 可以看到, 测试的父进程处于不可被打断的状态
        6. 向测试的父进程发送信号(SIGSTOP)
        7. 此时, 父进程处于不可打断的状态, 所以不会处理
        8. 向测试的父进程发送信号(SIGCONT)
        9. 此时, 父进程处于不可打断的状态, 所以不会处理
        10. 测试的子进程休眠完成(休眠时间为10s)
        11. 测试的父进程继续运行, 直到结束
   * SIGKILL 不会被阻塞 -- 004-04.cc
        1. 使用 fork() 产生测试的父进程
        2. 测试的父进程使用 vfork() 产生测试的子进程
        3. 测试的子进程休眠10s
        4. 测试的父进程休眠1s
        5. 此时, 可以看到, 测试的父进程处于不可被打断的状态
        6. 向测试的父进程发送信号(SIGKILL)
        7. 测试的父进程退出
        8. 测试的子进程休眠完成(休眠时间为10s)
        9. 主进程结束
* 暂停(T)(作业控制)
    * 收到信号 SIGSTOP
    * 收到信号 SIGTSTP, 可由 ctrl+z 产生
    * 收到信号 SIGTTIN, 处于后台进程时读终端
    * 收到信号 SIGTTOT, 处于后台进程时写终端, 这个得看设置是否允许后台进程写终端
    * 继续, 收到信号 SIGCONT -- 004-05.cc
        1. 使用 fork() 产生子进程
        2. 子进程设置信号(SIGUSR1)处理函数
        3. 子进程空循环
        4. 父进程发送信号给子进程(SIGSTOP)
        5. 子进程暂停
        6. 父进程发送信号给子进程(SIGUSR1)
        7. 此时, 子进程处于暂停, 不会处理该信号
        8. 父进程发送信号给子进程(SIGCONT)
        9. 子进程继续, 然后处理 SIGUSR1, 直到结束
* 暂停(t)(由于 DEBUG 产生)
* 空闲(I)
    * 处于不可被打断的休眠状态时, 有时 CPU 是空闲的
* 僵尸(Z)
    * 子进程已退出, 父进程还未处理
* 退出(X)

## 操作系统-进程-系统文件
```
/proc/loadavg     # 系统负载
/proc/cpuinfo     # cpu 信息
/proc/uptime      # 运行时间
/proc/sys

/proc/PID/cmdline # 完整的启动命令
                  # 如果以符号链接启动, 将存储符号链接本身
/proc/PID/comm    # 进程名称, 不包含路径名称, 最多 15 位
                  # 如果以符号链接启动, 将存储符号链接本身
/proc/PID/cwd     # 进程当前的目录
/proc/PID/exe     # 符号链接, 指向运行的进程
/proc/PID/environ # 进程使用的环境变量
/proc/PID/fd      # 进程所打开的文件描述符
/proc/PID/limits  # 进程对各种资源的限制
/proc/PID/task    # 进程使用的线程情况
```

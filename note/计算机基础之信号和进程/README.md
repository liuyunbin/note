
# 计算机基础之进程
本文主要描述进程, 进程组, 会话, 终端的关系

## 进程
* 新建的进程将继承父进程的进程组, 会话
* 进程ID无法变化
* 进程退出时, 将向父进程发送信号, 父进程处理此信号前, 该进程变为僵尸进程
    * 如果此进程是该进程组的最后一个进程, 此进程退出后, 该进程组消失
* 一个进程只能有一个父进程
* 一个父进程可以有多个子进程
* 孤儿进程:
    * 产生: fork() 后, 父进程退出, 子进程成为孤儿进程
    * 父进程已经退出的进程, 孤儿进程的父进程ID会自动改变为1, 进程组ID, 会话ID 不变
* 孤儿进程组:
    * 该进程组所有的进程的父进程要么属于该进程组, 要么不属于此会话(这里讨论的进程不包括会话ID)
* 一个进程只能属于一个进程组
* 一个进程只能属于一个会话
* 存在原因: 为了唯一确认一个进程
* 其他属性:
    * 实际用户和组
    * 有效用户和组
    * 保存用户和组
    * 文件用户和组, 一般和有效的相同
    * 附属组
    * 进程状态: 运行, 休眠, 僵尸进程等
    * 优先级
    * 进程名称和启动命令

## 进程组
* 只能修改自身或者子进程(调用exec之前)的进程的进程组ID
* 进程和进程组必须属于同一个会话
* 只要该进程组还存在进程, 该进程组就不会消失
* 一个进程组包含一个或多个进程
* 一个进程组只能属于一个会话
* 存在原因: 为了便于处理一批进程, 比如发送信号

## 会话
* 新建会话
    * 当前进程不能是进程组进程, 为可以避免影响到原进程组的其他进程
    * 新的会话ID是当前进程的ID, 新的进程组ID也是当前进程的ID
    * 新会话和新进程组里将只包含当前进程
    * 新的会话将脱离终端的控制
* 会话退出时, 默认不会对会话内的其他进程有影响??
* 一个会话包括一个或多个进程
* 一个会话包括一个或多个进程组
* 一个会话最多和一个终端绑定
* 存在原因: 为了终端的作业控制

## 终端
* 用户登录时, 系统将一个会话与终端绑定, 此会话进程即为控制进程
* 终端退出时, 将发送 SIGHUP 给控制进程, 控制进程将向此会话中的所有进程组发送信号 SIGHUP
    * SIGHUP 表示控制终端断开(正常或异常), 默认行为是结束进程
* 此会话有且只有一个前台进程组, 有零个或多个后台进程组
* 终端的输入将发送到前台进程组, 前台和后台进程组的输出都将发送到终端
* 新建会话可以脱离终端
* 脱离终端的进程的父进程不一定是 1, 也可能是其他脱离终端的进程
* 脱离终端可以忽略 SIGHUP 或 新建会话

## 进程状态改变
* 就绪 => 运行(R)
* 运行(R) => 休眠(S)(可被信号打断)(指被捕获的信号)
    * pause() 只有收到未忽略的信号才返回
    * sleep() 只有收到未忽略的信号 或 到达指定秒数才返回
* 运行(R) => 休眠(D)(不可被信号打断)(指被捕获的信号)
    * 调用 vfork() 后的父进程
* 运行(R) 或 休眠(S) => 暂停(T)(作业控制)
    * 收到信号 SIGSTOP
    * 收到信号 SIGTSTP, 可由 ctrl+z 产生
    * 收到信号 SIGTTIN, 处于后台进程时读终端
    * 收到信号 SIGTTOT, 处于后台进程时写终端, 这个得看设置是否允许后台进程写终端
* 暂停(T) => 运行(R) 或 休眠(S)
    * 收到信号 SIGCONT
* 运行(R) => 暂停(t)(由于 DEBUG 产生)
* 运行(R) => 空闲(I), 处于不可被打断的休眠状态时, 有时 CPU 是空闲的
* 运行(R) 或 休眠(S) 或 暂停(T) 或 暂停(t) => 僵尸(Z)
    * 子进程已退出, 父进程还未处理
* 僵尸(Z) => 退出(X)

## 僵尸进程
* 产生的原因: 子进程已退出, 父进程未处理
* 产生的场景
    * 子进程已退出, 父进程处理之前
    * 子进程已退出, 父进程未处理
        1. fork() 产生子进程
        2. 父进程空循环
        3. 子进程退出, 此时子进程处于僵尸状态
    * 子进程已退出, 父进程已处理, 但处理方式不对, 由于 SIGCHLD 信号可能丢失, 导致产生僵尸进程
        1. 父进程捕捉 SIGCHLD, 信号处理函数调用一次 waitpid()
        2. 产生 10 子进程, 每个子进程都退出
        3. 此时, 由于有的 SIGCHLD 信号丢失, 所以有的子进程处于僵尸状态
* 存在的意义: 父进程可以获取子进程退出的状态信息
* 预防
    1. 父进程捕获 SIGCHLD, 在信号处理函数里循环调用 waitpid(...WNOHANG)
    2. 父进程使用 SIG_IGN 忽略 SIGCHLD 信号
    3. 父进程使用 sigaction(...SA_NOCLDWAIT)
    4. 父进程退出, 直接将对子进程的处理行为交给 system
* 杀死
    1. 只能杀死僵尸进程的父进程
    2. 此后, 僵尸进程的父进程将变为 systemd
    3. 此后, systemd 将处理 SIGCHLD 信号
    4. 然后, 僵尸进程消失

## 线程
* ps -o lwp,nlwp # 线程ID, 线程数
* ps -L          # 列每一个线程

ulimit              # 限制资源使用, 包括:
                    #   内存, 虚拟内存, CPU
                    #   进程数, 线程数
                    #   文件锁数, 文件描述符数, 写入文件大小
                    #   待处理的信号数
                    #   core 文件大小
                    # 也可指定是硬限制还是软限制
ulimit -a           # 列出资源的限制
ulimit -c unlimited # 允许 core 文件

ps -U RUID -G RGID           # 实际的用户和组
ps -u EUID -g EGID           # 有效的用户和组
ps -p PID                    # 进程ID
ps -s SID                    # 会话ID
ps --ppid PPID               # 父进程ID
ps -t ...                    # 终端
ps -C vim                    # 进程名称, 全名称 或 前 15 位

ps -o ruid,ruser,rgid,rgroup # 实际的用户和组
ps -o euid,euser,egid,egroup # 有效的用户和组
ps -o suid,suser,sgid,sgroup # 保存的用户和组
ps -o fuid,fuser,fgid,fgroup # 文件的用户和组, 一般和有效的相同
ps -o supgid,supgrp          # 附属组ID
ps -o pid,ppid,pgid,sid      # 进程ID, 父进程ID, 进程组ID, 会话ID
ps -o ouid                   # 会话ID所属用户ID
ps -o tty                    # 终端
ps -o tpgid                  # 输出前台进程的ID
ps -o luid,lsession          # 终端登录的用户ID和会话ID
ps -o stat,state             # 进程状态
                             # R 正在运行
                             # S 正在休眠
                             # T 后台暂停的作业
                             # t debug 调试中
                             # Z 僵尸进程
ps -o pmem,rsz,vsz           # 内存百分比,内存,内存(含交换分区)
ps -o pcpu,c,bsdtime,cputime # cpu: 百分比,百分比整数,user+system,system
ps -o lstart,etime,etimes    # 启动时间,运行时间,运行时间(秒)
ps -o nice,pri,psr,rtprio    # 优先级
ps -o wchan                  # 进程休眠, 返回当前使用的内核函数
                             # 进程运行, 返回 -
                             # 列出线程, 返回 *
ps -o cmd                    # 启动命令
ps -o comm                   # 进程名称
ps -o fname                  # 进程名称的前 8 位

ps -e           # 所有进程
ps -H           # 输出进程树
ps -ww          # 不限制输出宽度
ps --no-headers # 不输出列头部
ps --headers    #   输出列头部
ps --sort -pcpu # cpu 使用率逆序

* pgrep # 使用进程名称查找
        # 可以前缀匹配, 精确匹配, 使用启动命令匹配, 默认使用进程名称(15)匹配, 一般默认足够
        # 使用扩展的正则表达式
        # 可以指定 实际用户, 有效用户, 实际组ID, 进程组ID, 会话ID, 父进程ID, 终端
        # 可以反转匹配结果
        # 可以列出线程ID
        # 可以列出匹配到的最老或最新的进程
        # 可以列出进程ID, 进程名称(15位), 启动命令
        # 可以列出匹配到的数目
        # 可以指定输出的分隔符
* pkill # 杀死进程, 参数和 pgrep 类似
* pwdx  # 列出进程的当前工作目录
* pidof # 列出进程名称对应的 PID, 精确匹配, 没有长度限制
* kill        # 通过进程ID发送信号给进程或进程组
* killall     # 通过进程名称发送信号给进程或进程组, 进程名称精确匹配
* kill    -l  # 列出所有信号
* killall -l  # 列出所有信号
* kill    %1  # bash 内置的 kill, 杀死作业
* killall -o 2m a.out # 发给 2 分钟前启动的 a.out
* killall -y 2m a.out # 发给 2 分钟内启动的 a.out
* killall -w    a.out # 等待进程结束

* free -h    # 内存使用情况
* df   -Th   # 查看磁盘挂载情况

uname -a # 全部信息
uname -m # x86_64 等
uname -r # 内核版本

top
top -n 1 # 刷新次数
top -b # 方便写入文件
top        # 使用 CPU 排序 -- TODO
top -u lyb # M 内存排序
           # P CPU 排序
           # T 时间排序
           # m 显示内存信息
           # t 显示进程 或 CPU状态信息
           # c 显示命令名称 或 完整命令行

pstree     [PID] # 以进程 PID 为根画进程树, 默认为 1
pstree  -c [PID] # 展示所有子树
pstree  -p [PID] # 展示进程ID
pstree  -g [PID] # 展示进程组ID
pstree  -n [PID] # 使用 PID 排序而不是 进程名称
pstree  -l [PID] # 使用长行, 方便写入文件

nohup  # 忽略信号 SIGHUP
setsid # 以新的 session 执行命令

strace               # 追踪进程的系统调用和信号处理
strace cmd argv      # strace 和命令 同时启动
strace -p pid        # 追踪正在运行的程序, 多个进程, 指定 -p 多次
strace -c            # 统计系统调用的时间, 次数
strace -o ...        # 输出到指定的文件
strace -tt           # 显示调用时间 时分秒.毫秒
strace -T            # 显示系统调用的耗时
strace -f            # 跟踪子进程, 不包括 vfork
strace -F            # 跟踪 vfork
strace -e trace=...  # 跟踪指定信号调用
strace -s ...        # 参数是字符串时, 最大输出长度, 默认是32个字节
strace -e signal=... # 跟踪指定信号

## proc 文件
/proc/loadavg     # 系统负载
/proc/cpuinfo     # cpu 信息
/proc/uptime      # 运行时间
/proc/sys

/proc/PID/cmdline # 完整的启动命令
/proc/PID/comm    # 进程名称, 不包含路径名称, 最多 15 位
                  # 如果以符号链接启动, 将存储符号链接
/proc/PID/cwd     # 进程当前的目录
/proc/PID/exe     # 符号链接, 指向运行的进程
/proc/PID/environ # 进程使用的环境变量
/proc/PID/fd      # 进程所打开的文件描述符
/proc/PID/limits  # 进程对各种资源的限制
/proc/PID/task    # 进程使用的线程情况


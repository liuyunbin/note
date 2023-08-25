
## core 不能生成的原因
* 设置了 SUID, 进程的实际用户不是可执行文件的所有者
* 设置了 SGID, 进程的实际组不是可执行文件组的所有者
* 没有写当前目录的权限
* 文件已存在, 但无权限修改
* 文件太大, 受 ulimit 的限制

## ubuntu 生成 core
1. ulimit -c unlimited -- 设置 core 文件大小的软限制不受限制
2. /etc/sysctl.conf ----- 添加 `kernel.core_pattern=%e.%p` -- 文件名, 进程号
    * %% --- %
    * %p --- pid
    * %u --- uid
    * %g --- gid
    * %s --- 导致dump的信号
    * %t --- 时间
    * %e --- 执行文件的名称
    * %h --- hostname
3. sudo sysctl -p ------- 配置生效

## 常用命令
```
                             # 多个命令之间取或
ps -U RUID -G RGID           # 实际的用户和组
ps -u EUID -g EGID           # 有效的用户和组
ps -p PID                    # 进程ID, 多个进程可以重复使用 -p 或者参数以分号分割 -- 常用
ps -s SID                    # 会话ID
ps --ppid PPID               # 父进程ID
ps -t ...                    # 终端
ps -C vim                    # 进程名称, 全名称 或 前 15 位 -- 常用

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
                             # S 正在休眠(可被打断)
                             # D 正在休眠(不可被打断)
                             # T 后台暂停的作业
                             # t debug 调试中
                             # Z 僵尸进程
ps -o pmem,rsz,vsz           # 内存百分比,内存,内存(含交换分区)
ps -o pcpu,c,bsdtime,cputime # cpu: 百分比,百分比整数,user+system,system
ps -o lstart,etime,etimes    # 启动时间,运行时间,运行时间(秒), 无法对 etimes 进行排序
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

ps -o lwp,nlwp # 线程ID, 线程数
ps -L          # 列每一个线程

pstree     [PID] # 以进程 PID 为根画进程树, 默认为 1 -- 常用
pstree  -c [PID] # 展示所有子树
pstree  -p [PID] # 展示进程ID
pstree  -g [PID] # 展示进程组ID
pstree  -n [PID] # 使用 PID 排序而不是 进程名称
pstree  -l [PID] # 使用长行, 方便写入文件

              # 多个命令之间取且
pgrep         # 使用进程名称查找, 使用扩展的正则表达式
pgrep -f  ... # 使用启动命令匹配, 默认使用进程名称匹配(最多15位)
pgrep -c  ... # 输出匹配到的进程数目           -- 常用
pgrep -d，... # 设置输出的分割符，默认是换行符 -- 常用
pgrep -i  ... # 忽略大小写
pgrep -l  ... # 列出进程名称(最多15位)         -- 常用
pgrep -a  ... # 列出启动命令                   -- 常用
pgrep -n  ... # 仅列出最新的进程
pgrep -o  ... # 仅列出最旧的进程
pgrep -g  ... # 指定进程组ID
pgrep -G  ... # 指定实际组ID
pgrep -P  ... # 指定父进程ID
pgrep -s  ... # 指定会话ID
pgrep -t  ... # 指定终端
pgrep -u  ... # 指定有效用户ID
pgrep -U  ... # 指定实际用户ID
pgrep -v  ... # 反转结果
pgrep -x  ... # 精确匹配，默认不需要完全匹配
pgrep -w  ... # 列出线程ID

pidof    # 进程名称 => PID, 精确匹配, 没有长度限制

pwdx pid # 列出进程的当前工作目录

kill         pid # 通过进程ID发送信号给进程或进程组
kill -signal pid # 指定信号，默认值为 SIGTERM
kill -l          # 列出所有信号

killall             # 通过进程名称发送信号给进程或进程组, 进程名称精确匹配
killall -l          # 列出所有信号
killall -o 2m a.out # 发给 2 分钟前启动的 a.out
killall -y 2m a.out # 发给 2 分钟内启动的 a.out
killall -w    a.out # 等待进程结束

pkill         ... # 杀死进程, 扩展的正则表达式，参数和 pgrep 类似 -- 常用
pkill -signal ... # 指定信号，默认值为 SIGTERM

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

top     # 第一行 系统时间 运行时间 用户数 平均负载
        # 第二行 进程总结
        # 第三行 CPU 总结
        # 第四行 物理内存总结
        # 第五行 虚拟内存总结
        # 交互命令
        #   空格 或 回车 刷新
        #   l 切换负载的显示
        #   t 切换任务的显示
        #   m 切换内存的显示
        #   f 选择展示的字段
        #   R 反向排序
        #   c 显示命令名称 或 完整命令行
        #   i 显示空闲任务
        #   u 显示特定用户的进程
        #   k 结束任务
        #   h 帮助
        #   L 搜索字符串
        #   H 显示线程
        #   0 不显示统计值为 0 的项
        #   1   显示所有的cpu信息
        #   < 排序字段左移
        #   > 排序字段右移
        #   M 内存排序   --- 常用
        #   P CPU 排序   --- 常用
        #   T 时间排序   --- 常用
top -n 1   # 刷新次数
top -b     # 方便写入文件
top -c     # 显示完整命令行
top -p ... # 指定 PID
top -u lyb # 指定用户

ulimit -a           # 列出资源的限制
ulimit -c unlimited # 允许 core 文件
```

## 建议
* 使用 pgrep 获取 PID, 使用 ps 列出详细信息
* 使用 etimes 可以方便计算出启动时间, 并格式化 年-月-日 时-分-秒 时区
* 一般使用进程的前 15 位即可
* 使用 pkill 发送信号

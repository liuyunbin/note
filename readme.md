
# 编译
```
./bash/install-dependency.sh
./bash/build.sh
```

# 目录
* [计算机操作系统-001](#计算机操作系统)
    * [僵尸进程](#僵尸进程)
* [计算机组成原理-002](#计算机组成原理)
* [计算机网络-003](#计算机网络)
* [常用函数](#常用函数)
* [常用命令](#常用命令)

# 计算机操作系统
## 僵尸进程
## 产生的原因
* 子进程退出时, 会向父进程发送 `SIGCHLD`, 同时内核会保留子进程退出的状态信息
* 但父进程未正确处理此信号, 导致内核一直保留子进程退出的状态信息

## 存在的意义
* 父进程可以获取子进程退出的状态信息

## 存在的危害
* 数量较少时没有过大的负作用
* 但大量僵尸进程会占用大量的 `PID` 以及其他系统资源, 影响系统正常使用

## 查看以及处理
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

测试文件: [01.cc](./01.cc)

## 操作系统-僵尸进程-产生: 未正确处理 `SIGCHLD`
1. 父进程设置捕捉 `SIGCHLD` 时, 调用一次 `waitpid()`
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 由于有的 `SIGCHLD` 信号丢失, 所以有的子进程处于僵尸状态

测试文件: [02.cc](./02.cc)

## 操作系统-僵尸进程-预防: `SIGCHLD` 处理为 `SIG_IGN`
1. 父进程设置捕捉 `SIGCHLD` 时, 使用 `SIG_IGN` 忽略此信号
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 没有进程处于僵尸状态

测试文件: [03.cc](./03.cc)

## 操作系统-僵尸进程-预防: `SIGCHLD` 处理为 循环调用 `waitpid`
1. 父进程设置捕捉 `SIGCHLD` 时, 循环调用 `waitpid()` 直到失败
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 没有进程处于僵尸状态

测试文件: [04.cc](./04.cc)

## 操作系统-僵尸进程-预防: `SIGCHLD` 处理为 `SA_NOCLDWAIT`
1. 父进程设置捕捉 `SIGCHLD` 时, 设置 `SA_NOCLDWAIT`
2. 父进程阻塞信号 `SIGCHLD`
3. 父进程产生五个子进程, 每次子进程都退出, 父进程休眠一秒, 保证子进程已退出
4. 父进程解除信号 `SIGCHLD` 阻塞
5. 此时, 没有进程处于僵尸状态

测试文件: [05.cc](./05.cc)

## 操作系统-僵尸进程-预防: 杀死父进程
1. 进程产生子进程作为测试的父进程
2. 测试的父进程产生测试的子进程
3. 测试的父进程产生测试的控制进程
4. 通过测试的控制进程可以看到测试的子进程处于运行状态
5. 通过测试的控制进程杀死测试的父进程
6. 通过测试的控制进程可以看到测试的子进程的父进程发生变化
7. 通过测试的控制进程杀死测试的子进程
8. 通过测试的控制进程可以看到测试的子进程并未处于僵尸状态

测试文件: [06.cc](./06.cc)

## 操作系统-僵尸进程-销毁: 杀死僵尸进程的父进程
1. 进程产生子进程作为测试的父进程
2. 测试的父进程产生测试的子进程
3. 测试的父进程产生测试的控制进程
4. 通过测试的控制进程可以看到测试的子进程处于运行状态
5. 通过测试的控制进程杀死测试的子进程
6. 通过测试的控制进程可以看到测试的子进程处于僵尸状态
7. 通过测试的控制进程杀死测试的父进程
8. 通过测试的控制进程可以看到测试的子进程消失了

测试文件: [07.cc](./07.cc)

## 操作系统-僵尸进程-测试: 产生僵尸进程不退出
1. 父进程产生子进程
2. 子进程退出
3. 此时, 可以看到子进程处于僵尸状态
4. 父进程死循环

测试文件: [08.cc](./08.cc)

## 操作系统-僵尸进程-注意事项
1. 设置 `SIGCHLD` 为 `SIG_IGN` 和 `SIG_DFL`(默认会忽略信号), 是不同的, 前者不会产生僵尸进程, 后者会
2. 发送 `SIGCHLD` 的子进程与 waitpid() 得到的子进程不一定相同

## 常用函数
* signal()
* wait()
* waitpid()
* wait3()
* wait4()
* waitid()


       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *wstatus);
       pid_t waitpid(pid_t pid, int *wstatus, int options);

       int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

   wait() and waitpid()
       The call wait(&wstatus) is equivalent to:
           waitpid(-1, &wstatus, 0);

< -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.
-1     meaning wait for any child process.
0      meaning  wait  for  any  child  process  whose  process group ID is equal to that of the calling
        process at the time of the call to waitpid().
> 0    meaning wait for the child whose process ID is equal to the value of pid.

       The value of options is an OR of zero or more of the following constants:

       WNOHANG -- 无子进程退出时立刻退出
       WUNTRACED -- 子进程暂停
       WCONTINUED -- 子进程继续

       WIFEXITED(wstatus) -- 子进程正常退出

       WEXITSTATUS(wstatus) -- 子进程退出的状态

       WIFSIGNALED(wstatus) -- 信号导致子进程退出

       WTERMSIG(wstatus) -- 导致子进程退出的信号

       WCOREDUMP(wstatus) -- 是否产生 core

       WIFSTOPPED(wstatus) -- 是否暂停

       WSTOPSIG(wstatus) -- 导致子进程暂停的信号

       WIFCONTINUED(wstatus) -- 子进程是否继续


NOTES
    A  child that terminates, but has not been waited for becomes a "zombie".  The kernel maintains a mini‐
    mal set of information about the zombie process (PID, termination status, resource  usage  information)
    in order to allow the parent to later perform a wait to obtain information about the child.  As long as
    a zombie is not removed from the system via a wait, it will consume a slot in the kernel process table,
and if this table fills, it will not be possible to create further processes.  If a parent process ter‐       minates, then its "zombie" children (if any) are adopted by init(1), (or  by  the  nearest  "subreaper"
    process as defined through the use of the prctl(2) PR_SET_CHILD_SUBREAPER operation); init(1) automati‐
   cally performs a wait to remove the zombies.

    POSIX.1-2001 specifies that if the disposition of SIGCHLD is set to SIG_IGN or the SA_NOCLDWAIT flag is
   set  for  SIGCHLD  (see sigaction(2)), then children that terminate do not become zombies and a call to
    wait() or waitpid() will block until all children have terminated, and then  fail  with  errno  set  to
   ECHILD.   (The  original  POSIX  standard  left the behavior of setting SIGCHLD to SIG_IGN unspecified.
    Note that even though the default disposition of SIGCHLD is "ignore", explicitly setting  the  disposi‐
   tion to SIG_IGN results in different treatment of zombie process children.)

    Linux  2.6  conforms to the POSIX requirements.  However, Linux 2.4 (and earlier) does not: if a wait()
   or waitpid() call is made while SIGCHLD is being ignored, the call behaves just as though SIGCHLD  were
    not  being  ignored,  that  is,  the  call  blocks until the next child terminates and then returns the
    process ID and status of that child.

   Linux notes
    In the Linux kernel, a kernel-scheduled thread is not a distinct construct from a process.  Instead,  a
   thread  is simply a process that is created using the Linux-unique clone(2) system call; other routines
    such as the portable pthread_create(3) call are implemented using clone(2).  Before Linux 2.4, a thread
   was just a special case of a process, and as a consequence one thread could not wait on the children of
    another thread, even when the latter belongs to the same thread group.  However, POSIX prescribes  such
   functionality, and since Linux 2.4 a thread can, and by default will, wait on children of other threads
    in the same thread group.

   The following Linux-specific options are for use with children created using clone(2); they  can  also,
   since Linux 4.7, be used with waitid():

       The following program demonstrates the use of fork(2) and  waitpid().   The  program  creates  a  child
       process.  If no command-line argument is supplied to the program, then the child suspends its execution
       using pause(2), to allow the user to send signals to the child.  Otherwise, if a command-line  argument
       is  supplied,  then  the child exits immediately, using the integer supplied on the command line as the
       exit status.  The parent process executes a loop that monitors the child using waitpid(), and uses  the
       W*() macros described above to analyze the wait status value.

       The following shell session demonstrates the use of the program:

           $ ./a.out &
           Child PID is 32360
           [1] 32359
           $ kill -STOP 32360
           stopped by signal 19
           $ kill -CONT 32360
           continued
           $ kill -TERM 32360
           killed by signal 15
           [1]+  Done                    ./a.out
           $

   Program source

       #include <sys/wait.h>
       #include <stdint.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>

       int
       main(int argc, char *argv[])
       {
           pid_t cpid, w;
           int wstatus;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */
               printf("Child PID is %jd\n", (intmax_t) getpid());
               if (argc == 1)
                   pause();                    /* Wait for signals */
               _exit(atoi(argv[1]));

           } else {                    /* Code executed by parent */
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(wstatus)) {
                       printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                   } else if (WIFSIGNALED(wstatus)) {
                       printf("killed by signal %d\n", WTERMSIG(wstatus));
                   } else if (WIFSTOPPED(wstatus)) {
                       printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                   } else if (WIFCONTINUED(wstatus)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
               exit(EXIT_SUCCESS);
           }
       }

SYNOPSIS

       pid_t wait3(int *wstatus, int options,
                   struct rusage *rusage);

       pid_t wait4(pid_t pid, int *wstatus, int options,
                   struct rusage *rusage);

DESCRIPTION
       These functions are nonstandard; in new programs, the use of waitpid(2) or waitid(2) is preferable.

       The  wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage
       information about the child in the structure pointed to by rusage.

       Other than the use of the rusage argument, the following wait3() call:

           wait3(wstatus, options, rusage);

       is equivalent to:

           waitpid(-1, wstatus, options);

       Similarly, the following wait4() call:

           wait4(pid, wstatus, options, rusage);

       is equivalent to:

           waitpid(pid, wstatus, options);

# 计算机组成原理
# 计算机网络
# 常用函数
# 常用命令

# 最佳实际
* 文件名称建议: 大小写字母 数字 下划线 短横线 点
* 参数建议: 不要空格, 不要以短横线开头
* 学习命令: 以功能为核心,
* 学习一个命令需要注意的点
    * 不常用的命令, 只需知道大致功能即可, 比如, 组相关的命令
    * 不常用的命令, 只需知道命令的大致功能 或者 关键参数即可, 比如, 组相关的命令
    *   复杂的命令, 需要总结出常用的参数, 每次都过一遍 man 文档太麻烦了, 比如, ps
    *   常用的命令, 需要知道大致功能即可, 记住常用参数, 其他参数需要的时候查询即可
    * 支持 通配符, 还是基础的正则表达式 还是 扩展的正则表达式
    * 涉及过滤时, 多个命令是且还是或
    * 对符号链接的处理, 这个可以先猜, 有利于加深理解
    * 对转义字符的处理
    * 学习命令要以功能为核心而不是以命令参数为核心
    * 不要垃圾进垃圾出, 宁可不写, 也不写错的, 或者 不懂的内容


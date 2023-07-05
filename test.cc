
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

void test_signal();   // 测试信号
void test_process();  // 测试进程

void test_va();     // 测试可变参数
void test_macro();  // 测试宏
void test_exit();   // 测试退出
void test_jmp();    // 测试跨函数跳转
void test_limit();  // 测试资源限制

void test_orphan_process();        // 测试孤儿进程
void test_orphan_process_group();  // 测试孤儿进程组

void test_pgid();   // 测试进程组
void test_sid();    // 测试会话
void test_vfork();  // 测试 vfork

void test_process_01();  // 测试进程:   可被信号打断的休眠(指被捕获的信号)
void test_process_02();  // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
void test_process_03();  // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
                         // 对 SIGSTOP 的处理
void test_process_04();  // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
                         // 对 SIGKILL 的处理
void test_process_05();  // 测试进程: 暂停 => 继续

int main() {
    test_signal();   // 测试信号
    test_process();  // 测试进程

    // 测试宏
    // test_macro();

    // 测试可变参数
    // test_va();

    // 测试退出
    // test_exit();

    // 测试跨函数跳转
    // test_jmp();

    // 测试资源限制
    // test_limit();

    // 测试孤儿进程
    // test_orphan_process();

    // 测试孤儿进程组
    // test_orphan_process_group();

    // 测试进程组
    // test_pgid();

    // 测试会话
    // test_sid();

    // 测试 vfork
    // test_vfork();

    // 测试进程: 可被信号打断的休眠(指被捕获的信号)
    // test_process_01();

    // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
    // test_process_02();

    // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
    // 对 SIGSTOP 的处理
    // test_process_03();

    // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
    // 对 SIGKILL 的处理
    // test_process_04();

    // 测试进程: 暂停 -> 继续
    // test_process_05();
    // std::cout << "环境变量 PATH: " << getenv("PATH") << std::endl;
    //  sleep(1);
    return 0;
}

// 日志输出
template <typename T>
std::string to_string(T data) {
    std::stringstream tmp;
    tmp << data;
    return tmp.str();
}

template <typename T, typename... Args>
std::string to_string(T data, Args... args) {
    std::stringstream tmp;
    tmp << data;
    return tmp.str() + to_string(args...);
}

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

template <typename... Args>
void log(Args... args) {
    log(to_string(args...));
}

std::map<int, std::string> m{
    {SIGHUP,    " 1-SIGHUP"   },
    {SIGINT,    " 2-SIGINT"   },
    {SIGQUIT,   " 3-SIGQUIT"  },
    {SIGILL,    " 4-SIGILL"   },
    {SIGTRAP,   " 5-SIGTRAP"  },
    {SIGABRT,   " 6-SIGABRT"  },
    {SIGBUS,    " 7-SIGBUS"   },
    {SIGFPE,    " 8-SIGFPE"   },
    {SIGKILL,   " 9-SIGKILL"  },
    {SIGUSR1,   "10-SIGUSR1"  },
    {SIGSEGV,   "11-SIGSEGV"  },
    {SIGUSR2,   "12-SIGUSR2"  },
    {SIGPIPE,   "13-SIGPIPE"  },
    {SIGALRM,   "14-SIGALRM"  },
    {SIGTERM,   "15-SIGTERM"  },
    {SIGSTKFLT, "16-SIGSTKFLT"},
    {SIGCHLD,   "17-SIGCHLD"  },
    {SIGCONT,   "18-SIGCONT"  },
    {SIGSTOP,   "19-SIGSTOP"  },
    {SIGTSTP,   "20-SIGTSTP"  },
    {SIGTTIN,   "21-SIGTTIN"  },
    {SIGTTOU,   "22-SIGTTOU"  },
    {SIGURG,    "23-SIGURG"   },
    {SIGXCPU,   "24-SIGXCPU"  },
    {SIGXFSZ,   "25-SIGXFSZ"  },
    {SIGVTALRM, "26-SIGVTALRM"},
    {SIGPROF,   "27-SIGPROF"  },
    {SIGWINCH,  "28-SIGWINCH" },
    {SIGIO,     "29-SIGIO"    },
    {SIGPWR,    "30-SIGPWR"   },
    {SIGSYS,    "31-SIGSYS"   }
};

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 ", sig_info->si_pid, " 的信号 ", m[sig]);
}

void handle_signal(int sig) {
    log("子进程捕捉到信号 ", m[sig]);
}

void handle_signal_1(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGCHLD, 来自: ", sig_info->si_pid);
    int fd = waitpid(-1, NULL, WNOHANG);
    if (fd > 0) {
        log("已退出的子进程是: ", fd);
    }
}

void handle_signal_2(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGCHLD 来自: ", sig_info->si_pid);
    for (;;) {
        int fd = waitpid(-1, NULL, WNOHANG);
        if (fd <= 0)
            break;
        log("已退出的子进程是: ", fd);
    }
}

int count = 0;

void handle_signal_3(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGUSR1 第 " + std::to_string(++count) + " 次");
}

void handle_signal_4(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 " + m[sig] + " 第 " + std::to_string(++count) + " 次");
    log("处理信号 " + m[sig] + " 中...");
    sleep(2);
    log("处理信号 " + m[sig] + " 完成");
}

void handle_signal_5(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 " + m[sig]);
    log("处理信号 " + m[sig] + " 中...");
    sleep(2);
    log("处理信号 " + m[sig] + " 完成");
}

jmp_buf buf;

void handle_signal_6(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGABRT");
    longjmp(buf, 1);
}

// 测试信号
void test_signal_01() {
    log();
    log("测试信号阻塞");
    log();

    log("阻塞所有信号");
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    log("查看被阻塞的信号");
    sigset_t old_mask;
    sigprocmask(SIG_SETMASK, NULL, &old_mask);

    for (auto key : m)
        if (sigismember(&old_mask, key.first))
            log("已被阻塞的信号: " + m[key.first]);

    log("发送除 " + m[SIGKILL] + " 和 " + m[SIGSTOP] + " 外的所有信号");

    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            kill(getpid(), key.first);

    log("查看待决的信号");
    sigset_t new_mask;
    sigpending(&new_mask);
    for (auto key : m)
        if (sigismember(&new_mask, key.first))
            log("待决的信号: " + m[key.first]);

    log();
    log("主进程正常退出");
    log();
}

// 测试信号
void test_signal_02() {
    log();
    log("测试信号优先级");
    log();

    log("注册所有的信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;

    log("设置信号处理过程中阻塞所有信号");
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    for (auto key : m) {
        sigaction(key.first, &act, NULL);
    }

    log("阻塞所有信号");
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    log("发送除 " + m[SIGKILL] + " 和 " + m[SIGSTOP] + " 外的所有信号");

    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            kill(getpid(), key.first);

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_03() {
    count = 0;

    log();
    log("测试信号不可靠: 多个信号处于待决状态信号会丢失");
    log();

    log("注册信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal_3;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);

    log("阻塞信号 SIGUSR1");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    for (int i = 1; i <= 5; ++i) {
        log("发送信号 SIGUSR1 第 " + std::to_string(i) + " 次");
        kill(getpid(), SIGUSR1);
    }

    log("解除信号 SIGUSR1 阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_04() {
    count = 0;

    log();
    log("测试信号不可靠: 信号处理函数被重置");
    log();

    log("注册信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal_3;
    sigemptyset(&act.sa_mask);

    log("设置信号触发后被重置");
    act.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigaction(SIGUSR1, &act, NULL);

    log("发送信号 SIGUSR1 第 1 次");
    kill(getpid(), SIGUSR1);
    sleep(1);
    log("发送信号 SIGUSR1 第 2 次");
    kill(getpid(), SIGUSR1);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_05() {
    count = 0;

    log();
    log("测试信号处理过程中相同的信号到达");
    log();

    log("设置信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal_4;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 " + m[SIGUSR1] + " 第 1 次");
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 " + m[SIGUSR1] + " 第 2 次");
        kill(fd, SIGUSR1);
        log("发送信号 " + m[SIGUSR1] + " 第 3 次");
        kill(fd, SIGUSR1);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("主进程正常退出");
    log();
}

void test_signal_06() {
    log();
    log("测试信号处理过程中不同的信号到达");
    log();

    log("设置信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal_5;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 " + m[SIGUSR1]);
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 " + m[SIGUSR2]);
        kill(fd, SIGUSR2);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("主进程正常退出");
    log();
}

void test_signal_07() {
    log();
    log("测试信号处理过程中阻塞其他信号");
    log();

    log("设置信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal_5;
    sigemptyset(&act.sa_mask);

    log("设置信号处理过程中阻塞 SIGUSR2");
    sigaddset(&act.sa_mask, SIGUSR2);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        for (;;)
            ;
    } else {
        sleep(1);
        log("发送信号 " + m[SIGUSR1]);
        kill(fd, SIGUSR1);
        sleep(1);
        log("发送信号 " + m[SIGUSR2]);
        kill(fd, SIGUSR2);
        sleep(5);
        kill(fd, SIGKILL);
    }

    log();
    log("主进程正常退出");
    log();
}

void test_signal_08() {
    log();
    log("测试信号 SIGABRT 处理为 SIG_DFL");
    log();

    log("设置 SIGABRT 处理为 SIG_DFL");
    signal(SIGABRT, SIG_DFL);

    log("调用 abort()");
    abort();

    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_09() {
    log();
    log("测试信号 SIGABRT 处理为 SIG_IGN");
    log();

    log("设置 SIGABRT 处理为 SIG_IGN");
    signal(SIGABRT, SIG_IGN);

    log("调用 abort()");
    abort();

    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_10() {
    log();
    log("测试信号 SIGABRT 处理为 捕获信号并返回");
    log();

    log("设置 SIGABRT 处理为 捕获信号并返回");
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO;
    sigaction(SIGABRT, &act, NULL);

    log("调用 abort()");
    abort();

    log();
    log("主进程正常退出");
    log();
}

void test_signal_11() {
    log();
    log("测试信号 SIGABRT 处理为 捕获信号不返回");
    log();

    log("设置 SIGABRT 处理为 捕获信号不返回");
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal_6;
    act.sa_flags     = SA_SIGINFO;
    sigaction(SIGABRT, &act, NULL);

    if (setjmp(buf) == 0) {
        log("调用 abort()");
        abort();
    }

    log();
    log("主进程正常退出");
    log();
}

void test_signal_12() {
    log();
    log("测试信号 SIGFPE 处理为 捕获信号并返回");
    log();

    log("设置 SIGFPE 处理为 捕获信号并返回");
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO;
    sigaction(SIGFPE, &act, NULL);

    log("整数除以 0");
    int a = 0;
    int b = 1 / a;
    log(std::to_string(b));

    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_13() {
    log();
    log("测试信号: 子进程状态变化时, 父进程的处理");
    log();

    log("注册信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        // 子进程
        log("子进程启动");
        sleep(2);
        log("子进程退出");
        return;
    } else {
        // 父进程
        sleep(1);
        log("发送信号使子进程暂停");
        kill(fd, SIGTSTP);
        sleep(1);
        log("发送信号使子进程继续");
        kill(fd, SIGCONT);
    }
    sleep(1);
    sleep(1);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_14() {
    log();
    log("测试信号: 子进程状态变化时, 父进程的处理");
    log("不接收子进程暂停继续产生的 SIGCHLD");
    log();

    log("注册信号处理");
    log("设置不接受子进程暂停继续产生的 SIGCHLD");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &act, NULL);

    pid_t fd = fork();
    if (fd == 0) {
        // 子进程
        log("子进程启动");
        sleep(2);
        log("子进程退出");
        return;
    } else {
        // 父进程
        sleep(1);
        log("发送信号使子进程暂停");
        kill(fd, SIGTSTP);
        sleep(1);
        log("发送信号使子进程继续");
        kill(fd, SIGCONT);
    }
    sleep(1);
    sleep(1);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

void test_signal_15() {
    log();
    log("信号测试: 捕捉所有信号, 死循环");
    log();

    log("注册所有信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_NOCLDWAIT | SA_RESTART;
    for (auto key : m) {
        sigaction(key.first, &act, NULL);
    }

    std::string cmd = "ps -o pid,ppid,pgid,sid,comm -p ";
    cmd += std::to_string(getpid()) + ",";
    cmd += std::to_string(getppid());
    log("进程状态");
    system(cmd.data());

    log("主进程死循环");
    for (;;)
        ;

    log();
    log("主进程正常退出");
    log();
}

void test_signal() {
    // 测试信号阻塞
    // test_signal_01();

    // 测试信号优先级
    // test_signal_02();

    // 测试信号不可靠: 多个信号处于待决状态信号会丢失
    // test_signal_03();

    // 测试信号不可靠: 信号处理函数被重置
    // test_signal_04();

    // 测试信号处理过程中相同的信号到达
    // test_signal_05();

    // 测试信号处理过程中不同的信号到达
    // test_signal_06();

    // 测试信号处理过程中阻塞其他信号
    // test_signal_07();

    // 测试信号 SIGABRT 处理为 SIG_DFL
    // test_signal_08();

    // 测试信号 SIGABRT 处理为 SIG_IGN
    // test_signal_09();

    // 测试信号 SIGABRT 处理为 捕获信号并返回
    // test_signal_10();

    // 测试信号 SIGABRT 处理为 捕获信号不返回
    // test_signal_11();

    // 测试信号 SIGFPE 处理为 捕获信号并返回
    // test_signal_12();

    // 测试信号: 子进程状态变化时, 父进程的处理
    // test_signal_13();

    // 测试信号: 子进程状态变化时, 父进程的处理
    // 设置不接收子进程暂停继续产生的 SIGCHLD
    // test_signal_14();

    // 信号测试: 捕捉所有信号, 死循环
    // test_signal_15();
}

// 测试僵尸进程
void test_zombie_1() {
    log();
    log("重现僵尸进程的产生: 父进程未处理子进程退出的状态信息");
    log();

    pid_t fd = fork();

    if (fd == 0) {
        log("子进程已启动: ", getpid());
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(fd);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程:", fd);
    kill(fd, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_2() {
    log();
    log("重新僵尸进程的产生: 父进程未正确处理子进程退出的状态信息");
    log();

    log("设置 SIGCHLD 处理为: 调用 waitpid() 一次");
    struct sigaction act;
    act.sa_sigaction = handle_signal_1;
    act.sa_flags     = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    std::string cmd = "ps -o pid,comm,state -p ";

    for (int i = 1; i <= 5; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动后退出: ", getpid());
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_3() {
    log();
    log("预防僵尸进程的产生: 忽略信号 SIGCHLD");
    log();

    log("设置 SIGCHLD 的信号处理");
    signal(SIGCHLD, SIG_IGN);

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    std::string cmd = "ps -o pid,comm,state -p ";

    for (int i = 1; i <= 5; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动后退出: ", getpid());
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_4() {
    log();
    log("预防僵尸进程的产生: 设置 SIGCHLD 处理为 循环调用 waitpid");
    log();

    log("设置 SIGCHLD 的信号处理: 循环调用 waitpid");
    struct sigaction act;
    act.sa_sigaction = handle_signal_2;
    act.sa_flags     = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    std::string cmd = "ps -o pid,comm,state -p ";

    for (int i = 1; i <= 5; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动后退出: ", getpid());
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_5() {
    log();
    log("预防僵尸进程的产生: 设置 SIGCHLD 选项为 SA_NOCLDWAIT");
    log();

    log("设置 SIGCHLD 的信号选项: SA_NOCLDWAIT");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO | SA_NOCLDWAIT;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    std::string cmd = "ps -o pid,comm,state -p ";

    for (int i = 1; i <= 5; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动后退出: ", getpid());
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_6() {
    log();
    log("预防僵尸进程的产生: 杀死父进程");
    log();

    if (fork() == 0) {
        pid_t fd = fork();
        if (fd == 0) {
            log("测试的子进程启动: ", getpid());
            for (;;)
                ;
        } else if (fork() == 0) {
            log("测试的控制进程启动: ", getpid());
            sleep(1);
            std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(fd);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的父进程: ", getppid());
            kill(getppid(), SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的子进程: ", fd);
            kill(fd, SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            return;
        } else {
            log("测试的父进程启动: ", getpid());
            for (;;)
                ;
        }
    }

    sleep(4);

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_7() {
    log();
    log("销毁僵尸进程: 杀死僵尸进程的父进程");
    log();

    if (fork() == 0) {
        pid_t fd = fork();

        if (fd == 0) {
            log("测试的子进程启动: ", getpid());
            for (;;)
                ;
        } else if (fork() == 0) {
            log("测试的控制进程启动: ", getpid());
            sleep(1);
            std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(fd);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的子进程: ", fd);
            kill(fd, SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的父进程: ", getppid());
            kill(getppid(), SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            return;
        } else {
            log("测试的父进程启动: ", getpid());
            for (;;)
                ;
        }
    }

    sleep(4);

    log();
    log("主进程正常退出");
    log();
}

void test_zombie_8() {
    log();
    log("测试: 产生僵尸进程不退出");
    log();

    pid_t child = fork();

    if (child == 0) {
        exit(0);
    }
    sleep(1);  // 保证子进程已启动并退出
    log("产生僵尸进程: ", child);
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    system(cmd.data());

    log("死循环...");
    for (;;)
        ;

    log();
    log("主进程正常退出");
    log();
}

void test_zombie() {
    // 重现僵尸进程的产生: 父进程未处理子进程退出的状态信息
    // test_zombie_1();
    // 重新僵尸进程的产生: 父进程未正确处理子进程退出的状态信息
    // test_zombie_2();
    // 预防僵尸进程的产生: 忽略信号 SIGCHLD
    // test_zombie_3();
    // 预防僵尸进程的产生: 设置 SIGCHLD 处理为 循环调用 waitpid");
    // test_zombie_4();
    // 预防僵尸进程的产生: 设置 SIGCHLD 选项为 SA_NOCLDWAIT
    // test_zombie_5();
    // 预防僵尸进程的产生: 杀死父进程
    // test_zombie_6();
    // 销毁僵尸进程: 杀死僵尸进程的父进程
    // test_zombie_7();
    // 测试: 产生僵尸进程不退出
    // test_zombie_8();
}

// 测试进程
void test_process() {
    test_zombie();  // 测试僵尸进程
}

// 测试孤儿进程
void test_orphan_process() {
    log();
    log("测试孤儿进程");
    log();

    if (fork() == 0) {
        if (fork() == 0) {
            // 测试的子进程
            sleep(1);
            log("测试的子进程启动: " + std::to_string(getpid()));
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(getpid()) + "," + std::to_string(getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(getpid()) + "," + std::to_string(getppid());
            log("进程状态");
            system(cmd.data());
            return;
        } else {
            // 测试的父进程
            log("测试的父进程启动: " + std::to_string(getpid()));
            for (;;)
                ;
        }
    }

    sleep(3);

    log();
    log("主进程正常退出");
    log();
}

// 测试孤儿进程组
void test_orphan_process_group() {
    log();
    log("测试孤儿进程组");
    log();

    log("设置信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGCONT, &act, NULL);

    pid_t main_pid = getpid();
    if (fork() == 0) {
        // 测试的父进程
        log("测试的父进程启动: " + std::to_string(getpid()));
        log("设置新的进程组: " + std::to_string(getpid()));
        setpgid(getpid(), getpid());
        pid_t child_1 = fork();
        if (child_1 == 0) {
            // 测试的第一个子进程
            log("测试的第一个子进程启动: " + std::to_string(getpid()));
            log("测试的第一个子进程使自己暂停");
            kill(getpid(), SIGSTOP);
            for (;;)
                ;
        } else if (fork() == 0) {
            // 测试的第二个子进程
            sleep(1);
            log("测试的第二个子进程启动: " + std::to_string(getpid()));
            log("进程状态");
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(main_pid) + ",";
            cmd += std::to_string(child_1) + ",";
            cmd += std::to_string(getpid()) + ",";
            cmd += std::to_string(getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死测试的父进程: " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            sleep(1);
            cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            cmd += std::to_string(main_pid) + ",";
            cmd += std::to_string(child_1) + ",";
            cmd += std::to_string(getpid()) + ",";
            cmd += std::to_string(getppid());
            log("进程状态");
            system(cmd.data());
            log("杀死测试的第一个子进程: " + std::to_string(child_1));
            kill(child_1, SIGKILL);
            log("测试的第二个子进程退出");
            return;
        } else {
            // 父进程
            for (;;)
                ;
        }
    }

    sleep(3);

    log();
    log("主进程正常退出");
    log();
}

// 展示 PID PGID SID
void show_pid_pgid_sid(pid_t pid) {
    log("进程 ", pid, " 进程组 ", getpgid(pid), " 会话 ", getsid(pid));
}

// 测试 PGID
void test_pgid(pid_t pid, pid_t pgid) {
    show_pid_pgid_sid(pid);

    std::string msg = to_string("修改进程组 ", getpgid(pid), " => ", pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show_pid_pgid_sid(pid);
}

void test_pgid() {
    log();
    log("测试进程组: 新建自身进程对应的进程组");

    test_pgid(getpid(), getpid());
    if (fork() == 0) {
        test_pgid(getpid(), getpid());
        exit(-1);
    }
    sleep(1);

    log();
    log("测试进程组: 新建父进程对应的进程组");

    if (fork() == 0) {
        // 测试的父进程
        if (fork() == 0) {
            // 测试的子进程
            log("新建父进程的进程组: ", getppid());
            test_pgid(getppid(), getppid());
            kill(getppid(), SIGKILL);
            exit(-1);
        }
        for (;;)
            ;
    }
    sleep(1);

    log();
    log("测试进程组: 新建子进程对应的进程组(子进程属于不同的会话)");

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程新建会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("父进程会话: ", getsid(getpid()));
    log("子进程会话: ", getsid(fd));
    log("新建子进程的进程组: ", fd);
    test_pgid(fd, fd);
    kill(fd, SIGKILL);

    sleep(1);

    log();
    log("测试进程组: 新建子进程对应的进程组(子进程调用exec之后)");

    fd = fork();
    if (fd == 0) {
        log("子进程调用exec");
        execl("/usr/bin/sleep", "sleep", "3", NULL);
        log("子进程失败");
        exit(-1);
    }
    sleep(1);
    log("新建子进程的进程组: ", fd);
    test_pgid(fd, fd);
    kill(fd, SIGKILL);

    sleep(1);

    log();
    log("测试进程组: 新建子进程对应的进程组(其他情况)");

    fd = fork();
    if (fd == 0) {
        for (;;)
            ;
    }
    sleep(1);
    log("新建子进程的进程组: ", fd);
    test_pgid(fd, fd);
    kill(fd, SIGKILL);

    sleep(1);

    log();
    log("操作系统-进程组: 新建孙进程对应的进程组");

    int pipefd[2];
    pipe(pipefd);
    pid_t child = fork();
    if (child == 0) {
        pid_t grandchild = fork();

        if (grandchild == 0) {
            // 测试的孙进程
            close(pipefd[0]);
            close(pipefd[1]);
            for (;;)
                ;
        } else {
            // 测试的子进程
            close(pipefd[0]);
            std::string str = std::to_string(grandchild);
            write(pipefd[1], str.data(), str.size());
            close(pipefd[1]);
            for (;;)
                ;
        }
    } else {
        // 测试的父进程
        close(pipefd[1]);

        char        ch;
        std::string str;

        while (read(pipefd[0], &ch, 1) > 0) {
            str.push_back(ch);
        }
        pid_t grandchild = atoi(str.data());

        log("进程关系");
        std::string cmd = "ps -o pid,ppid,pgid,sid,comm -p";
        cmd += std::to_string(child) + ",";
        cmd += std::to_string(grandchild) + ",";
        cmd += std::to_string(getpid());
        system(cmd.data());
        log("修改孙进程的进程组: " + str);
        test_pgid(grandchild, grandchild);

        kill(child, SIGKILL);
        kill(grandchild, SIGKILL);
    }

    log();
    log("测试进程组: 新建会话首进程对应的的进程组");

    if (fork() == 0) {
        log("创建新会话");
        setsid();
        test_pgid(getpid(), getpid());
        exit(-1);
    }
    sleep(1);

    log();
    log("测试进程组: 测试修改进程组(原进程组和目标进程组属于不同会话)");

    fd = fork();

    if (fd == 0) {
        log("子进程创建新会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("子进程的状态信息");
    test_pgid(getpid(), fd);
    sleep(1);

    log();
    log("主进程正常退出");
    log();
}

// 测试会话
void test_sid_help() {
    show_pid_pgid_sid(getpid());

    std::string msg = "新建会话";
    if (setsid() < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show_pid_pgid_sid(getpid());
}

void test_sid() {
    log();
    log("测试进程组的首进程建立新会话");
    test_sid_help();

    log();
    log("测试不是进程组的首进程建立新会话");

    if (fork() == 0) {
        test_sid_help();
        exit(-1);
    }

    sleep(1);

    log();
    log("测试会话销毁: 会话不和终端绑定");

    if (fork() == 0) {
        log("建立新会话");
        test_sid_help();
        if (fork() == 0) {
            log("新会话的子进程");
            log("当前进程和父进程的信息");
            show_pid_pgid_sid(getpid());
            show_pid_pgid_sid(getppid());
            log("杀死父进程(会话首进程): " + std::to_string(getppid()));
            if (kill(getppid(), SIGKILL) < 0) {
                perror("");
            }
            sleep(1);
            log("当前进程和父进程的信息");
            show_pid_pgid_sid(getpid());
            show_pid_pgid_sid(getppid());
            exit(-1);
        } else {
            for (;;)
                ;
        }
    }

    sleep(3);

    log();
    log("主进程正常退出");
    log();
}

// 测试宏
int v123 = 123456;

#define TEST_MACRO_STR(fmt, X) printf(fmt, #X, X)
#define TEST_MACRO_CAT(fmt, X) printf(fmt, v##X)
// 可变参数, 如果可变参数不存在, 去掉前面的逗号
#define TEST_MACRO(fmt, ...) printf(fmt, ##__VA_ARGS__)

void test_macro() {
    TEST_MACRO_STR("测试宏变字符串: %s -> %d\n", 123);
    TEST_MACRO_CAT("测试    宏连接: %d\n", 123);
    TEST_MACRO("测试宏有可变参数: %d\n", 123);
    TEST_MACRO("测试宏无可变参数\n");
}

// 测试可变参数
//    printf() -- 输出到标准输出
//   fprintf() -- 输出到标准IO
//   dprintf() -- 输出到文件描述符
//   sprintf() -- 输出到字符串
//  snprintf() -- 输出到字符串
//
//   vprintf() -- 使用可变参数 va
//  vfprintf() -- 使用可变参数 va
//  vdprintf() -- 使用可变参数 va
//  vsprintf() -- 使用可变参数 va
// vsnprintf() -- 使用可变参数 va
//
//  __VA_ARGS__  -- 只能在宏中使用, 代替可变参数
//
//  va_start -- 初始化
//  va_arg   -- 获取下一个可变参数
//  va_copy  -- 拷贝
//  va_end   -- 清空
//

#define TEST_VA(fmt, ...) printf(fmt, ##__VA_ARGS__)

void test_va_c(const char* s, ...) {
    va_list ap;
    va_start(ap, s);
    vprintf(s, ap);
    va_end(ap);
}

void test_va_cpp() {
}

template <typename T, typename... Args>
void test_va_cpp(T t, Args... args) {
    std::cout << t;
    test_va_cpp(args...);
}

void test_va() {
    TEST_VA("测试 C 风格的可变参数: %s -> %s\n", "123", "456");
    test_va_c("测试 C 风格的可变参数: %s -> %s\n", "123", "456");
    test_va_cpp("测试 C++ 风格的可变参数: ", "123", " -> ", "456", "\n");
}

// 测试退出
class A {
  public:
    A() {
        std::cout << "调用构造函数" << std::endl;
    }

    ~A() {
        std::cout << "调用析构函数" << std::endl;
    }
};

void test_1() {
    std::cout << "测试函数-1" << std::endl;
}

void test_2() {
    std::cout << "测试函数-2" << std::endl;
}

void test_atexit() {
    std::cout << "注册退出函数" << std::endl;
    atexit(test_1);
    atexit(test_1);
    atexit(test_2);
    atexit(test_2);
}

void test_exit() {
    if (fork() == 0) {
        std::cout << "测试 exit" << std::endl;
        A a;
        test_atexit();
        std::cout << "退出" << std::endl;
        exit(0);
    }

    sleep(1);
    std::cout << std::endl;

    if (fork() == 0) {
        std::cout << "测试 _exit" << std::endl;
        A a;
        test_atexit();
        std::cout << "退出" << std::endl;
        _exit(0);
    }

    sleep(1);
    std::cout << std::endl;

    if (fork() == 0) {
        std::cout << "测试正常退出" << std::endl;
        A a;
        test_atexit();
        std::cout << "退出" << std::endl;
        return;
    }

    sleep(1);
}

// 测试跨函数跳转

jmp_buf buf_jmp;

void test_jmp(int v) {
    if (v == 0) {
        longjmp(buf_jmp, 3);
    }

    if (v == 3) {
        if (setjmp(buf_jmp) == 0) {
            log("第一次经过, v = ", v);
        } else {
            log("再一次经过, v = ", v);
            return;
        }
    }
    log("参数: v = ", v);
    test_jmp(v - 1);
}

void test_jmp() {
    log("测试 jmp");
    test_jmp(10);
}

// 测试资源限制

#define TEST_LIMIT(X)                   \
    {                                   \
        struct rlimit rlim;             \
        getrlimit(X, &rlim);            \
        log(#X);                        \
        log("软限制: ", rlim.rlim_cur); \
        log("硬限制: ", rlim.rlim_max); \
        log();                          \
    }

void test_limit() {
    log("测试资源限制: ");
    log();
    TEST_LIMIT(RLIMIT_CPU);
    TEST_LIMIT(RLIMIT_CORE);
}

// 测试 vfork
void test_vfork_help() {
    std::string str = "123";
    std::cout << "调用 vfork 前为: " << str << std::endl;
    if (vfork() == 0) {
        str = "456";
        std::cout << "vfork 内修改为: " << str << std::endl;
        exit(0);
    }
    std::cout << "调用 vfork 后为: " << str << std::endl;
}

void test_vfork() {
    std::string str = "123";
    std::cout << "上一层函数调用前为: " << str << std::endl;
    test_vfork_help();
    std::cout << "上一层函数调用后为: " << str << std::endl;
}

//  fork()
// vfork()
//
// getpid()  -- 进程 ID
// getppid() -- 父进程 ID
// getuid()  -- 实际用户
// geteuid() -- 有效用户
// getgid()  -- 实际组
// getegid() -- 有效组
//
// setuid(uid) -- 进程  具有超级权限时, 设置 实际的 有效的 保存的用户 ID 为 uid
//             -- 进程不具有超级权限时, uid 等于 实际的 ID 或 保存的用户 ID 时,
//             将有效的 ID 改为 uid
// setgid()    -- 和上述类似

void test_process_01() {
    log();
    log("测试进程: 可被信号打断的休眠(指被捕获的信号)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程启动");

        log("子进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);

        log("子进程休眠10秒");
        sleep(10);
        log("子进程休眠完成");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        wait(NULL);
    }

    log();
    log("主进程正常退出");
    log();
}

void test_process_02() {
    log();
    log("测试进程: 不可被信号打断的休眠(指被捕获的信号)");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("测试的父进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);
        if (vfork() == 0) {
            log("测试的子进程启动");
            log("测试的子进程休眠10秒");
            sleep(10);
            log("测试的子进程休眠完成");
            log("测试的子进程退出");
            exit(-1);
        }
        log("测试的父进程休眠1s");
        sleep(1);
        log("测试的父进程退出");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");
    log();
}

void test_process_03() {
    log();
    log("测试进程: 不可被信号打断的休眠(指被捕获的信号)");
    log("对 SIGSTOP 的处理");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        if (vfork() == 0) {
            log("测试的子进程启动");
            log("测试的子进程休眠10秒");
            sleep(10);
            log("测试的子进程休眠完成");
            log("测试的子进程退出");
            exit(-1);
        }
        log("测试的父进程休眠1s");
        sleep(1);
        log("测试的父进程退出");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGSTOP");
        kill(fd, SIGSTOP);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGCONT");
        kill(fd, SIGCONT);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");
    log();
}

void test_process_04() {
    log();
    log("测试进程: 不可被信号打断的休眠(指被捕获的信号)");
    log("对 SIGKILL 的处理");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        if (vfork() == 0) {
            log("测试的子进程启动");
            log("测试的子进程休眠10秒");
            sleep(10);
            log("测试的子进程休眠完成");
            log("测试的子进程退出");
            exit(-1);
        }
        log("测试的父进程休眠1s");
        sleep(1);
        log("测试的父进程退出");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGKILL");
        kill(fd, SIGKILL);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());
        wait(NULL);
    }

    sleep(10);

    log();
    log("主进程正常退出");
    log();
}

void test_process_05() {
    log();
    log("测试进程: 暂停 => 继续");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);
        for (;;)
            ;
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("使子进程暂停");
        kill(fd, SIGSTOP);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGCONT");
        kill(fd, SIGCONT);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGKILL");
        kill(fd, SIGKILL);
        sleep(1);
        log("子进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");
    log();
}

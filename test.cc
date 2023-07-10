
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

/********************************
 *
 *         公共函数
 *
 ********************************/
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

/*****************************
 *
 *          测试信号
 *
 *****************************/
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

/****************************************
 *
 *              测试进程
 *
 ****************************************/

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
    test_zombie_8();
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

void test_env() {
    log("环境变量 PATH: ", getenv("PATH"));
    log("修改环境变量");
    char str[] = "PATH=LYB";
    putenv(str);
    log("环境变量 PATH: ", getenv("PATH"));
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

// 测试退出
class A {
  public:
    A() {
        log("调用构造函数");
    }

    ~A() {
        log("调用析构函数");
    }
};

void test_1() {
    log("测试函数-1");
}

void test_2() {
    log("测试函数-2");
}

void test_atexit() {
    log("注册退出函数");
    atexit(test_1);
    atexit(test_1);
    atexit(test_2);
    atexit(test_2);
}

void test_exit() {
    if (fork() == 0) {
        log("测试 exit");
        A a;
        test_atexit();
        log("退出");
        exit(0);
    }

    sleep(1);
    log();

    if (fork() == 0) {
        log("测试 _exit");
        A a;
        test_atexit();
        log("退出");
        _exit(0);
    }

    sleep(1);
    log();

    if (fork() == 0) {
        log("测试正常退出");
        A a;
        test_atexit();
        log("退出");
        return;
    }

    sleep(1);
}

// 测试资源限制

/*
 * ulimit -c -------- 查看 core 文件大小的软限制
 * ulimit -d -------- 限制程序数据段的大小
 * ulimit -e -------- 限制程序优先级
 * ulimit -f -------- 限制文件大小
 * ulimit -i -------- 限制待决的信号的数量
 * ulimit -l -------- 限制加锁的内存大小
 * ulimit -m -------- 限制物理内存大小
 * ulimit -n -------- 限制打开文件的最大个数
 * ulimit -p -------- 限制匿名管道的缓冲大小 -- 可能没有设置
 * ulimit -q -------- 限制消息队列的大小
 * ulimit -r -------- 限制任务调度优先级
 * ulimit -R -------- 限制任务调度时, CPU 大最大使用时间
 * ulimit -s -------- 限制栈大小
 * ulimit -t -------- 限制 CPU 总的使用时间
 * ulimit -u -------- 限制进程数
 * ulimit -v -------- 限制虚拟内存大小
 * ulimit -x -------- 限制文件锁的个数
 */

#define TEST_LIMIT(name, X)                 \
    {                                       \
        struct rlimit rlim;                 \
        getrlimit(X, &rlim);                \
        log(name, ": ", #X);                \
        if (rlim.rlim_cur == RLIM_INFINITY) \
            log("软限制: ", "不限制");      \
        else                                \
            log("软限制: ", rlim.rlim_cur); \
        if (rlim.rlim_max == RLIM_INFINITY) \
            log("硬限制: ", "不限制");      \
        else                                \
            log("硬限制: ", rlim.rlim_max); \
        log();                              \
    }

void test_limit() {
    log();
    log("测试资源限制: ");
    log();
    TEST_LIMIT("虚拟内存大小", RLIMIT_AS);
    TEST_LIMIT("core 文件大小", RLIMIT_CORE);
    TEST_LIMIT("CPU 总的时间大小", RLIMIT_CPU);
    TEST_LIMIT("数据段(初始化数据, 未初始化数据, 堆)", RLIMIT_DATA);
    TEST_LIMIT("文件大小", RLIMIT_FSIZE);
    TEST_LIMIT("文件锁的个数", RLIMIT_LOCKS);
    TEST_LIMIT("内存中可以锁定的大小", RLIMIT_MEMLOCK);
    TEST_LIMIT("消息队列的大小", RLIMIT_MSGQUEUE);
    TEST_LIMIT("进程优先级的上限", RLIMIT_NICE);
    TEST_LIMIT("文件描述符的最大限制", RLIMIT_NOFILE);
    TEST_LIMIT("用户的进程线程数", RLIMIT_NPROC);
    TEST_LIMIT("物理内存大小", RLIMIT_RSS);
    TEST_LIMIT("调度的优先级", RLIMIT_RTPRIO);
    TEST_LIMIT("调度时 CPU 的最大耗时 毫秒", RLIMIT_RTTIME);
    TEST_LIMIT("信号队列的长度", RLIMIT_SIGPENDING);
    TEST_LIMIT("栈大小", RLIMIT_STACK);
}

void test_process_status_01() {
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

void test_process_status_02() {
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

void test_process_status_03() {
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

void test_process_status_04() {
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

void test_process_status_05() {
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

// 测试进程状态
void test_process_status() {
    // 测试进程: 可被信号打断的休眠(指被捕获的信号)
    // test_process_status_01();

    // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
    // test_process_status_02();

    // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
    // 对 SIGSTOP 的处理
    // test_process_status_03();

    // 测试进程: 不可被信号打断的休眠(指被捕获的信号)
    // 对 SIGKILL 的处理
    // test_process_status_04();

    // 测试进程: 暂停 -> 继续
    test_process_status_05();
}

void test_process() {
    // 测试僵尸进程
    // test_zombie();

    // 测试孤儿进程
    // test_orphan_process();

    // 测试孤儿进程组
    // test_orphan_process_group();

    // 测试进程组
    // test_pgid();

    // 测试会话
    // test_sid();

    // 测试环境变量
    // test_env();

    // 测试跨函数跳转
    // test_jmp();

    // 测试退出
    // test_exit();

    // 测试资源限制
    // test_limit();

    // 测试进程状态
    test_process_status();
}

int main() {
    test_signal();   // 测试信号
    test_process();  // 测试进程

    //    test_cpp();      // 测试 cpp

    return 0;
}

// 测试 vfork
void test_vfork_help() {
    std::string str = "123";
    log("调用 vfork 前为: ", str);
    if (vfork() == 0) {
        str = "456";
        log("vfork 内修改为: ", str);
        exit(0);
    }
    log("调用 vfork 后为: ", str);
}

void test_vfork() {
    std::string str = "123";
    log("上一层函数调用前为: ", str);
    test_vfork_help();
    log("上一层函数调用后为: ", str);
}

// 测试进程
void test_process_1() {
    // 测试 vfork
    // test_vfork();
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

/****************************************
 *
 *              测试 C++
 *
 ****************************************/

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

void test_cpp() {
    // 测试宏
    // test_macro();

    // 测试可变参数
    // test_va();
}

/****************************************
 *
 *              测试计算机存储
 *
 ****************************************/

#if 0

template <typename T>
union Node {
    char str[sizeof(T)];
    T    t;
};

template <typename T>
void test(const std::string& str, T v) {
    Node<T> node;
    node.t = v;

    std::string msg = str + " ";
    for (size_t i = 0; i < sizeof(T); ++i) {
        if (i != 0 && i % 4 == 0) {
            msg += "\n" + std::string(58, ' ');
        }
        msg += std::bitset<8>(node.str[i]).to_string() + " ";
    }
    log(msg);
}

int main() {
    log();
    log("测试字节序");
    log();

    test("测试        char 存储数字 1 => ", (char)1);
    test("测试       short 存储数字 1 => ", (short)1);
    test("测试         int 存储数字 1 => ", (int)1);
    test("测试        long 存储数字 1 => ", (long)1);
    test("测试 long   long 存储数字 1 => ", (long long)1);
    test("测试       float 存储数字 1 => ", (float)1);
    test("测试      double 存储数字 1 => ", (double)1);
    test("测试 long double 存储数字 1 => ", (long double)1);
    test("测试     wchar_t 存储数字 1 => ", (wchar_t)1);
    //    test("测试     char8_t 存储数字 1 => ", (char8_t)1); C++20
    test("测试    char16_t 存储数字 1 => ", (char16_t)1);
    test("测试    char32_t 存储数字 1 => ", (char32_t)1);

    Node<short> node;
    node.t = 1;

    std::string msg = "测试本机的大小端 => ";
    msg += node.str[0] == 1 ? "小端存储" : "大端存储";
    log(msg);

    log();
    log("主进程正常退出");
    log();
    return 0;
}

void test(const std::string& str, int x, int y) {
    log();
    log("测试: " + str);
    log("求商: " + std::to_string(x / y));
    log("求余: " + std::to_string(x % y));
    log();
}

int main() {
    log();
    log("测试整数溢出以及除法的符号");
    log();

    int x = std::numeric_limits<int>::max();
    log("测试有符号整数max      : " + std::to_string(x));
    x = x + 10;
    log("测试有符号整数max + 10 : " + std::to_string(x));

    unsigned y = std::numeric_limits<unsigned int>::max();
    log("测试无符号整数max      : " + std::to_string(y));
    y = y + 10;
    log("测试无符号整数max + 10 : " + std::to_string(y));

    test("5/2", 5, 2);
    test("5/-2", 5, -2);
    test("-5/2", -5, 2);
    test("-5/-2", -5, -2);

    log();
    log("主进程正常退出");
    log();
    return 0;
}

int main() {
    log();
    log("测试保留小数时的四舍六入五取偶");
    log();

    log("        舍入方向: " + dict_round[fegetround()]);
    test_double(
        "测试保留小数时的 五进",
        "0 01111111100 0000000000000000000000000000000000000000000000000001");
    test_double(
        "测试保留小数时的 五取偶(舍)",
        "0 01111111100 0000000000000000000000000000000000000000000000000000");
    test_double(
        "测试保留小数时的 五取偶(入)",
        "0 01111111101 1000000000000000000000000000000000000000000000000000");

    log();
    log("主进程正常退出");
    log();
    return 0;
}

int main() {
    log();
    log("测试存储时的四舍六入五取偶");
    log();

    log("        舍入方向: " + dict_round[fegetround()]);

    test_double(
        "测试 最后一位是 0, 多余位是 00(舍)",
        "0100001100110000000000000000000000000000000000000000000000000000 00");

    test_double(
        "测试 最后一位是 0, 多余位是 01(舍)",
        "0100001100110000000000000000000000000000000000000000000000000000 01");

    test_double(
        "测试 最后一位是 0, 多余位是 10(舍, 取偶)",
        "0100001100110000000000000000000000000000000000000000000000000000 10");

    test_double(
        "测试 最后一位是 0, 多余位是 11(入)",
        "0100001100110000000000000000000000000000000000000000000000000000 11");

    test_double(
        "测试 最后一位是 1, 多余位是 00(舍)",
        "0100001100110000000000000000000000000000000000000000000000000001 00");

    test_double(
        "测试 最后一位是 1, 多余位是 01(舍)",
        "0100001100110000000000000000000000000000000000000000000000000001 01");

    test_double(
        "测试 最后一位是 1, 多余位是 10(入, 取偶)",
        "0100001100110000000000000000000000000000000000000000000000000001 10");

    test_double(
        "测试 最后一位是 1, 多余位是 11(入)",
        "0100001100110000000000000000000000000000000000000000000000000001 11");

    log();
    log("主进程正常退出");
    log();
    return 0;
}

// type 为 0 表示除, 为 1 表示 乘, 2 表示小于, 3 表示使用 isless, 其他使用 lrint
void test(const std::string& name, double x, double y, int type = 0) {
    std::feclearexcept(FE_ALL_EXCEPT);
    std::string result;
    if (type == 0)
        x = x / y;
    else if (type == 1)
        x = x * y;
    else if (type == 2)
        result = x < y ? "true" : "false";
    else if (type == 3)
        result = std::isless(x, y) ? "true" : "false";
    else
        result = std::lrint(x) ? "true" : "false";

    std::string except;
    for (auto v : dict_except)
        if (std::fetestexcept(v.first)) {
            except += v.second + " ";
        }

    if (except.empty()) {
        except = "空";
    }

    log();
    log("测试类型: " + name);
    log("测试结果: " + result);
    log("异常信息: " + except);
}

int main() {
    log();
    log("测试浮点数的异常");
    log();

    double x;
    test("测试除以零", 1, 0.0);
    test("测试结果不准确", 1, 10.0);
    x = std::numeric_limits<double>::max();
    test("测试上溢", x, 2, 1);
    x = std::numeric_limits<double>::denorm_min();
    test("测试下溢", x, 2);

    test("测试 NAN < NAN", NAN, NAN, 2);
    test("测试 isless(NAN, NAN)", NAN, NAN, 3);
    test("测试 lrint(NAN)", NAN, NAN, 4);

    x = std::numeric_limits<double>::quiet_NaN();
    test("测试 quiet_NAN < quiet_NAN", x, x, 2);
    test("测试 isless(quiet_NAN, quiet_NAN)", x, x, 3);
    test("测试 lrint(quiet_NAN)", x, x, 4);

    x = std::numeric_limits<double>::signaling_NaN();
    test("测试 signaling_NaN < signaling_NaN", x, x, 2);
    test("测试 isless(signaling_NaN, signaling_NaN)", x, x, 3);
    test("测试 lrint(signaling_NaN)", x, x, 4);

    log();
    log("主进程正常退出");
    log();
    return 0;
}

int main() {
    log();
    log("测试浮点数能表示的最大的小数点后的位数");
    log();

    double x = std::numeric_limits<double>::denorm_min();

    Double d(x);

    std::string str = d.double_by_cs;

    log("最小非规约正数: " + str);
    log("小数点后共有: " + std::to_string(str.size() - 2) + " 位");

    log();
    log("主进程正常退出");
    log();
    return 0;
}

int main() {
    log();
    log("测试不同类型的浮点数以及浮点数的差值");
    log();

    test_double(
        "正零",
        "0 00000000000 0000000000000000000000000000000000000000000000000000");
    test_double(
        "最小非规约正数",
        "0 00000000000 0000000000000000000000000000000000000000000000000001");
    test_double(
        "最大非规约正数",
        "0 00000000000 1111111111111111111111111111111111111111111111111111");
    test_double(
        "最小  规约正数",
        "0 00000000001 0000000000000000000000000000000000000000000000000000");
    test_double(
        "最大  规约正数",
        "0 11111111110 1111111111111111111111111111111111111111111111111111");
    test_double(
        "正无穷",
        "0 11111111111 0000000000000000000000000000000000000000000000000000");
    test_double(
        "非数字",
        "0 11111111111 0000000000000000000000000000000000000000000000000001");

    log();
    log("使用 numeric_limits");
    log("最小非规约负数: " + Double(std::numeric_limits<double>::lowest()).bit);
    log("最小非规约正数: " +
        Double(std::numeric_limits<double>::denorm_min()).bit);
    log("最小  规约正数: " + Double(std::numeric_limits<double>::min()).bit);
    log("最大  规约正数: " + Double(std::numeric_limits<double>::max()).bit);
    log("        正无穷: " +
        Double(std::numeric_limits<double>::infinity()).bit);

    log();
    log("测试浮点数的差值");
    log();
    double a, b, c, d;

    // 最小规约正数
    c = std::numeric_limits<double>::min();
    // 最小规约正数的下一数
    d = std::nextafter(c, std::numeric_limits<double>::infinity());
    // 最大非规约正数
    b = std::nextafter(c, std::numeric_limits<double>::lowest());
    // 最大非规约正数的上一数
    a = std::nextafter(b, std::numeric_limits<double>::lowest());

    log(format("最大非规约正数       - 最大非规约正数的上一数: %.2000lf",
               b - a));
    log(format("最小规约正数         - 最大非规约正数:       : %.2000lf",
               c - b));
    log(format("最小规约正数的下一数 - 最小规约正数:         : %.2000lf",
               d - c));

    log();
    log("主进程正常退出");
    log();
    return 0;
}

int main() {
    log();
    log("测试浮点数的上下限");
    log();

    double x;

    x = std::nextafter(0.1, std::numeric_limits<double>::lowest());
    test_double("0.1 的前一个数", x);

    x = 0.1;
    test_double("0.1", x);

    x = std::nextafter(0.1, std::numeric_limits<double>::max());
    test_double("0.1 的后一个数", x);

    test_double(
        "0.1",
        "0 01111111011 1001100110011001100110011001100110011001100110011010");

    test_double(
        "0.1 的下限(进, 含)",
        "0 01111111011 1001100110011001100110011001100110011001100110011001 1");

    test_double(
        "0.1 的上限(舍, 含)",
        "0 01111111011 1001100110011001100110011001100110011001100110011010 1");

    test_double(
        "测试 4503599627370496",
        "0 10000110011 0000000000000000000000000000000000000000000000000000");

    test_double(
        "测试 4503599627370496 的下限(进, 含)",
        "0 10000110010 1111111111111111111111111111111111111111111111111111 1");

    test_double(
        "测试 4503599627370496 的上限(舍, 含)",
        "0 10000110011 0000000000000000000000000000000000000000000000000000 1");

    test_double(
        "测试 4503599627370497",
        "0 10000110011 0000000000000000000000000000000000000000000000000001");

    test_double(
        "测试 4503599627370497 的下限(舍, 不含)",
        "0 10000110011 0000000000000000000000000000000000000000000000000000 1");

    test_double(
        "测试 4503599627370497 的上限(进, 不含)",
        "0 10000110011 0000000000000000000000000000000000000000000000000001 1");

    log();
    log("主进程正常退出");
    log();
    return 0;
}

void test(const std::string& str, double x) {
    log(str + " => " + Double(x).double_by_cs);
}

int main() {
    log();
    log("测试浮点数不精确");
    log();

    test("4503599627370496.0", 4503599627370496.0);
    test("4503599627370496.1", 4503599627370496.1);
    test("4503599627370496.2", 4503599627370496.2);
    test("4503599627370496.3", 4503599627370496.3);
    test("4503599627370496.4", 4503599627370496.4);
    test("4503599627370496.5", 4503599627370496.5);
    test("4503599627370496.6", 4503599627370496.6);
    test("4503599627370496.7", 4503599627370496.7);
    test("4503599627370496.8", 4503599627370496.8);
    test("4503599627370496.9", 4503599627370496.9);
    test("4503599627370490  ", 4503599627370490);
    test("4503599627370491  ", 4503599627370491);
    test("4503599627370492  ", 4503599627370492);
    test("4503599627370493  ", 4503599627370493);
    test("4503599627370494  ", 4503599627370494);
    test("4503599627370495  ", 4503599627370495);
    test("4503599627370496  ", 4503599627370496);
    test("4503599627370497  ", 4503599627370497);
    test("4503599627370498  ", 4503599627370498);
    test("4503599627370499  ", 4503599627370499);

    log();
    log("主进程正常退出");
    log();
    return 0;
}

void test(const std::string& name, char* p, size_t n) {
    log(name);
    for (size_t i = 0; i < n; ++i) {
        log("第" + std::to_string(i + 1) + "个字节: " + format("%x", p[i]));
    }
}

int main() {
    log();
    log("测试 UTF-8");
    log();

    char     utf8_1[] = "中";
    char     utf8_2[] = "\u4e2d";
    char16_t utf16[]  = u"中";
    char32_t utf32[]  = U"中";

    log("utf-8      中: " + std::string(utf8_1));
    log("utf-8  \\u4e2d: " + std::string(utf8_2));
    log("utf8   sizeof: " + std::to_string(sizeof(utf8_1)));
    log("utf16  sizeof: " + std::to_string(sizeof(utf16)));
    log("utf32  sizeof: " + std::to_string(sizeof(utf32)));

    test("UTF-8  在内存中的存储: ", utf8_1, sizeof(utf8_1));
    test("UTF-16 在内存中的存储: ", (char*)utf16, sizeof(utf16));
    test("UTF-32 在内存中的存储: ", (char*)utf32, sizeof(utf32));

    log();
    log("主进程正常退出");
    log();
    return 0;
}

template <typename T>
std::string format(const char* fmt, T data) {
    char buf[2048];
    snprintf(buf, sizeof(buf), fmt, data);
    return buf;
}

double to_double(const std::string& str) {
    double data;
    sscanf(str.data(), "%lf", &data);
    return data;
}

// 存储浮点数异常
std::map<int, std::string> dict_except{
    {FE_DIVBYZERO, "除以0"        },
    {FE_INEXACT,   "结果不准确"},
    {FE_INVALID,   "参数非法"   },
    {FE_OVERFLOW,  "上溢"         },
    {FE_UNDERFLOW, "下溢"         }
};

//存储舍入模式
std::map<int, std::string> dict_round{
    {FE_DOWNWARD,   "向下舍入"},
    {FE_TONEAREST,  "最近舍入"},
    {FE_TOWARDZERO, "向零舍入"},
    {FE_UPWARD,     "向上舍入"}
};

// 测试 浮点数
class Double {
  public:
    union Node {
        double   x;
        uint64_t y;
    };

    double      data;
    std::string bit;
    std::string bit_by_test;
    std::string bit_by_cs;
    std::string bit_by_show;
    std::string double_by_hand;
    std::string double_by_cs;

    Double(double x) {
        init();

        Node node;
        node.x         = x;
        bit            = std::bitset<64>(node.y).to_string();
        bit_by_test    = bit;
        bit_by_cs      = bit;
        bit_by_show    = to_bit();
        double_by_hand = to_double_hand();
        double_by_cs   = to_double_cs();
        data           = x;
    }

    Double(const std::string& str) {
        init();

        bit = trim(str);
        if ((int)bit.size() < 64) {
            // 往后补0
            bit += std::string(64 - (int)bit.size(), '0');
        }

        bit_by_test    = bit;
        bit_by_show    = to_bit();
        double_by_hand = to_double_hand();

        Node node;
        node.x = to_double(double_by_hand);

        bit          = std::bitset<64>(node.y).to_string();
        bit_by_cs    = bit;
        double_by_cs = to_double_cs();
        data         = node.x;
    }

  private:
    // 存储 2 的幂次, 负幂次只存储小数点后的部分
    std::map<int, std::string> dict_pow;

    void init() {
        // 2 的幂次
        int         n = 2000;
        std::string str;

        str = "5";
        for (int i = -1; i >= -n; --i) {
            dict_pow[i] = str;

            str     = "";
            int sum = 0;
            for (char ch : dict_pow[i]) {
                sum = sum * 10 + (ch - '0');
                str += std::string(1, sum / 2 + '0');
                sum %= 2;
            }
            if (sum != 0)
                str += "5";
        }

        str = "1";
        for (int i = 0; i <= n; ++i) {
            dict_pow[i] = str;

            str     = "";
            int sum = 0;
            for (int j = (int)dict_pow[i].size() - 1; j >= 0; --j) {
                sum += (dict_pow[i][j] - '0') * 2;
                str = std::string(1, sum % 10 + '0') + str;
                sum /= 10;
            }
            if (sum != 0)
                str = std::string(1, sum + '0') + str;
        }
    }

    // 移除所有的 空字符
    std::string trim(const std::string& str) {
        std::string result;
        for (char ch : str) {
            if (!std::isspace(ch)) {
                result += ch;
            }
        }
        return result;
    }

    // 浮点数 符号位 阶码 尾码
    std::string to_bit() {
        std::string s_str = bit.substr(0, 1);
        std::string e_str = bit.substr(1, 11);
        std::string f_str = bit.substr(12, 52);

        std::bitset<11> e_bit(e_str);
        std::bitset<52> f_bit(f_str);

        int e_int = e_bit.to_ulong();

        if (e_bit.none() && not f_bit.none()) {
            // 非规约数字: 阶码都为 0, 尾码不都为 0
            e_int -= 1022;
        } else if (not e_bit.all() && not e_bit.none()) {
            // 规约数字: 阶码不都为 0, 也不都为 1
            e_int -= 1023;
        } else {
            // 还剩 0 无穷 非数字
        }

        std::string e_int_string = std::to_string(e_int);
        e_int_string =
            std::string(5 - (int)e_int_string.size(), ' ') + e_int_string;

        std::string result =
            s_str + " " + e_str + "(" + e_int_string + ") " + f_str;
        result += " " + bit.substr(64);  // 多余 64 位的部分
        return result;
    }

    // 计算机内部存储的浮点数(字符串)
    std::string to_double_cs() {
        Node node;
        node.y             = std::bitset<64>(bit.substr(0, 64)).to_ulong();
        std::string result = format("%.2000f", node.x);  // 最多 1074 位
        size_t      index  = result.find_last_not_of('0');

        if (result[index] == '.') {
            --index;
        }
        return result.substr(0, index + 1);
    }

    // 两个数的加法(十进制)
    // type 为 0 表示整数加法 1 表示小数加法
    std::string add(std::string x, std::string y, int type = 0) {
        if (x.size() > y.size()) {
            swap(x, y);
        }
        if (type == 0)
            x = std::string(y.size() - x.size(), '0') + x;  // 整数
        else
            x = x + std::string(y.size() - x.size(), '0');  // 小数

        int         sum = 0;
        std::string z;

        for (int i = (int)x.size() - 1; i >= 0; --i) {
            sum += (x[i] - '0') + (y[i] - '0');
            z = std::string(1, '0' + sum % 10) + z;
            sum /= 10;
        }
        if (sum != 0) {
            z = std::string(1, '0' + sum) + z;
        }
        return z;
    }

    // 二进制的浮点数转化为 十进制,
    // str_int --> 整数部分, str_dec --> 小数部分
    std::string to_double_hand(const std::string& str_int,
                               const std::string& str_dec) {
        std::string result_int = "0";
        for (int i = 0; i < (int)str_int.size(); ++i)
            if (str_int[i] == '1')
                result_int = add(result_int, dict_pow[str_int.size() - 1 - i]);

        std::string result_dec;
        for (int i = 0; i < (int)str_dec.size(); ++i)
            if (str_dec[i] == '1')
                result_dec = add(result_dec, dict_pow[-1 - i], 1);

        if (result_dec.empty())
            return result_int;
        else
            return result_int + "." + result_dec;
    }

    // 手动计算浮点数(字符串)
    std::string to_double_hand() {
        std::string s_str = bit.substr(0, 1);
        std::string e_str = bit.substr(1, 11);
        std::string f_str = bit.substr(12);

        std::bitset<11> e_bit(e_str);
        int             e_int = e_bit.to_ulong();

        std::bitset<52> f_bit(f_str);  // 只用于判断 0 无穷 非数字

        // 阶码都为 1, 尾码都为 0
        if (e_bit.all() && f_bit.none()) {
            return s_str == "1" ? "负无穷" : "正无穷";
        }

        // 阶码都为 1, 尾码不都为 0
        if (e_bit.all() && not f_bit.none()) {
            return "非数字";
        }

        // 阶码都为 0, 尾码都为 0
        if (e_bit.none() && f_bit.none()) {
            return s_str == "1" ? "负零" : "正零";
        }

        std::string str_int;          // 尾码的整数部分
        std::string str_dec = f_str;  // 尾码的小数部分

        if (e_bit.none() && not f_bit.none()) {
            // 阶码都为 0, 尾码不都为 0
            // 非规约数字
            f_str = "0." + f_str;
            e_int -= 1022;
        } else {
            // 阶码不都为 0, 也不都为 1
            // 规约数字
            f_str = "1." + f_str;
            e_int -= 1023;
            str_int = "1";
        }

        // 处理 阶码 的移位
        if (e_int > 0) {
            if ((int)str_dec.size() < e_int)
                str_dec += std::string(e_int - str_dec.size(), 0);

            str_int += str_dec.substr(0, e_int);
            str_dec = str_dec.substr(e_int);
        } else if (e_int < 0) {
            if (!str_int.empty())
                str_dec = std::string(-e_int - 1, '0') + str_int + str_dec;
            else
                str_dec = std::string(-e_int, '0') + str_dec;
            str_int = "";
        }
        std::string result = to_double_hand(str_int, str_dec);
        if (s_str == "1") {
            result = "-" + result;
        }
        return result;
    }
};

template <typename T>
void test_double(const std::string& name, T data) {
    Double d(data);

    log();
    log("        测试类型: " + name);
    log("    测试的二进制: " + d.bit_by_test);
    log("    存储的二进制: " + d.bit_by_cs);
    log("          手动值: " + d.double_by_hand);
    log("          存储值: " + d.double_by_cs);
    log("    保留两位小数: " + format("%.2lf", d.data));
}

template <typename T>
std::string format(const char* fmt, T data) {
    char buf[2048];
    snprintf(buf, sizeof(buf), fmt, data);
    return buf;
}

double to_double(const std::string& str) {
    double data;
    sscanf(str.data(), "%lf", &data);
    return data;
}

// 存储浮点数异常
std::map<int, std::string> dict_except{
    {FE_DIVBYZERO, "除以0"        },
    {FE_INEXACT,   "结果不准确"},
    {FE_INVALID,   "参数非法"   },
    {FE_OVERFLOW,  "上溢"         },
    {FE_UNDERFLOW, "下溢"         }
};

//存储舍入模式
std::map<int, std::string> dict_round{
    {FE_DOWNWARD,   "向下舍入"},
    {FE_TONEAREST,  "最近舍入"},
    {FE_TOWARDZERO, "向零舍入"},
    {FE_UPWARD,     "向上舍入"}
};

// 测试 浮点数
class Double {
  public:
    union Node {
        double   x;
        uint64_t y;
    };

    double      data;
    std::string bit;
    std::string bit_by_test;
    std::string bit_by_cs;
    std::string bit_by_show;
    std::string double_by_hand;
    std::string double_by_cs;

    Double(double x) {
        init();

        Node node;
        node.x         = x;
        bit            = std::bitset<64>(node.y).to_string();
        bit_by_test    = bit;
        bit_by_cs      = bit;
        bit_by_show    = to_bit();
        double_by_hand = to_double_hand();
        double_by_cs   = to_double_cs();
        data           = x;
    }

    Double(const std::string& str) {
        init();

        bit = trim(str);
        if ((int)bit.size() < 64) {
            // 往后补0
            bit += std::string(64 - (int)bit.size(), '0');
        }

        bit_by_test    = bit;
        bit_by_show    = to_bit();
        double_by_hand = to_double_hand();

        Node node;
        node.x = to_double(double_by_hand);

        bit          = std::bitset<64>(node.y).to_string();
        bit_by_cs    = bit;
        double_by_cs = to_double_cs();
        data         = node.x;
    }

  private:
    // 存储 2 的幂次, 负幂次只存储小数点后的部分
    std::map<int, std::string> dict_pow;

    void init() {
        // 2 的幂次
        int         n = 2000;
        std::string str;

        str = "5";
        for (int i = -1; i >= -n; --i) {
            dict_pow[i] = str;

            str     = "";
            int sum = 0;
            for (char ch : dict_pow[i]) {
                sum = sum * 10 + (ch - '0');
                str += std::string(1, sum / 2 + '0');
                sum %= 2;
            }
            if (sum != 0)
                str += "5";
        }

        str = "1";
        for (int i = 0; i <= n; ++i) {
            dict_pow[i] = str;

            str     = "";
            int sum = 0;
            for (int j = (int)dict_pow[i].size() - 1; j >= 0; --j) {
                sum += (dict_pow[i][j] - '0') * 2;
                str = std::string(1, sum % 10 + '0') + str;
                sum /= 10;
            }
            if (sum != 0)
                str = std::string(1, sum + '0') + str;
        }
    }

    // 移除所有的 空字符
    std::string trim(const std::string& str) {
        std::string result;
        for (char ch : str) {
            if (!std::isspace(ch)) {
                result += ch;
            }
        }
        return result;
    }

    // 浮点数 符号位 阶码 尾码
    std::string to_bit() {
        std::string s_str = bit.substr(0, 1);
        std::string e_str = bit.substr(1, 11);
        std::string f_str = bit.substr(12, 52);

        std::bitset<11> e_bit(e_str);
        std::bitset<52> f_bit(f_str);

        int e_int = e_bit.to_ulong();

        if (e_bit.none() && not f_bit.none()) {
            // 非规约数字: 阶码都为 0, 尾码不都为 0
            e_int -= 1022;
        } else if (not e_bit.all() && not e_bit.none()) {
            // 规约数字: 阶码不都为 0, 也不都为 1
            e_int -= 1023;
        } else {
            // 还剩 0 无穷 非数字
        }

        std::string e_int_string = to_string(e_int);
        e_int_string =
            std::string(5 - (int)e_int_string.size(), ' ') + e_int_string;

        std::string result;
        return to_string(s_str,
                         " ",
                         e_str,
                         "(",
                         e_int_string,
                         ") ",
                         f_str,
                         " ",
                         bit.substr(64));  // 多余 64 位的部分
    }

    // 计算机内部存储的浮点数(字符串)
    std::string to_double_cs() {
        Node node;
        node.y             = std::bitset<64>(bit.substr(0, 64)).to_ulong();
        std::string result = format("%.2000f", node.x);  // 最多 1074 位
        size_t      index  = result.find_last_not_of('0');

        if (result[index] == '.') {
            --index;
        }
        return result.substr(0, index + 1);
    }

    // 两个数的加法(十进制)
    // type 为 0 表示整数加法 1 表示小数加法
    std::string add(std::string x, std::string y, int type = 0) {
        if (x.size() > y.size()) {
            swap(x, y);
        }
        if (type == 0)
            x = std::string(y.size() - x.size(), '0') + x;  // 整数
        else
            x = x + std::string(y.size() - x.size(), '0');  // 小数

        int         sum = 0;
        std::string z;

        for (int i = (int)x.size() - 1; i >= 0; --i) {
            sum += (x[i] - '0') + (y[i] - '0');
            z = std::string(1, '0' + sum % 10) + z;
            sum /= 10;
        }
        if (sum != 0) {
            z = std::string(1, '0' + sum) + z;
        }
        return z;
    }

    // 二进制的浮点数转化为 十进制,
    // str_int --> 整数部分, str_dec --> 小数部分
    std::string to_double_hand(const std::string& str_int,
                               const std::string& str_dec) {
        std::string result_int = "0";
        for (int i = 0; i < (int)str_int.size(); ++i)
            if (str_int[i] == '1')
                result_int = add(result_int, dict_pow[str_int.size() - 1 - i]);

        std::string result_dec;
        for (int i = 0; i < (int)str_dec.size(); ++i)
            if (str_dec[i] == '1')
                result_dec = add(result_dec, dict_pow[-1 - i], 1);

        if (result_dec.empty())
            return result_int;
        else
            return result_int + "." + result_dec;
    }

    // 手动计算浮点数(字符串)
    std::string to_double_hand() {
        std::string s_str = bit.substr(0, 1);
        std::string e_str = bit.substr(1, 11);
        std::string f_str = bit.substr(12);

        std::bitset<11> e_bit(e_str);
        int             e_int = e_bit.to_ulong();

        std::bitset<52> f_bit(f_str);  // 只用于判断 0 无穷 非数字

        // 阶码都为 1, 尾码都为 0
        if (e_bit.all() && f_bit.none()) {
            return s_str == "1" ? "负无穷" : "正无穷";
        }

        // 阶码都为 1, 尾码不都为 0
        if (e_bit.all() && not f_bit.none()) {
            return "非数字";
        }

        // 阶码都为 0, 尾码都为 0
        if (e_bit.none() && f_bit.none()) {
            return s_str == "1" ? "负零" : "正零";
        }

        std::string str_int;          // 尾码的整数部分
        std::string str_dec = f_str;  // 尾码的小数部分

        if (e_bit.none() && not f_bit.none()) {
            // 阶码都为 0, 尾码不都为 0
            // 非规约数字
            f_str = "0." + f_str;
            e_int -= 1022;
        } else {
            // 阶码不都为 0, 也不都为 1
            // 规约数字
            f_str = "1." + f_str;
            e_int -= 1023;
            str_int = "1";
        }

        // 处理 阶码 的移位
        if (e_int > 0) {
            if ((int)str_dec.size() < e_int)
                str_dec += std::string(e_int - str_dec.size(), 0);

            str_int += str_dec.substr(0, e_int);
            str_dec = str_dec.substr(e_int);
        } else if (e_int < 0) {
            if (!str_int.empty())
                str_dec = std::string(-e_int - 1, '0') + str_int + str_dec;
            else
                str_dec = std::string(-e_int, '0') + str_dec;
            str_int = "";
        }
        std::string result = to_double_hand(str_int, str_dec);
        if (s_str == "1") {
            result = "-" + result;
        }
        return result;
    }
};

template <typename T>
void test_double(const std::string& name, T data) {
    Double d(data);

    log();
    log("        测试类型: ", name);
    log("    测试的二进制: ", d.bit_by_test);
    log("    存储的二进制: ", d.bit_by_cs);
    log("          手动值: ", d.double_by_hand);
    log("          存储值: ", d.double_by_cs);
    log("    保留两位小数: ", format("%.2lf", d.data));
}

int main() {
    log();
    log("测试 C++ 格式化输入和输出");
    log();

    // scanf     # 除了 %c 外, 将忽略所有的空白字符
    // getchar() # 读取一个字符, 包含空白字符
    // fgets()   # 读取一行, 包含换行符

#if 0
    char ch;
    log("请输入字符(包括空白字符)");
    scanf("%c", &ch);
    log("111%c111", ch);
#endif

#if 0
    char ch;
    log("请输入字符(空白字符将被忽略)");
    scanf(" %c", &ch);
    log("111%c111", ch);
#endif

#if 0
    char buf[64];
    log("请输入字符串(最多输入5位)");
    scanf("%5s", buf);
    log("1111%s111", buf);
#endif

#if 0
    int v;
    log("请输入整数(最多输入5位)");
    scanf("%5d", &v);
    log("aaa%daaa", v);
#endif

    const char* s = "123";

    log("字符串(原始            ): %s", s);
    log("字符串(最小宽度, 右对齐): %10s", s);
    log("字符串(最小宽度, 左对齐): %-10s", s);
    printf("字符串(最小宽度, 参数指定): %*s\n", 10, s);

    int i = 123;

    log("整数(原始              ): %d", i);
    log("整数(最小宽度,   右对齐): %10d", i);
    log("整数(最小宽度,   左对齐): %-10d", i);
    printf("整数  (最小宽度, 参数指定): %*d\n", 10, i);
    log("整数(最小宽度, 前缀为零): %010d", i);
    log("整数(正数添加前缀加号  ): %+10d", i);
    log("整数(  十进制    无符号): %u", i);
    log("整数(  八进制    无符号): %o", i);
    log("整数(十六进制    无符号): %x", i);
    // %lu %ld 同理
    log("指针                    : %p", &i);

    double d = 3.1459265354;
    log("浮点数(非科学计数)      : %f", d);
    log("浮点数(  科学计数)      : %e", d);
    log("浮点数(指明小数点位数)  : %.2f", d);  // 四舍六入五取偶
    log("浮点数(指明最小宽度)    : %10.2f", d);

    log();
    log("主进程正常退出");
    log();
    return 0;
}

#endif

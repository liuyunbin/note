
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <map>

void log(const std::string& msg) {
    std::cout << "进程(" << getpid() <<  "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    log("信号处理函数-捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
    log("已退出的子进程是: " + std::to_string(waitpid(-1, NULL, 0)));
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGCHLD, &act, NULL);
}

int main() {
    std::string cmd = "ps -o pid,ppid,state,comm -C a.out,ps";

    log("测试僵尸进程");
    log("测试子进程已退出, 父进程未正确处理的情况");
    log("设置信号 SIGCHLD 处理函数");
    set_signal();
    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    for (int i = 0; i < 3; ++i)
        if (fork() == 0) {
            // 子进程
            log("子进程启动");
            sleep(2);
            log("子进程退出");
            return 0;
        }
    // 父进程
    sleep(1);
    log("子进程状态");
    system(cmd.data());
    sleep(2);
    log("解除信号 SIGCHLD 阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());
    log("父进程退出");

    return 0;
}


#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <map>

void log(const std::string& msg) {
    std::cout << "进程(" << getpid() <<  "): " << msg << std::endl;
}

void handle_signal(int sig, siginfo_t* sig_info, void * ) {
    log("捕获信号 SIGCHLD 来自 " + std::to_string(sig_info->si_pid));
}

void set_signal() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGCHLD, &act, NULL);
}

int main() {
    //set_signal();

    log("测试僵尸进程");
    log("");
    log("测试父进程未处理 SIGCHLD 的情况");
    pid_t fd = fork();

    if (fd == 0) {
        // 子进程
        log("子进程启动");
        log("子进程退出");
        return 0;
    } else {
        // 父进程
        sleep(1);
        log("子进程状态");
        std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(fd);
        system(cmd.data());
    }

    return 0;
}


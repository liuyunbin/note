
#ifndef LOG_H_
#define LOG_H_

#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
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

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << msg << std::endl;
}

#endif
#include "00.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGCHLD");
}

int main() {
    init();

    log();
    log("测试子进程暂停, 继续, 退出时, 向父进程发送 SIGCHLD, 父进程的处理");
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
        return 0;
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

    log("主进程退出");
    log();
    return 0;
}


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

int count = 0;

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGUSR1 第 " + std::to_string(++count) + " 次");
}

int main() {
    log();
    log("测试多个信号处于待决状态信号会丢失");
    log();

    log("注册信号处理函数");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
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

    log("主进程退出");
    log();

    return 0;
}

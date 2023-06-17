
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
    log("捕获信号 " + m[sig]);
}

int main() {
    init();

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

    log("主进程退出");
    log();

    return 0;
}

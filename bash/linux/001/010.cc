
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
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 SIGABRT");
}

int main() {
    log();
    log("测试 SIGABRT 处理为 捕获信号并返回");
    log();

    log("设置 SIGABRT 处理为 捕获信号并返回");
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGABRT, &act, NULL);

    log("调用 abort()");
    abort();

    log("主进程正常退出");
    log();

    return 0;
}


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

int main() {
    init();

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

    log("主进程退出");
    log();

    return 0;
}

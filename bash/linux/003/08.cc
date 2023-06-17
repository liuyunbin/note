
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
    log();
    log("测试修改进程组(原进程组和目标进程组属于不同会话)");
    log();

    pid_t child = fork();

    if (child == 0) {
        log("子进程创建新会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("子进程的状态信息");
    test(getpid(), child);
    sleep(1);
    log("主进程退出");
    log();

    return 0;
}

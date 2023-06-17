
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

int main() {
    log();
    log("测试僵尸进程");
    log("测试父进程未处理子进程退出的状态信息");
    log();

    pid_t child = fork();

    if (child == 0) {
        log("子进程(" + std::to_string(getpid()) + ")已启动");
        for (;;)
            ;
    }
    sleep(1);  // 保证子进程已启动
    std::string cmd = "ps -o pid,comm,state -p " + std::to_string(child);
    log("子进程状态");
    system(cmd.data());
    log("杀死子进程(" + std::to_string(child) + ")");
    kill(child, SIGKILL);
    sleep(1);
    log("子进程状态");
    system(cmd.data());

    log("主进程退出");
    log();

    return 0;
}


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
    log("测试预防僵尸进程");
    log("测试杀死父进程");
    log();

    if (fork() == 0) {
        pid_t child = fork();
        if (child == 0) {
            log("测试的子进程(" + std::to_string(getpid()) + ")启动");
            for (;;)
                ;
        } else if (fork() == 0) {
            log("测试的控制进程(" + std::to_string(getpid()) + ")启动");
            sleep(1);
            std::string cmd = "ps -o pid,ppid,comm,state -p ";
            cmd += std::to_string(child);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的父进程(" + std::to_string(getppid()) + ")");
            kill(getppid(), SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的子进程(" + std::to_string(child) + ")");
            kill(child, SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            return 0;
        } else {
            log("测试的父进程(" + std::to_string(getpid()) + ")启动");
            for (;;)
                ;
        }
    }

    sleep(4);

    log("主进程退出");
    log();

    return 0;
}

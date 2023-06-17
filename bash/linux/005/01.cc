
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
    log("测试孤儿进程");
    log();

    if (fork() == 0) {
        if (fork() == 0) {
            // 测试的子进程
            sleep(1);
            log("测试的子进程(" + std::to_string(getpid()) + ")启动");
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            std::string commond = cmd;
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            log("进程状态");
            system(commond.data());
            log("杀死父进程 " + std::to_string(getppid()));
            kill(getppid(), SIGKILL);
            sleep(1);
            log("进程状态");
            commond = cmd;
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            return 0;
        } else {
            // 测试的父进程
            log("测试的父进程(" + std::to_string(getpid()) + ")启动");
            for (;;)
                ;
        }
    }

    sleep(3);

    log("主进程退出");
    log();

    return 0;
}

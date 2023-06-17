
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
    log("测试不可被信号打断的休眠(指被捕获的信号) 对 SIGSTOP 的处理");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        if (vfork() == 0) {
            log("测试的子进程启动");
            log("测试的子进程休眠10秒");
            sleep(10);
            log("测试的子进程休眠完成");
            log("测试的子进程退出");
            exit(-1);
        }
        log("测试的父进程休眠1s");
        sleep(1);
        log("测试的父进程退出");
        exit(-1);
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGSTOP");
        kill(fd, SIGSTOP);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());

        log("向测试的父进程发送信号 SIGCONT");
        kill(fd, SIGCONT);
        sleep(1);
        log("测试的父进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log("主进程正常退出");
    log();

    return 0;
}


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

void handle_signal(int sig) { log("子进程捕捉到信号 SIGUSR1"); }

int main() {
    log();
    log("测试 暂停 => 继续");
    log();

    pid_t fd = fork();
    if (fd == 0) {
        log("子进程注册信号处理函数");
        signal(SIGUSR1, handle_signal);
        for (;;)
            ;
    } else {
        sleep(1);
        std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);

        log("使子进程暂停");
        kill(fd, SIGSTOP);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGUSR1");
        kill(fd, SIGUSR1);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGCONT");
        kill(fd, SIGCONT);
        sleep(1);
        log("子进程状态");
        system(cmd.data());

        log("向子进程发送信号 SIGKILL");
        kill(fd, SIGKILL);
        sleep(1);
        log("子进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log("主进程正常退出");
    log();

    return 0;
}

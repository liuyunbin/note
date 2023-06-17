
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
    log("测试销毁会话(会话不和终端绑定)");
    log();

    if (fork() == 0) {
        log("建立新会话");
        test();
        if (fork() == 0) {
            log("新会话的子进程");
            log("当前进程和父进程的信息");
            show(getpid());
            show(getppid());
            log("杀死父进程(会话首进程): " + std::to_string(getppid()));
            if (kill(getppid(), SIGKILL) < 0) {
                perror("");
            }
            sleep(1);
            log("当前进程和父进程的信息");
            show(getpid());
            show(getppid());
            exit(-1);
        } else {
            for (;;)
                ;
        }
    }

    sleep(3);
    log("主进程退出");
    log();

    return 0;
}

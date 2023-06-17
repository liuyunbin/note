
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
    log("测试新建孙进程对应的进程组");
    log();

    int pipefd[2];
    pipe(pipefd);
    pid_t child = fork();
    if (child == 0) {
        pid_t grandchild = fork();

        if (grandchild == 0) {
            // 测试的孙进程
            close(pipefd[0]);
            close(pipefd[1]);
            for (;;)
                ;
        } else {
            // 测试的子进程
            close(pipefd[0]);
            std::string str = std::to_string(grandchild);
            write(pipefd[1], str.data(), str.size());
            close(pipefd[1]);
            for (;;)
                ;
        }
    } else {
        // 测试的父进程
        close(pipefd[1]);

        char ch;
        std::string str;

        while (read(pipefd[0], &ch, 1) > 0) {
            str.push_back(ch);
        }
        pid_t grandchild = atoi(str.data());

        log("进程关系");
        std::string cmd = "ps -o pid,ppid,pgid,sid,comm -p";
        cmd += std::to_string(child) + ",";
        cmd += std::to_string(grandchild) + ",";
        cmd += std::to_string(getpid());
        system(cmd.data());
        log("修改孙进程(" + str + ")的进程组");
        test(grandchild, grandchild);

        kill(child, SIGKILL);
        kill(grandchild, SIGKILL);
    }

    log("主进程退出");
    log();

    return 0;
}

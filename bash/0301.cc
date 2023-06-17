
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

std::map<int, std::string> m;

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

int main() {
    m[SIGHUP] = " 1-SIGHUP ";
    m[SIGCONT] = "18-SIGCONT";

    log();
    log("测试孤儿进程组");
    log();
    log("设置信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGCONT, &act, NULL);

    pid_t main_pid = getpid();
    if (fork() == 0) {
        // 测试的父进程
        log("测试的父进程(" + std::to_string(getpid()) + ")启动");
        log("设置新的进程组(" + std::to_string(getpid()) + ")");
        setpgid(getpid(), getpid());
        pid_t child_1 = fork();
        if (child_1 == 0) {
            // 测试的第一个子进程
            log("测试的第一个子进程(" + std::to_string(getpid()) + ")启动");
            log("测试的第一个子进程使自己暂停");
            kill(getpid(), SIGSTOP);
            for (;;)
                ;
        } else if (fork() == 0) {
            // 测试的第二个子进程
            sleep(1);
            log("测试的第二个子进程(" + std::to_string(getpid()) + ")启动");
            log("进程状态");
            std::string cmd = "ps -o pid,ppid,pgid,sid,state,comm -p ";
            std::string commond = cmd;
            commond += std::to_string(main_pid) + ",";
            commond += std::to_string(child_1) + ",";
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            log("杀死测试的父进程(" + std::to_string(getppid()) + ")");
            kill(getppid(), SIGKILL);
            sleep(1);
            sleep(1);
            log("进程状态");
            commond = cmd;
            commond += std::to_string(child_1) + ",";
            commond += std::to_string(getpid()) + ",";
            commond += std::to_string(getppid());
            system(commond.data());
            log("杀死测试的第一个子进程(" + std::to_string(child_1) + ")");
            kill(child_1, SIGKILL);
            log("测试的第二个子进程退出");
            return 0;
        } else {
            // 父进程
            for (;;)
                ;
        }
    }

    sleep(3);
    log("主进程退出");
    log();

    return 0;
}

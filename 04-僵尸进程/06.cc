
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>

void log(const std::string& msg = "") {
    time_t     now  = time(NULL);
    struct tm* info = localtime(&now);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    std::cout << buf << " " << msg << std::endl;
}

int main() {
    log();
    log("计算机操作系统-僵尸进程-预防: 杀死父进程");
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
            std::string cmd =
                "ps -o pid,ppid,comm,state -p " + std::to_string(child);
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

    log();
    log("主进程正常退出");
    log();
    return 0;
}

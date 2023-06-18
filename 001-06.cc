
#include "log.h"

int main() {
    log();
    log("操作系统-僵尸进程-预防");
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


#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "log.h"

int main() {
    log();
    log("计算机操作系统-僵尸进程");
    log("销毁僵尸进程: 杀死僵尸进程的父进程");
    log();

    if (fork() == 0) {
        pid_t fd = fork();

        if (fd == 0) {
            log("测试的子进程启动: ", getpid());
            for (;;)
                ;
        } else if (fork() == 0) {
            log("测试的控制进程启动: ", getpid());
            sleep(1);
            std::string cmd = "ps -o pid,ppid,state -p " + std::to_string(fd);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的子进程: ", fd);
            kill(fd, SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            log("杀死测试的父进程: ", getppid());
            kill(getppid(), SIGKILL);
            sleep(1);
            log("测试的子进程的状态");
            system(cmd.data());
            return 0;
        } else {
            log("测试的父进程启动: ", getpid());
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
